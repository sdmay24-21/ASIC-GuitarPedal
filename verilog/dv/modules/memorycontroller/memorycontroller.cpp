  #include "Vmemorycontroller.h"
  #include "verilated.h"

#define CLOCKRATIO 20000000/10000

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

//https://stackoverflow.com/questions/12911299/read-csv-file-in-c
const char* getfield(char* line, int num)
{
    char buf[512];
    strcpy(buf, line);
    char* tok;
    // VL_PRINTF(buf);
    // //fflush(stdout)
    // tok = strtok(buf, ",");
    // VL_PRINTF("%s\n", tok);
    // VL_PRINTF("%s\n",buf);
    // tok = strtok(buf, ",");
    // VL_PRINTF("%s\n", tok);


    for (tok = strtok(buf, ",");
            tok && *tok;
            tok = strtok(NULL, ","))
    {
     // VL_PRINTF("%s\n",tok);
      //VL_PRINTF("%d\n",num);
        if (!num)
            return tok;
        num--;
    }
    return NULL;
}

int16_t memory[10*1000*20]; //20 seconds of memory 

int main(int argc, char** argv) {
  char* inputfile = argv[1]; //file to load
  VL_PRINTF("input file is %s\n",inputfile);
  char* impulsefile = argv[2];
  VL_PRINTF("input impulse file is %s\n",impulsefile);
  char* outputfile = argv[3];
  VL_PRINTF("output file is %s\n",outputfile);

  char line[1024];
  

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
  Verilated::debug(0);
    
    // Verilator must compute traced signals
  Verilated::traceEverOn(true);
    
    // Create logs/ directory in case we have traces to put under it
  Verilated::mkdir("logs");
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);
  Vmemorycontroller* top = new Vmemorycontroller{contextp};

    //get RAM (impulses)
  FILE* impulsefile_stream = fopen(impulsefile, "r");
  VL_PRINTF("Loading impulses\n");
  int impulse_count = 0;
  fgets(line, sizeof(line), impulsefile_stream); //get header (unused)

  while (fgets(line, sizeof(line), impulsefile_stream)) {

    char tmp[1080];
    strcpy(tmp, line);

    //VL_PRINTF("Line %s and impulse num is %d\n",tmp,impulse_count);
    int16_t data_in = atoi(getfield(tmp,0));
    //VL_PRINTF("data in %d\n",data_in);
    
    memory[impulse_count] = data_in; //load into ram
    impulse_count++;
  }



    //read audio file
  FILE* stream = fopen(inputfile, "r");



  top->clk = 0;
  top->adc_clock = 0;
  char* tmp;

  int datapoint = 0;
  fgets(line, 1024, stream); //remove header
 

    VL_PRINTF("Starting test!\n");
    fgets(line, 1024, stream);
    tmp = strdup(line);

    while (!Verilated::gotFinish()) {
      main_time++;  // Time passes...
      top->clk = !top->clk; //invert clock

      if(main_time%CLOCKRATIO == 0){
        top->adc_clock = 1; //ADC CLOCK SET

        int16_t data_in = atoi(getfield(tmp,0));     //DATA INPUT
        top->data_in = data_in;
        int16_t impulses = atoi(getfield(tmp,1));     //number of impulses INPUT
        top->impulses = impulses;
        bool record = getfield(tmp,3 );               // record
        top->record = record;


        bool loop = getfield(tmp,2 ); // loop useless
        //LOG RESULTS
        VL_PRINTF("[%" VL_PRI64 "d] Inputs: clk=%x data_in=%x data_out = %x impulses=%x record=%x\n",
        datapoint, top->clk, top->data_in, top->data_out,top->impulses, top->record);
        
        if(!fgets(line, 1024, stream)) break;
        tmp = strdup(line);
        
        datapoint++;

      }
      else{
        top->adc_clock = 0; //ADC CLOCK SET
      }
          bool off_chip_mem = getfield(tmp,4 ); // offchipmem
          top->off_chip_mem = off_chip_mem;
          bool off_chip_mem_ready = getfield(tmp,5 ); // offchipmemready
          top->off_chip_mem_ready = off_chip_mem_ready;


      top->eval();
    }




    top->final();
      delete top;
      delete contextp;
      return 0;
}
