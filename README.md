# FPGA Project

FPGA Project is a Verilog implementation of a small fixed-point neural-network inference pipeline. The project combines a CORDIC-based `tanh` activation unit with reusable arithmetic blocks and a multi-layer perceptron wired for simulation with Verilator.

## What is inside

- `cordic.v`, `cordic_calc.v` - iterative CORDIC engine and per-iteration calculation logic.
- `cordic_tanh.v` - wraps the CORDIC core to compute `tanh(x)` by first producing `sinh/cosh` in hyperbolic rotation mode and then dividing them in linear vectoring mode.
- `single_neuron.v` - accumulates fixed-point input/weight products and applies the CORDIC tanh activation.
- `mlp_network.v` - a 3-layer MLP controller with 3 inputs, a 5-neuron first layer, a 3-neuron second layer, and a final output neuron.
- `adder.v`, `multiplier.v` - parameterized fixed-point arithmetic blocks used by the neuron pipeline.
- `layer1_weights.v`, `layer2_weights.v`, `layer3_weights.v` - generated 20-bit ROM modules that store the network weights.
- `test_mlp.cpp`, `test_single_neuron.cpp`, `tanh_sim.cpp` - C++/Verilator test benches for the MLP, neuron, and CORDIC/tanh flow.
- `ram_module_generator.py`, `luts_generator.py`, `test_generator.py`, `Iteration_bit_calculation.py` - helper scripts for generating weight ROMs, CORDIC lookup tables, fixed-point test vectors, and iteration/precision estimates.
- `FPGA-Project.pdf` - project report/documentation.

## Design Overview

The design uses 20-bit signed fixed-point values, with the main simulation code treating values as Q2.18. Each neuron multiplies every input by its corresponding weight, accumulates the result, and feeds the sum into the `cordic_tanh` activation module.

The MLP controller starts each layer, waits for all neurons in that layer to finish, and then forwards the generated activations to the next layer. The final output is reduced to a binary classification by checking the sign bit of the final neuron output.

## CORDIC Tanh Flow

`cordic_tanh.v` coordinates two CORDIC passes:

1. Hyperbolic rotation mode computes approximations of `sinh(x)` and `cosh(x)`.
2. Linear vectoring mode computes the ratio `sinh(x) / cosh(x)`, producing `tanh(x)`.

The lookup tables and special hyperbolic iteration indexes are embedded in `cordic_calc.v`, while `luts_generator.py` can be used to regenerate LUT values for experimentation.

## Simulation

The repository includes a Makefile for building the MLP simulation with Verilator:

```sh
make
./test_mlp
```

To remove generated simulation output:

```sh
make clean
```

The Makefile is configured for an Apple Silicon/macOS-style toolchain with `-arch arm64`. If you use a different platform, you may need to adjust `CXXFLAGS` and `LDFLAGS`.

## Helper Scripts

Generate Verilog weight ROM modules:

```sh
python3 ram_module_generator.py
```

Generate CORDIC lookup table snippets:

```sh
python3 luts_generator.py
```

Generate fixed-point tanh input/output vectors:

```sh
python3 test_generator.py
```

Estimate bit width and iteration requirements for a requested input range and tolerance:

```sh
python3 Iteration_bit_calculation.py
```

## Generated Files

This repository also contains generated Verilator artifacts under `obj_dir/` and a compiled `test_mlp` binary. They reflect a previous local simulation build and are not required to understand or modify the source design.
