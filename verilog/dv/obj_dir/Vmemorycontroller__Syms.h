// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMEMORYCONTROLLER__SYMS_H_
#define VERILATED_VMEMORYCONTROLLER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmemorycontroller.h"

// INCLUDE MODULE CLASSES
#include "Vmemorycontroller___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vmemorycontroller__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmemorycontroller* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmemorycontroller___024root    TOP;

    // CONSTRUCTORS
    Vmemorycontroller__Syms(VerilatedContext* contextp, const char* namep, Vmemorycontroller* modelp);
    ~Vmemorycontroller__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
