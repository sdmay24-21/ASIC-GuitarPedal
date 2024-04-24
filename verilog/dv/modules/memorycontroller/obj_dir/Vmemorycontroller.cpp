// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmemorycontroller__pch.h"

//============================================================
// Constructors

Vmemorycontroller::Vmemorycontroller(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmemorycontroller__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , adc_clock{vlSymsp->TOP.adc_clock}
    , record{vlSymsp->TOP.record}
    , off_chip_mem{vlSymsp->TOP.off_chip_mem}
    , off_chip_mem_ready{vlSymsp->TOP.off_chip_mem_ready}
    , memory_we{vlSymsp->TOP.memory_we}
    , impulses{vlSymsp->TOP.impulses}
    , data_in{vlSymsp->TOP.data_in}
    , address_out{vlSymsp->TOP.address_out}
    , data_out{vlSymsp->TOP.data_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmemorycontroller::Vmemorycontroller(const char* _vcname__)
    : Vmemorycontroller(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmemorycontroller::~Vmemorycontroller() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmemorycontroller___024root___eval_debug_assertions(Vmemorycontroller___024root* vlSelf);
#endif  // VL_DEBUG
void Vmemorycontroller___024root___eval_static(Vmemorycontroller___024root* vlSelf);
void Vmemorycontroller___024root___eval_initial(Vmemorycontroller___024root* vlSelf);
void Vmemorycontroller___024root___eval_settle(Vmemorycontroller___024root* vlSelf);
void Vmemorycontroller___024root___eval(Vmemorycontroller___024root* vlSelf);

void Vmemorycontroller::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmemorycontroller::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmemorycontroller___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmemorycontroller___024root___eval_static(&(vlSymsp->TOP));
        Vmemorycontroller___024root___eval_initial(&(vlSymsp->TOP));
        Vmemorycontroller___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmemorycontroller___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmemorycontroller::eventsPending() { return false; }

uint64_t Vmemorycontroller::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vmemorycontroller::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmemorycontroller___024root___eval_final(Vmemorycontroller___024root* vlSelf);

VL_ATTR_COLD void Vmemorycontroller::final() {
    Vmemorycontroller___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmemorycontroller::hierName() const { return vlSymsp->name(); }
const char* Vmemorycontroller::modelName() const { return "Vmemorycontroller"; }
unsigned Vmemorycontroller::threads() const { return 1; }
void Vmemorycontroller::prepareClone() const { contextp()->prepareClone(); }
void Vmemorycontroller::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vmemorycontroller::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vmemorycontroller::trace()' called on model that was Verilated without --trace option");
}
