// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmemorycontroller.h for the primary calling header

#include "Vmemorycontroller__pch.h"
#include "Vmemorycontroller___024root.h"

VL_ATTR_COLD void Vmemorycontroller___024root___eval_static(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vmemorycontroller___024root___eval_initial(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vmemorycontroller___024root___eval_final(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__stl(Vmemorycontroller___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vmemorycontroller___024root___eval_phase__stl(Vmemorycontroller___024root* vlSelf);

VL_ATTR_COLD void Vmemorycontroller___024root___eval_settle(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vmemorycontroller___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../rtl/memory/memorycontroller.v", 8, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vmemorycontroller___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__stl(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmemorycontroller___024root___stl_sequent__TOP__0(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->data_out = (vlSelf->memorycontroller__DOT__output_buffer 
                        >> 0x10U);
}

VL_ATTR_COLD void Vmemorycontroller___024root___eval_stl(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vmemorycontroller___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vmemorycontroller___024root___eval_triggers__stl(Vmemorycontroller___024root* vlSelf);

VL_ATTR_COLD bool Vmemorycontroller___024root___eval_phase__stl(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vmemorycontroller___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vmemorycontroller___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__act(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__nba(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmemorycontroller___024root___ctor_var_reset(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->adc_clock = VL_RAND_RESET_I(1);
    vlSelf->record = VL_RAND_RESET_I(1);
    vlSelf->off_chip_mem = VL_RAND_RESET_I(1);
    vlSelf->off_chip_mem_ready = VL_RAND_RESET_I(1);
    vlSelf->impulses = VL_RAND_RESET_I(16);
    vlSelf->data_in = VL_RAND_RESET_I(16);
    vlSelf->memory_we = VL_RAND_RESET_I(1);
    vlSelf->address_out = VL_RAND_RESET_I(16);
    vlSelf->data_out = VL_RAND_RESET_I(16);
    vlSelf->memorycontroller__DOT__head_adr = VL_RAND_RESET_I(16);
    vlSelf->memorycontroller__DOT__tail_adr = VL_RAND_RESET_I(16);
    vlSelf->memorycontroller__DOT__curr_w_adr = VL_RAND_RESET_I(16);
    vlSelf->memorycontroller__DOT__curr_impulse = VL_RAND_RESET_I(11);
    vlSelf->memorycontroller__DOT__output_buffer = VL_RAND_RESET_I(32);
    vlSelf->memorycontroller__DOT__curr_r_adr = VL_RAND_RESET_I(16);
    vlSelf->memorycontroller__DOT__impulse_read = VL_RAND_RESET_I(1);
    vlSelf->memorycontroller__DOT__large_jump = VL_RAND_RESET_I(1);
    vlSelf->memorycontroller__DOT__jump_value = VL_RAND_RESET_I(6);
    vlSelf->memorycontroller__DOT__impulse_multiplier = VL_RAND_RESET_I(8);
    vlSelf->memorycontroller__DOT__record_buffer = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
