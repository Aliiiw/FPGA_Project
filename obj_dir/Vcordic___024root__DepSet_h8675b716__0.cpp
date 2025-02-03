// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcordic.h for the primary calling header

#include "verilated.h"

#include "Vcordic___024root.h"

VL_INLINE_OPT void Vcordic___024root___sequent__TOP__0(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___sequent__TOP__0\n"); );
    // Init
    CData/*1:0*/ __Vdly__cordic__DOT__state;
    CData/*3:0*/ __Vdly__cordic__DOT__iter_count;
    // Body
    __Vdly__cordic__DOT__state = vlSelf->cordic__DOT__state;
    __Vdly__cordic__DOT__iter_count = vlSelf->cordic__DOT__iter_count;
    if (vlSelf->reset) {
        vlSelf->x = 0U;
        vlSelf->y = 0U;
        vlSelf->z = 0U;
        __Vdly__cordic__DOT__state = 1U;
        vlSelf->busy = 1U;
        __Vdly__cordic__DOT__iter_count = 0U;
    } else if ((1U == (IData)(vlSelf->cordic__DOT__state))) {
        if (vlSelf->start) {
            vlSelf->x = ((0x100000U & (vlSelf->x_0 
                                       << 1U)) | vlSelf->x_0);
            vlSelf->y = ((0x100000U & (vlSelf->y_0 
                                       << 1U)) | vlSelf->y_0);
            vlSelf->z = ((0x100000U & (vlSelf->z_0 
                                       << 1U)) | vlSelf->z_0);
            vlSelf->busy = 1U;
            __Vdly__cordic__DOT__state = 2U;
            __Vdly__cordic__DOT__iter_count = 0U;
        }
    } else if ((2U == (IData)(vlSelf->cordic__DOT__state))) {
        if ((0xfU == (IData)(vlSelf->cordic__DOT__iter_count))) {
            vlSelf->busy = 0U;
            __Vdly__cordic__DOT__state = 1U;
        } else {
            __Vdly__cordic__DOT__iter_count = (0xfU 
                                               & ((IData)(1U) 
                                                  + (IData)(vlSelf->cordic__DOT__iter_count)));
            vlSelf->x = vlSelf->cordic__DOT__x_out;
            vlSelf->y = vlSelf->cordic__DOT__y_out;
            vlSelf->z = vlSelf->cordic__DOT__z_out;
        }
    }
    vlSelf->cordic__DOT__state = __Vdly__cordic__DOT__state;
    vlSelf->cordic__DOT__iter_count = __Vdly__cordic__DOT__iter_count;
}

