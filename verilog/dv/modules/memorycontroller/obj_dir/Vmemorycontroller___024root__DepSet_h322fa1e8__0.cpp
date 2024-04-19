// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmemorycontroller.h for the primary calling header

#include "Vmemorycontroller__pch.h"
#include "Vmemorycontroller___024root.h"

void Vmemorycontroller___024root___eval_act(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__0(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__0\n"); );
    // Body
    vlSelf->__Vdly__curr_adr = vlSelf->curr_adr;
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__1(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->__Vdly__memorycontroller__DOT__curr_r_adr 
        = vlSelf->memorycontroller__DOT__curr_r_adr;
    vlSelf->__Vdly__memorycontroller__DOT__impulse_read 
        = vlSelf->memorycontroller__DOT__impulse_read;
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__2(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__2\n"); );
    // Body
    vlSelf->memorycontroller__DOT__output_buffer = 0U;
    vlSelf->data_out = (vlSelf->memorycontroller__DOT__output_buffer 
                        >> 0x10U);
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__4(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__4\n"); );
    // Body
    vlSelf->memory_we = 0U;
    if (vlSelf->off_chip_mem) {
        if (vlSelf->off_chip_mem_ready) {
            if (vlSelf->memorycontroller__DOT__impulse_read) {
                vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_impulse;
                vlSelf->__Vdly__memorycontroller__DOT__impulse_read = 0U;
            } else {
                vlSelf->address_out = (0xffffU & ((IData)(vlSelf->memorycontroller__DOT__curr_w_adr) 
                                                  - (IData)(vlSelf->memorycontroller__DOT__offset_adr)));
                vlSelf->__Vdly__memorycontroller__DOT__impulse_read = 1U;
            }
        }
    } else if (vlSelf->memorycontroller__DOT__impulse_read) {
        vlSelf->memorycontroller__DOT__top_offset = 
            (7U & ((IData)(vlSelf->data_in) >> 0xdU));
        vlSelf->memorycontroller__DOT__bottom_offset 
            = (7U & ((IData)(vlSelf->data_in) >> 9U));
        vlSelf->address_out = vlSelf->memorycontroller__DOT__offset_adr;
        vlSelf->__Vdly__memorycontroller__DOT__impulse_read = 0U;
    } else {
        vlSelf->__Vdly__memorycontroller__DOT__curr_r_adr 
            = (0xffffU & ((IData)(vlSelf->memorycontroller__DOT__curr_r_adr) 
                          + (IData)(vlSelf->memorycontroller__DOT__impulse_offset)));
        vlSelf->address_out = vlSelf->memorycontroller__DOT__curr_r_adr;
        vlSelf->__Vdly__memorycontroller__DOT__impulse_read = 1U;
    }
    vlSelf->memorycontroller__DOT__impulse_read = vlSelf->__Vdly__memorycontroller__DOT__impulse_read;
    vlSelf->memorycontroller__DOT__impulse_offset = 
        (((IData)(vlSelf->memorycontroller__DOT__top_offset) 
          << 7U) | (IData)(vlSelf->memorycontroller__DOT__bottom_offset));
    vlSelf->memorycontroller__DOT__curr_r_adr = vlSelf->__Vdly__memorycontroller__DOT__curr_r_adr;
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__5(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__5\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->record)))) {
        vlSelf->memory_we = 1U;
        vlSelf->address_out = vlSelf->curr_adr;
    }
    vlSelf->__Vdly__curr_adr = (0xffffU & ((0xffffU 
                                            == ((IData)(1U) 
                                                + (IData)(vlSelf->curr_adr)))
                                            ? (IData)(vlSelf->impulses)
                                            : ((IData)(1U) 
                                               + (IData)(vlSelf->curr_adr))));
    vlSelf->memorycontroller__DOT__curr_impulse = 0U;
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__6(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__6\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->record)))) {
        vlSelf->memory_we = 1U;
        vlSelf->address_out = vlSelf->curr_adr;
    }
    vlSelf->__Vdly__curr_adr = (0xffffU & ((0xffffU 
                                            == ((IData)(1U) 
                                                + (IData)(vlSelf->curr_adr)))
                                            ? (IData)(vlSelf->impulses)
                                            : ((IData)(1U) 
                                               + (IData)(vlSelf->curr_adr))));
}

VL_INLINE_OPT void Vmemorycontroller___024root___nba_sequent__TOP__8(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___nba_sequent__TOP__8\n"); );
    // Body
    vlSelf->curr_adr = vlSelf->__Vdly__curr_adr;
}

void Vmemorycontroller___024root___eval_nba(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_nba\n"); );
    // Body
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vmemorycontroller___024root___nba_sequent__TOP__8(vlSelf);
    }
}

void Vmemorycontroller___024root___eval_triggers__act(Vmemorycontroller___024root* vlSelf);

bool Vmemorycontroller___024root___eval_phase__act(Vmemorycontroller___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<5> __VpreTriggered;
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
    if (false && vlSelf) {}  // Prevent unused
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
    if (false && vlSelf) {}  // Prevent unused
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
    if (false && vlSelf) {}  // Prevent unused
    Vmemorycontroller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmemorycontroller___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->adc_clock & 0xfeU))) {
        Verilated::overWidthError("adc_clock");}
    if (VL_UNLIKELY((vlSelf->record & 0xfeU))) {
        Verilated::overWidthError("record");}
    if (VL_UNLIKELY((vlSelf->loop & 0xfeU))) {
        Verilated::overWidthError("loop");}
    if (VL_UNLIKELY((vlSelf->off_chip_mem & 0xfeU))) {
        Verilated::overWidthError("off_chip_mem");}
    if (VL_UNLIKELY((vlSelf->off_chip_mem_ready & 0xfeU))) {
        Verilated::overWidthError("off_chip_mem_ready");}
}
#endif  // VL_DEBUG
