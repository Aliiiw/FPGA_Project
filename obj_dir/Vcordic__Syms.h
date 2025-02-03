// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCORDIC__SYMS_H_
#define VERILATED_VCORDIC__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcordic.h"

// INCLUDE MODULE CLASSES
#include "Vcordic___024root.h"

// SYMS CLASS (contains all model state)
class Vcordic__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcordic* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcordic___024root              TOP;

    // CONSTRUCTORS
    Vcordic__Syms(VerilatedContext* contextp, const char* namep, Vcordic* modelp);
    ~Vcordic__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
