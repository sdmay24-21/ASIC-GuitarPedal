// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmemorycontroller.h for the primary calling header

#include "Vmemorycontroller__pch.h"
#include "Vmemorycontroller___024root.h"

void Vmemorycontroller___024root___eval_act(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__0(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__0\n"); );
    // Init
    SData/*15:0*/ __Vdly__memorycontroller__DOT__head_adr;
    __Vdly__memorycontroller__DOT__head_adr = 0;
    SData/*15:0*/ __Vdly__memorycontroller__DOT__tail_adr;
    __Vdly__memorycontroller__DOT__tail_adr = 0;
    SData/*15:0*/ __Vdly__memorycontroller__DOT__curr_w_adr;
    __Vdly__memorycontroller__DOT__curr_w_adr = 0;
    CData/*0:0*/ __Vdly__memorycontroller__DOT__impulse_read;
    __Vdly__memorycontroller__DOT__impulse_read = 0;
    CData/*0:0*/ __Vdly__memorycontroller__DOT__large_jump;
    __Vdly__memorycontroller__DOT__large_jump = 0;
    CData/*5:0*/ __Vdly__memorycontroller__DOT__jump_value;
    __Vdly__memorycontroller__DOT__jump_value = 0;
    // Body
    __Vdly__memorycontroller__DOT__jump_value = vlSelf->memorycontroller__DOT__jump_value;
    __Vdly__memorycontroller__DOT__large_jump = vlSelf->memorycontroller__DOT__large_jump;
    __Vdly__memorycontroller__DOT__impulse_read = vlSelf->memorycontroller__DOT__impulse_read;
    __Vdly__memorycontroller__DOT__curr_w_adr = vlSelf->memorycontroller__DOT__curr_w_adr;
    __Vdly__memorycontroller__DOT__tail_adr = vlSelf->memorycontroller__DOT__tail_adr;
    __Vdly__memorycontroller__DOT__head_adr = vlSelf->memorycontroller__DOT__head_adr;
    if ((1U & (~ (IData)(vlSelf->adc_clock)))) {
        if ((1U & (~ (IData)(vlSelf->off_chip_mem)))) {
            vlSelf->memorycontroller__DOT__output_buffer 
                = (vlSelf->memorycontroller__DOT__output_buffer 
                   + ((IData)(vlSelf->data_in) * (IData)(vlSelf->memorycontroller__DOT__impulse_multiplier)));
        }
    }
    vlSelf->memory_we = ((IData)(vlSelf->adc_clock) 
                         && (IData)(vlSelf->record));
    vlSelf->data_out = (vlSelf->memorycontroller__DOT__output_buffer 
                        >> 0x10U);
    if (vlSelf->adc_clock) {
        if (vlSelf->record) {
            if (vlSelf->memorycontroller__DOT__record_buffer) {
                __Vdly__memorycontroller__DOT__head_adr 
                    = vlSelf->memorycontroller__DOT__curr_w_adr;
            }
            vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_w_adr;
            __Vdly__memorycontroller__DOT__tail_adr 
                = vlSelf->memorycontroller__DOT__curr_w_adr;
            __Vdly__memorycontroller__DOT__curr_w_adr 
                = (0xffffU & ((0xffffU == ((IData)(1U) 
                                           + (IData)(vlSelf->memorycontroller__DOT__curr_w_adr)))
                               ? (IData)(vlSelf->impulses)
                               : ((IData)(1U) + (IData)(vlSelf->memorycontroller__DOT__curr_w_adr))));
        } else {
            __Vdly__memorycontroller__DOT__curr_w_adr 
                = (0xffffU & ((((IData)(1U) + (IData)(vlSelf->memorycontroller__DOT__curr_w_adr)) 
                               == (IData)(vlSelf->memorycontroller__DOT__tail_adr))
                               ? (IData)(vlSelf->memorycontroller__DOT__head_adr)
                               : ((IData)(1U) + (IData)(vlSelf->memorycontroller__DOT__curr_w_adr))));
        }
        vlSelf->memorycontroller__DOT__curr_impulse = 0U;
        vlSelf->memorycontroller__DOT__record_buffer 
            = (1U & (~ (IData)(vlSelf->record)));
    } else if (vlSelf->off_chip_mem) {
        if (vlSelf->off_chip_mem_ready) {
            if (vlSelf->memorycontroller__DOT__impulse_read) {
                vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_impulse;
                __Vdly__memorycontroller__DOT__impulse_read = 0U;
            } else {
                vlSelf->address_out = (0xffffU & ((IData)(vlSelf->memorycontroller__DOT__curr_w_adr) 
                                                  - (IData)(vlSelf->impulses)));
                __Vdly__memorycontroller__DOT__impulse_read = 1U;
            }
        }
    } else {
        if (vlSelf->memorycontroller__DOT__impulse_read) {
            vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_r_adr;
            __Vdly__memorycontroller__DOT__large_jump 
                = (1U & ((IData)(vlSelf->data_in) >> 0xfU));
            __Vdly__memorycontroller__DOT__jump_value 
                = (0x3fU & ((IData)(vlSelf->data_in) 
                            >> 9U));
            vlSelf->memorycontroller__DOT__impulse_multiplier 
                = (0xffU & (IData)(vlSelf->data_in));
            __Vdly__memorycontroller__DOT__impulse_read = 0U;
        } else {
            vlSelf->memorycontroller__DOT__curr_r_adr 
                = (0xffffU & ((IData)(vlSelf->memorycontroller__DOT__large_jump)
                               ? ((IData)(vlSelf->memorycontroller__DOT__curr_r_adr) 
                                  + VL_SHIFTL_III(16,32,32, (IData)(vlSelf->memorycontroller__DOT__jump_value), 2U))
                               : ((IData)(vlSelf->memorycontroller__DOT__curr_r_adr) 
                                  + (IData)(vlSelf->memorycontroller__DOT__jump_value))));
        }
        vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_impulse;
        __Vdly__memorycontroller__DOT__impulse_read = 1U;
    }
    vlSelf->memorycontroller__DOT__head_adr = __Vdly__memorycontroller__DOT__head_adr;
    vlSelf->memorycontroller__DOT__tail_adr = __Vdly__memorycontroller__DOT__tail_adr;
    vlSelf->memorycontroller__DOT__curr_w_adr = __Vdly__memorycontroller__DOT__curr_w_adr;
    vlSelf->memorycontroller__DOT__impulse_read = __Vdly__memorycontroller__DOT__impulse_read;
    vlSelf->memorycontroller__DOT__large_jump = __Vdly__memorycontroller__DOT__large_jump;
    vlSelf->memorycontroller__DOT__jump_value = __Vdly__memorycontroller__DOT__jump_value;
}

void Vmemorycontroller___024root___eval_nba(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vmemorycontroller___024root___eval_triggers__act(Vmemorycontroller___024root* vlSelf);

bool Vmemorycontroller___024root___eval_phase__act(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vmemorycontroller___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vmemorycontroller___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vmemorycontroller___024root___eval_phase__nba(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vmemorycontroller___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__nba(Vmemorycontroller___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmemorycontroller___024root___dump_triggers__act(Vmemorycontroller___024root* vlSelf);
#endif  // VL_DEBUG

void Vmemorycontroller___024root___eval(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vmemorycontroller___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../../../rtl/memory/memorycontroller.v", 8, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vmemorycontroller___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../../../rtl/memory/memorycontroller.v", 8, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vmemorycontroller___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vmemorycontroller___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vmemorycontroller___024root___eval_debug_assertions(Vmemorycontroller___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->adc_clock & 0xfeU))) {
        Verilated::overWidthError("adc_clock");}
    if (VL_UNLIKELY((vlSelf->record & 0xfeU))) {
        Verilated::overWidthError("record");}
    if (VL_UNLIKELY((vlSelf->off_chip_mem & 0xfeU))) {
        Verilated::overWidthError("off_chip_mem");}
    if (VL_UNLIKELY((vlSelf->off_chip_mem_ready & 0xfeU))) {
        Verilated::overWidthError("off_chip_mem_ready");}
}
#endif  // VL_DEBUG
