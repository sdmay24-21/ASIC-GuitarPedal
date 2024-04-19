// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmemorycontroller.h for the primary calling header

#ifndef VERILATED_VMEMORYCONTROLLER___024ROOT_H_
#define VERILATED_VMEMORYCONTROLLER___024ROOT_H_  // guard

#include "verilated.h"


class Vmemorycontroller__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vmemorycontroller___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(adc_clock,0,0);
    VL_IN8(record,0,0);
    VL_IN8(loop,0,0);
    VL_IN8(off_chip_mem,0,0);
    VL_IN8(off_chip_mem_ready,0,0);
    VL_OUT8(memory_we,0,0);
    CData/*0:0*/ memorycontroller__DOT__impulse_read;
    CData/*2:0*/ memorycontroller__DOT__top_offset;
    CData/*2:0*/ memorycontroller__DOT__bottom_offset;
    CData/*0:0*/ __Vdly__memorycontroller__DOT__impulse_read;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__adc_clock__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(delay_reverb,15,0);
    VL_IN16(gain,15,0);
    VL_IN16(impulses,15,0);
    VL_IN16(data_in,15,0);
    VL_OUT16(curr_adr,15,0);
    VL_OUT16(address_out,15,0);
    VL_OUT16(data_out,15,0);
    SData/*15:0*/ memorycontroller__DOT__curr_w_adr;
    SData/*10:0*/ memorycontroller__DOT__curr_impulse;
    SData/*15:0*/ memorycontroller__DOT__curr_r_adr;
    SData/*15:0*/ memorycontroller__DOT__offset_adr;
    SData/*15:0*/ memorycontroller__DOT__impulse_offset;
    SData/*15:0*/ __Vdly__curr_adr;
    SData/*15:0*/ __Vdly__memorycontroller__DOT__curr_r_adr;
    IData/*31:0*/ memorycontroller__DOT__output_buffer;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<5> __VactTriggered;
    VlTriggerVec<5> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vmemorycontroller__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vmemorycontroller___024root(Vmemorycontroller__Syms* symsp, const char* v__name);
    ~Vmemorycontroller___024root();
    VL_UNCOPYABLE(Vmemorycontroller___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
