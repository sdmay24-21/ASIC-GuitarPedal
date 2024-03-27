  #include "top_level_level3_tb.h"
  #include "verilated.h"

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

int main(int argc, char** argv) {
  //argv[0] file to load
  

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
  Verilated::debug(0);
    
    // Verilator must compute traced signals
  Verilated::traceEverOn(true);
    
    // Create logs/ directory in case we have traces to put under it
  Verilated::mkdir("logs");
  pedal_top* top = new pedal_top{contextp};

  top->clk = 0;
  top->adc_clock = 0;
    
  VerilatedContext* contextp = new VerilatedContext;
  contextp->commandArgs(argc, argv);

  while (!Verilated::gotFinish()) {
    main_time++;  // Time passes...
    top->clk = !top->clk; //invert clock
    if(main_time%clock_ratio){
      top->adc_clock = !top->adc_clock; //ADC CLOCK SET
      
      if(top->adc_clock){ //SET VALUES
        top->adc = 

      }
      else{ //READ DAC VALUES
        top->dac
      }
    }

    top->eval();

    //LOG RESULTS
    VL_PRINTF("[%" VL_PRI64 "d] clk=%x rstl=%x iquad=%" VL_PRI64 "x"
      " -> oquad=%" VL_PRI64 "x owide=%x_%08x_%08x\n",
      main_time, top->clk, top->reset_l, top->in_quad, top->out_quad, top->out_wide[2],
      top->out_wide[1], top->out_wide[0]);
  }
  
  //end simulation
      top->final();
      delete top;
      delete contextp;
      return 0;
  }
