// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcordic.h for the primary calling header

#ifndef VERILATED_VCORDIC___024ROOT_H_
#define VERILATED_VCORDIC___024ROOT_H_  // guard

#include "verilated.h"

class Vcordic__Syms;
VL_MODULE(Vcordic___024root) {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(calc_mode,0,0);
    VL_IN8(start,0,0);
    VL_OUT8(busy,0,0);
    CData/*3:0*/ cordic__DOT__iter_count;
    CData/*1:0*/ cordic__DOT__state;
    CData/*3:0*/ cordic__DOT__cordic_ins__DOT__iter_idx;
    CData/*3:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__Vfuncout;
    CData/*3:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter;
    CData/*3:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n;
    CData/*3:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n;
    CData/*3:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n;
    CData/*0:0*/ __Vclklast__TOP__clk;
    VL_IN(x_0,19,0);
    VL_IN(y_0,19,0);
    VL_IN(z_0,19,0);
    VL_OUT(x,20,0);
    VL_OUT(y,20,0);
    VL_OUT(z,20,0);
    IData/*20:0*/ cordic__DOT__x_out;
    IData/*20:0*/ cordic__DOT__y_out;
    IData/*20:0*/ cordic__DOT__z_out;
    IData/*20:0*/ cordic__DOT__cordic_ins__DOT__e_lut;
    IData/*20:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__Vfuncout;
    IData/*20:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__Vfuncout;
    IData/*20:0*/ __Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__Vfuncout;

    // INTERNAL VARIABLES
    Vcordic__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcordic___024root(Vcordic__Syms* symsp, const char* name);
    ~Vcordic___024root();
    VL_UNCOPYABLE(Vcordic___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
