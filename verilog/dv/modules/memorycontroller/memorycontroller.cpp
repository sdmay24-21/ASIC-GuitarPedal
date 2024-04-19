  #include "memorycontroller.h"
  #include "verilated.h"

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

//https://stackoverflow.com/questions/12911299/read-csv-file-in-c
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int16_t memory[10*1000*20]; //20 seconds of memory 

int main(int argc, char** argv) {
  char* inputfile = argv[0]; //file to load
  char* impulsefile = argv[1];
  char* outputfile = argv[2];
  char line[1024];

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
  Verilated::debug(0);
    
    // Verilator must compute traced signals
  Verilated::traceEverOn(true);
    
    // Create logs/ directory in case we have traces to put under it
  Verilated::mkdir("logs");
  memorycontroller* top = new memorycontroller{contextp};

    //get RAM (impulses)
  FILE* impulsefile_stream = fopen(impulsefile, "r");
  VL_PRINTF("Loading impulses\n");
  int impulse_count = 0;
  while (fgets(line, sizeof(line), impulsefile_stream)) {
    char* tmp = strdup(line);
    int16_t data_in = getfield(tmp,0);
    memory[impulse_count] = data_in; //load into ram
    impulse_count++;
  }



    //read audio file
  FILE* stream = fopen(inputfile, "r");



  top->clk = 0;
  top->adc_clock = 0;
    
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  while (!Verilated::gotFinish()) {
    main_time++;  // Time passes...
    top->clk = !top->clk; //invert clock

    

    if(main_time%clock_ratio || (main_time-1)%clock_ratio|| (main_time-2)%clock_ratio){ // 3 cycle ADC
      top->adc_clock = 1; //ADC CLOCK SET


    }
    else{
      top->adc_clock = 0; //ADC CLOCK SET
    }

      //get data from file
      fgets(line, 1024, stream);
      char* tmp = strdup(line);
      //header = ["Data", "Impulses", "Loop","record","off_chip_mem","off_chip_mem_ready"]

      //int clk =         getfield(tmp,0);     //CLK CYCLE NUMBER
      int16_t data_in = getfield(tmp,0);     //DATA INPUT
      top->data_in = data_in;
      int16_t impluses = getfield(tmp,1);     //number of impulses INPUT
      top->impulses = impulses;
      bool loop = getfield(tmp,2 ); // loop
      top->loop = loop;
      bool record = getfield(tmp,3 ); // record
      top->record = record;
      bool off_chip_mem = getfield(tmp,4 ); // offchipmem
      top->off_chip_mem = off_chip_mem;
      bool off_chip_mem_ready = getfield(tmp,5 ); // offchipmemready
      top->off_chip_mem_ready = off_chip_mem_ready;

    //EVALUATE the top level design
    top->eval();

    //LOG RESULTS
    VL_PRINTF("[%" VL_PRI64 "d] Inputs: clk=%x data_in=%x impulses=%x loop=%x record=%x\n",
      main_time, top->clk, top->data_in, top->impulses, top->loop, top->record);
    //VL_PRINTF("[%" VL_PRI64 "d] Outputs: clk=%x data_in=%x impulses=%x loop=%x record=%x\n",
    //  main_time, top->clk, top->data_in, top->impulses, top->loop, top->record);
  }
    top->final();
      delete top;
      delete contextp;
      return 0;
}
