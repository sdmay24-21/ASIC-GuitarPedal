#include "Vmemorycontroller.h"
#include "Vmemorycontroller___024root.h"

#include "verilated.h"
#include <verilated_vcd_c.h>
#include <verilated_vpi.h>  // Required to get definitions
#include <stdlib.h>

#define DEBUG_MEMOUTPUT 1
#define DEBUG_MEMSET 1
#define DEBUG_DATAPOINT 1001
#define CLOCKRATIO 4000//*2//20000000/10000
#define DATAPOINTS 20
#define ALLDATA 1
#define OFFCHIPMEMMAX 57328+1
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



  // int read_and_check() {
  //     vpiHandle vh1 = vpi_handle_by_name((PLI_BYTE8*)"TOP.memorycontroller.impulse_multiplier", NULL);
  //     if (!vh1) vl_fatal(__FILE__, __LINE__, "sim_main", "No handle found");
  //     //const char* name = vpi_get_str(vpiName, vh1);
  //     //const char* type = vpi_get_str(vpiType, vh1);
  //     //const int size = vpi_get(vpiSize, vh1);
  //     //printf("register name: %s, type: %s, size: %d\n", name, type, size);  // Prints "register name: readme, type: vpiReg, size: 32"

  //     s_vpi_value v;
  //     v.format = vpiIntVal;
  //     vpi_get_value(vh1, &v);
  //     //printf("Value of %s: %d\n", name, v.value.integer);  // Prints "Value of readme: 0"
  //     return v.value.integer;
  // }



//int16_t memory[10*1000*20]; //20 seconds of memory 
int16_t memory[ OFFCHIPMEMMAX];