VL_INLINE_OPT void Vcordic___024root___combo__TOP__0(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___combo__TOP__0\n"); );
    // Init
    CData/*0:0*/ cordic__DOT__cordic_ins__DOT__d_flag;
    // Body
    if (vlSelf->calc_mode) {
        cordic__DOT__cordic_ins__DOT__d_flag = (1U 
                                                & ((0x100000U 
                                                    & vlSelf->y)
                                                    ? 1U
                                                    : 0U));
        vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx 
            = vlSelf->cordic__DOT__iter_count;
        vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n 
            = vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx;
        if (((((((((0U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n)) 
                   | (1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                  | (2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                 | (3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                | (4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
               | (5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
              | (6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
             | (7U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n)))) {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__Vfuncout 
                = ((0U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                    ? 0x3ffffU : ((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                   ? 0x1ffffU : ((2U 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                  ? 0xffffU
                                                  : 
                                                 ((3U 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                   ? 0x7fffU
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                    ? 0x3fffU
                                                    : 
                                                   ((5U 
                                                     == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                     ? 0x1fffU
                                                     : 
                                                    ((6U 
                                                      == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                      ? 0xfffU
                                                      : 0x7ffU)))))));
        } else if (((((((((8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n)) 
                          | (9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                         | (0xaU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                        | (0xbU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                       | (0xcU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                      | (0xdU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                     | (0xeU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))) 
                    | (0xfU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n)))) {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__Vfuncout 
                = ((8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                    ? 0x3ffU : ((9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                 ? 0x1ffU : ((0xaU 
                                              == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                              ? 0xffU
                                              : ((0xbU 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                  ? 0x7fU
                                                  : 
                                                 ((0xcU 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                   ? 0x3fU
                                                   : 
                                                  ((0xdU 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                    ? 0x1fU
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__n))
                                                     ? 0xfU
                                                     : 7U)))))));
        }
        vlSelf->cordic__DOT__cordic_ins__DOT__e_lut 
            = vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__linear_lut__1__Vfuncout;
    } else {
        cordic__DOT__cordic_ins__DOT__d_flag = (1U 
                                                & ((0x100000U 
                                                    & vlSelf->z)
                                                    ? 0U
                                                    : 1U));
        vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter 
            = vlSelf->cordic__DOT__iter_count;
        if (((((((((0U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter)) 
                   | (1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                  | (2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                 | (3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                | (4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
               | (5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
              | (6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
             | (7U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter)))) {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__Vfuncout 
                = ((0U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                    ? 1U : ((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                             ? 2U : ((2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                      ? 3U : ((3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                               ? 4U
                                               : ((4U 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                   ? 4U
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                    ? 5U
                                                    : 
                                                   ((6U 
                                                     == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                     ? 6U
                                                     : 7U)))))));
        } else if (((((((((8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter)) 
                          | (9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                         | (0xaU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                        | (0xbU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                       | (0xcU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                      | (0xdU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                     | (0xeU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))) 
                    | (0xfU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter)))) {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__Vfuncout 
                = ((8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                    ? 8U : ((9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                             ? 9U : ((0xaU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                      ? 0xaU : ((0xbU 
                                                 == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                 ? 0xbU
                                                 : 
                                                ((0xcU 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                  ? 0xcU
                                                  : 
                                                 ((0xdU 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                   ? 0xdU
                                                   : 
                                                  ((0xeU 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__iter))
                                                    ? 0xdU
                                                    : 0xeU)))))));
        }
        vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx 
            = vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__hyperbolic_idx_lut__0__Vfuncout;
        if (vlSelf->calc_mode) {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n 
                = vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx;
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__Vfuncout 
                = (((((((((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n)) 
                          | (2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                         | (3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                        | (4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                       | (5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                      | (6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                     | (7U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))) 
                    | (8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n)))
                    ? ((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                        ? 0x232d2U : ((2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                       ? 0x1054eU : 
                                      ((3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                        ? 0x802aU : 
                                       ((4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                         ? 0x4001U : 
                                        ((5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                          ? 0x2000U
                                          : ((6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                              ? 0x1000U
                                              : ((7U 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                                  ? 0x800U
                                                  : 0x400U)))))))
                    : ((9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                        ? 0x200U : ((0xaU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                     ? 0x100U : ((0xbU 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                                  ? 0x80U
                                                  : 
                                                 ((0xcU 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                                   ? 0x40U
                                                   : 
                                                  ((0xdU 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                                    ? 0x20U
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__n))
                                                     ? 0x10U
                                                     : 0U)))))));
            vlSelf->cordic__DOT__cordic_ins__DOT__e_lut 
                = vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__3__Vfuncout;
        } else {
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n 
                = vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx;
            vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__Vfuncout 
                = (((((((((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n)) 
                          | (2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                         | (3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                        | (4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                       | (5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                      | (6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                     | (7U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))) 
                    | (8U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n)))
                    ? ((1U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                        ? 0x232d2U : ((2U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                       ? 0x1054eU : 
                                      ((3U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                        ? 0x802aU : 
                                       ((4U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                         ? 0x4001U : 
                                        ((5U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                          ? 0x2000U
                                          : ((6U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                              ? 0x1000U
                                              : ((7U 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                                  ? 0x800U
                                                  : 0x400U)))))))
                    : ((9U == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                        ? 0x200U : ((0xaU == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                     ? 0x100U : ((0xbU 
                                                  == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                                  ? 0x80U
                                                  : 
                                                 ((0xcU 
                                                   == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                                   ? 0x40U
                                                   : 
                                                  ((0xdU 
                                                    == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                                    ? 0x20U
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__n))
                                                     ? 0x10U
                                                     : 0U)))))));
            vlSelf->cordic__DOT__cordic_ins__DOT__e_lut 
                = vlSelf->__Vfunc_cordic__DOT__cordic_ins__DOT__atanh_lut__2__Vfuncout;
        }
    }
    if (cordic__DOT__cordic_ins__DOT__d_flag) {
        vlSelf->cordic__DOT__y_out = (0x1fffffU & (vlSelf->y 
                                                   + 
                                                   VL_SHIFTRS_III(21,21,4, vlSelf->x, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx))));
        vlSelf->cordic__DOT__x_out = (0x1fffffU & ((IData)(vlSelf->calc_mode)
                                                    ? vlSelf->x
                                                    : 
                                                   ((IData)(vlSelf->calc_mode)
                                                     ? 
                                                    (vlSelf->x 
                                                     - 
                                                     VL_SHIFTRS_III(21,21,4, vlSelf->y, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx)))
                                                     : 
                                                    (vlSelf->x 
                                                     + 
                                                     VL_SHIFTRS_III(21,21,4, vlSelf->y, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx))))));
        vlSelf->cordic__DOT__z_out = (0x1fffffU & (vlSelf->z 
                                                   - vlSelf->cordic__DOT__cordic_ins__DOT__e_lut));
    } else {
        vlSelf->cordic__DOT__y_out = (0x1fffffU & (vlSelf->y 
                                                   - 
                                                   VL_SHIFTRS_III(21,21,4, vlSelf->x, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx))));
        vlSelf->cordic__DOT__x_out = (0x1fffffU & ((IData)(vlSelf->calc_mode)
                                                    ? vlSelf->x
                                                    : 
                                                   ((IData)(vlSelf->calc_mode)
                                                     ? 
                                                    (vlSelf->x 
                                                     + 
                                                     VL_SHIFTRS_III(21,21,4, vlSelf->y, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx)))
                                                     : 
                                                    (vlSelf->x 
                                                     - 
                                                     VL_SHIFTRS_III(21,21,4, vlSelf->y, (IData)(vlSelf->cordic__DOT__cordic_ins__DOT__iter_idx))))));
        vlSelf->cordic__DOT__z_out = (0x1fffffU & (vlSelf->z 
                                                   + vlSelf->cordic__DOT__cordic_ins__DOT__e_lut));
    }
}

void Vcordic___024root___eval(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vcordic___024root___sequent__TOP__0(vlSelf);
    }
    Vcordic___024root___combo__TOP__0(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

#ifdef VL_DEBUG
void Vcordic___024root___eval_debug_assertions(Vcordic___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcordic__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcordic___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->calc_mode & 0xfeU))) {
        Verilated::overWidthError("calc_mode");}
    if (VL_UNLIKELY((vlSelf->start & 0xfeU))) {
        Verilated::overWidthError("start");}
    if (VL_UNLIKELY((vlSelf->x_0 & 0xfff00000U))) {
        Verilated::overWidthError("x_0");}
    if (VL_UNLIKELY((vlSelf->y_0 & 0xfff00000U))) {
        Verilated::overWidthError("y_0");}
    if (VL_UNLIKELY((vlSelf->z_0 & 0xfff00000U))) {
        Verilated::overWidthError("z_0");}
}
#endif  // VL_DEBUG
