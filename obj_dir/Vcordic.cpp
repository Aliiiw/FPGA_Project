// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcordic.h"
#include "Vcordic__Syms.h"

//============================================================
// Constructors

Vcordic::Vcordic(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vcordic__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , reset{vlSymsp->TOP.reset}
    , calc_mode{vlSymsp->TOP.calc_mode}
    , start{vlSymsp->TOP.start}
    , busy{vlSymsp->TOP.busy}
    , x_0{vlSymsp->TOP.x_0}
    , y_0{vlSymsp->TOP.y_0}
    , z_0{vlSymsp->TOP.z_0}
    , x{vlSymsp->TOP.x}
    , y{vlSymsp->TOP.y}
    , z{vlSymsp->TOP.z}
    , rootp{&(vlSymsp->TOP)}
{
}

Vcordic::Vcordic(const char* _vcname__)
    : Vcordic(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vcordic::~Vcordic() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vcordic___024root___eval_initial(Vcordic___024root* vlSelf);
void Vcordic___024root___eval_settle(Vcordic___024root* vlSelf);
void Vcordic___024root___eval(Vcordic___024root* vlSelf);
#ifdef VL_DEBUG
void Vcordic___024root___eval_debug_assertions(Vcordic___024root* vlSelf);
#endif  // VL_DEBUG
void Vcordic___024root___final(Vcordic___024root* vlSelf);

static void _eval_initial_loop(Vcordic__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vcordic___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vcordic___024root___eval_settle(&(vlSymsp->TOP));
        Vcordic___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vcordic::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcordic::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcordic___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vcordic___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

VerilatedContext* Vcordic::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vcordic::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vcordic::final() {
    Vcordic___024root___final(&(vlSymsp->TOP));
}