int main(int argc, char** argv) {
  int test_num = atoi(argv[1]);

  char inputfile[100];
  sprintf(inputfile,"testdata/test%d.csv",test_num);
  VL_PRINTF("input file is %s\n",inputfile);
  
  char impulsefile[100];
  sprintf(impulsefile,"testdata/test%dimpulse.csv",test_num);
  VL_PRINTF("input impulse file is %s\n",impulsefile);

  char outputfile[100];
  sprintf(outputfile,"outputs/test%doutput.txt",test_num);
  VL_PRINTF("output file is %s\n",outputfile);

  
  char errorfile[100];
  sprintf(errorfile,"outputs/test%derror.txt",test_num);
  VL_PRINTF("error file is %s\n",errorfile);
  
  VL_PRINTF("Off chip max memory is %x or %d\n",OFFCHIPMEMMAX,OFFCHIPMEMMAX);

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
  //Vmemorycontroller___024root* rootp = new ~Vmemorycontroller___024root{};
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
  // if(DEBUG_MEMOUTPUT){
  // for(int i=0; i<impulse_count; i++){
  //   VL_PRINTF("Memory of %d is: %x\r\n",i,memory[i]);
  // }
  //}
    //read audio file
  FILE* stream = fopen(inputfile, "r");



  top->clk = 1;
  top->adc_clock = 1;
  char* tmp;
  int datapoint = 0;

  fgets(line, 1024, stream); //remove header
 

    VL_PRINTF("Starting test!\n");
    // Open a file in writing mode
    FILE *fptr;
    fptr = fopen(outputfile, "w");
    
    FILE *ferror;
    ferror = fopen(errorfile, "w");

    fgets(line, 1024, stream);
    tmp = strdup(line);
    int16_t expected_output = 0;
    int16_t next_expected_output=0;
    int16_t ADC_VALUE = 0;
    int16_t data_in = 0;
    bool record;
    bool off_chip_mem;
    int16_t impulses;

    while ((datapoint< DATAPOINTS )|ALLDATA) {//!Verilated::gotFinish()
      main_time++;  // Time passes...
      top->clk = !top->clk; //invert clock

      if((main_time-1)%CLOCKRATIO == 0){
        //Expected,Data,Number of Impulses,record,off_chip_mem
        //expected_output = next_expected_output;
        expected_output = atoi(getfield(tmp,0));     //DATA Output
        ADC_VALUE = atoi(getfield(tmp,1));     //DATA INPUT
        impulses = atoi(getfield(tmp,2));     //number of impulses INPUT
        record = getfield(tmp,3 );               // record
        off_chip_mem = getfield(tmp,4 ); // offchipmem
        
        if(!fgets(line, 1024, stream)) break;
        tmp = strdup(line);
        datapoint++;
      }

      if((main_time-1)%CLOCKRATIO <2){ //one clock cycle of ADC
        top->adc_clock = 1; //ADC CLOCK SET
        top->record = record;
        top->impulses = impulses;
        top->off_chip_mem = off_chip_mem;
      }
      else{
        top->adc_clock = 0; //ADC CLOCK SET
      }
      
          top->off_chip_mem_ready = 1; //for now just assume 0 cycle sram?


      top->eval();

      if(top->memory_we){
        memory[top->address_out] = ADC_VALUE;
        data_in = ADC_VALUE;
        top->data_in = data_in;
        if(DEBUG_MEMSET) VL_PRINTF("Write to mem addr %x : %x\r\n",top->address_out,data_in);
      }
      else{
        if((u_int16_t)top->address_out < (u_int16_t)OFFCHIPMEMMAX)data_in = memory[(u_int16_t)(top->address_out)];
        else VL_PRINTF("INVALID READ");
        
        top->data_in = data_in;
      }


        //LOG RESULTS
        if((main_time-1) %CLOCKRATIO == 4){
          int16_t error =(int16_t)((int16_t)expected_output - (int16_t)top->data_out);
          VL_PRINTF("[%" VL_PRI64 "d] expected output =  %04hx and data_out = %04x ADC_IN=%04hx Current Write: %04hx Error = %d\r\n",
          datapoint, expected_output, top->data_out, ADC_VALUE,top->rootp->memorycontroller__DOT__curr_w_adr ,error);
          fprintf(fptr, "%hi\n", top->data_out);
          fprintf(ferror, "%hi\n", error);
          if(abs(error)>500){
            VL_PRINTF("BIG ERROR");
          }
          
          if(DEBUG_MEMOUTPUT && datapoint == DEBUG_DATAPOINT){
            VL_PRINTF("Memory output");
            FILE *memFile;
            memFile = fopen("memFile.txt", "w");
            for(int i=0; i<OFFCHIPMEMMAX; i++){
              //VL_PRINTF("Memory of %d is: %x\r\n",i,memory[i]);
              fprintf(memFile, "Memory of addr: %04hx is: %04hx\r\n",i,memory[i]);
            }
          }
        }

        if(top->clk && datapoint == DEBUG_DATAPOINT){
        VL_PRINTF("[%" VL_PRI64 "d - %03d] main time = %04d output buffer (shift1)= %08x address_out = %04x  WE = %x data_in = %04x ADC_CLOCK = %x data out = %04x\r\n",
          datapoint,((main_time-1) %CLOCKRATIO), main_time, top->rootp->memorycontroller__DOT__output_buffer<<1, top->address_out, top->memory_we,top->data_in, top->adc_clock, top->data_out);
         VL_PRINTF("Current Impulse: %d Impulse read: %xImpulse mult: %02x Impulse Jump Value: %02x\r\n",top->rootp->memorycontroller__DOT__curr_impulse,top->rootp->memorycontroller__DOT__impulse_read,top->rootp->memorycontroller__DOT__impulse_multiplier,top->rootp->memorycontroller__DOT__jump_value);
         VL_PRINTF("Current Read Address: %x\r\n",top->rootp->memorycontroller__DOT__curr_r_adr);
         VL_PRINTF("ADC_RESET: %x\r\n",top->rootp->memorycontroller__DOT__ADC_RESET);
        }

    }




    top->final();
      delete top;
      delete contextp;
      return 0;
}
