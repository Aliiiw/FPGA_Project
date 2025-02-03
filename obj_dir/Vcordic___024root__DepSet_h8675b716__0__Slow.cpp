// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcordic.h for the primary calling header

#include "verilated.h"

#include "Vcordic___024root.h"

VL_ATTR_COLD void Vcordic___024root___initial__TOP__0(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___initial__TOP__0\n"); );
    // Body
    vlSelf->cordic__DOT__state = 1U;
}

VL_ATTR_COLD void Vcordic___024root___eval_initial(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    Vcordic___024root___initial__TOP__0(vlSelf);
}

void Vcordic___024root___combo__TOP__0(Vcordic___024root* vlSelf);

VL_ATTR_COLD void Vcordic___024root___eval_settle(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___eval_settle\n"); );
    // Body
    Vcordic___024root___combo__TOP__0(vlSelf);
}

VL_ATTR_COLD void Vcordic___024root___final(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___final\n"); );
}

VL_ATTR_COLD void Vcordic___024root___ctor_var_reset(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->calc_mode = VL_RAND_RESET_I(1);
    vlSelf->start = VL_RAND_RESET_I(1);
    vlSelf->x_0 = VL_RAND_RESET_I(20);
    vlSelf->y_0 = VL_RAND_RESET_I(20);
    vlSelf->z_0 = VL_RAND_RESET_I(20);
    vlSelf->busy = VL_RAND_RESET_I(1);
    vlSelf->x = VL_RAND_RESET_I(21);
    vlSelf->y = VL_RAND_RESET_I(21);
    vlSelf->z = VL_RAND_RESET_I(21);
    vlSelf->cordic__DOT__iter_count = VL_RAND_RESET_I(4);
    vlSelf->cordic__DOT__x_out = VL_RAND_RESET_I(21);
    vlSelf->cordic__DOT__y_out = VL_RAND_RESET_I(21);
    vlSelf->cordic__DOT__z_out = VL_RAND_RESET_I(21);
    vlSelf->cordic__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx = VL_RAND_RESET_I(4);
    vlSelf->cordic__DOT__cordic_ins__DOT__e_lut = VL_RAND_RESET_I(21);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__Vfuncout = VL_RAND_RESET_I(4);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter = VL_RAND_RESET_I(4);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__Vfuncout = VL_RAND_RESET_I(21);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n = VL_RAND_RESET_I(4);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__Vfuncout = VL_RAND_RESET_I(21);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n = VL_RAND_RESET_I(4);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__Vfuncout = VL_RAND_RESET_I(21);
    vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n = VL_RAND_RESET_I(4);
}
