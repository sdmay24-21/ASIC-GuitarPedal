#include "Vmemorycontroller.h"
#include "verilated.h"
#include <verilated_vcd_c.h>

#define CLOCKRATIO 2000//20000000/10000
#define DATAPOINTS 2
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
  Verilated::debug(9);
    
    // Verilator must compute traced signals
  Verilated::traceEverOn(true);


    
    // Create logs/ directory in case we have traces to put under it
  Verilated::mkdir("logs");
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  Vmemorycontroller* top = new Vmemorycontroller{contextp};
  
  //VerilatedVcdC *m_trace = new VerilatedVcdC;
  //top->trace(m_trace, 5);

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
    // Open a file in writing mode
    FILE *fptr;
    fptr = fopen("output.txt", "w");
    fgets(line, 1024, stream);
    tmp = strdup(line);
    int16_t expected_output;

    while (datapoint< DATAPOINTS) {//!Verilated::gotFinish()
      main_time++;  // Time passes...
      top->clk = !top->clk; //invert clock

      if(main_time%CLOCKRATIO == 0){
        top->adc_clock = 1; //ADC CLOCK SET
        //Expected,Data,Number of Impulses,record,off_chip_mem
        expected_output = atoi(getfield(tmp,0));     //DATA Output
        int16_t data_in = atoi(getfield(tmp,1));     //DATA INPUT
        int16_t impulses = atoi(getfield(tmp,2));     //number of impulses INPUT
        bool record = getfield(tmp,3 );               // record
        bool off_chip_mem = getfield(tmp,4 ); // offchipmem

        top->data_in = data_in;
        top->impulses = impulses;
        top->record = record;
        top->off_chip_mem = off_chip_mem;


        if(!fgets(line, 1024, stream)) break;
        tmp = strdup(line);
        
        datapoint++;

      }
      else{
        top->adc_clock = 0; //ADC CLOCK SET
      }

          top->off_chip_mem_ready = 1; //for now just assume 0 cycle sram?


      top->eval();
        //LOG RESULTS
        if((main_time) %CLOCKRATIO == 0){
          VL_PRINTF("[%" VL_PRI64 "d] expected output =  %x and data_out = %x Inputs: clk=%x data_in=%x  number of impulses=%x record=%x\r\n",
          datapoint, expected_output, top->data_out, top->clk, top->data_in,top->impulses, top->record);
          fprintf(fptr, "%d\n", top->data_out);
        }
        if(top->clk){
        VL_PRINTF("[%" VL_PRI64 "d - %d] main time = %d address_out = %x  ADC_CLOCK = %x data out = %x\r\n",
          datapoint,((main_time) %CLOCKRATIO), main_time, top->address_out, top->adc_clock, top->data_out);
        }
    }




    top->final();
      delete top;
      delete contextp;
      return 0;
}
