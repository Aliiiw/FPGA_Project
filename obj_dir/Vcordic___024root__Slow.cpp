// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcordic.h for the primary calling header

#include "verilated.h"

#include "Vcordic__Syms.h"
#include "Vcordic___024root.h"

void Vcordic___024root___ctor_var_reset(Vcordic___024root* vlSelf);

Vcordic___024root::Vcordic___024root(Vcordic__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcordic___024root___ctor_var_reset(this);
}

void Vcordic___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcordic___024root::~Vcordic___024root() {
}
