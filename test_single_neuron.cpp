#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <cstdint>

#include "Vsingle_neuron.h"  // Generated Verilog module
#include "verilated.h"

#define FIXED_POINT_TO_FLOAT (1.0f / 262144.0f)

vluint64_t global_time = 0;

const int kNumInputs = 4;  // Number of input signals

// Converts a floating–point value to Q1.18 fixed–point format (20-bit signed)
int convertToFixed(float value) {
    if (value < -2.0f || value >= 2.0f) {
        throw std::out_of_range("Value must be in the range [-2, 2) for Q1.18 representation.");
    }
    int32_t signFlag = (value < 0) ? 1 : 0;
    int32_t fixedVal = static_cast<int32_t>(std::round(std::fabs(value) * (1 << 18)));
    if (signFlag) {
        fixedVal = ((~fixedVal & 0x3FFFF) + 1);
        fixedVal |= 0x80000;
    }
    return fixedVal & 0xFFFFF;
}

// Software test: Compute and display products in fixed–point for reference.
void simulateSoftwareTest(const float inputVals[kNumInputs], const float weightVals[kNumInputs]) {
    float runningSum = 0.0f;
    for (int i = 0; i < kNumInputs; ++i) {
        runningSum += inputVals[i] * weightVals[i];
        std::cout << "Input: 0x" << std::hex << convertToFixed(inputVals[i])
                  << ", Weight: 0x" << std::hex << convertToFixed(weightVals[i])
                  << ", Product: 0x" << std::hex << convertToFixed(inputVals[i] * weightVals[i])
                  << std::dec << std::endl;
    }
}

// Runs the hardware test on the neuron module.
void executeHardwareTest(Vsingle_neuron *neuron, int maxCycles, int fixedInputs[kNumInputs], int fixedWeights[kNumInputs]) {
    // Assign the fixed–point inputs and weights to the module.
    for (int i = 0; i < kNumInputs; ++i) {
        neuron->inputs[i]  = fixedInputs[i];
        neuron->weights[i] = fixedWeights[i];
    }

    // Pulse the start signal to begin computation.
    neuron->start = 1;
    neuron->eval();
    neuron->clk = 1; neuron->eval();
    neuron->clk = 0; neuron->eval();
    neuron->start = 0;

    bool computationStarted = false;
    // Run the clock for a maximum number of cycles.
    for (int cycle = 0; cycle < maxCycles; ++cycle) {
        neuron->clk = 0; neuron->eval();
        ++global_time;

        neuron->clk = 1; neuron->eval();
        ++global_time;

        if (neuron->busy) {
            computationStarted = true;
        }
        if (computationStarted && !neuron->busy) {
            std::cout << "Global Time: " << global_time 
                      << ", Output: " << (neuron->output_value * FIXED_POINT_TO_FLOAT)
                      << " (" << neuron->output_value << " in decimal)" << std::endl;
            break;
        }
    }

    if (!computationStarted) {
        std::cerr << "ERROR: Neuron computation did not start. Check the Verilog module logic." << std::endl;
    }
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Vsingle_neuron *neuron = new Vsingle_neuron;

    // Define example floating–point values for inputs and weights.
    float floatInputs[kNumInputs]  = { 0.5f, -0.25f, 0.125f, 0.75f };
    float floatWeights[kNumInputs] = { 0.8f, -0.6f,  0.3f,  -0.9f };
    float biasValue = 0.1f;  // Bias value (unused in this example)

    int fixedInputs[kNumInputs], fixedWeights[kNumInputs];
    int fixedBias = convertToFixed(biasValue);

    // Convert the floating–point numbers to fixed–point representation.
    for (int i = 0; i < kNumInputs; ++i) {
        fixedInputs[i]  = convertToFixed(floatInputs[i]);
        fixedWeights[i] = convertToFixed(floatWeights[i]);
    }

    // Reset and initialize the neuron module.
    neuron->clk = 0;
    neuron->reset = 1;
    neuron->eval();

    neuron->clk = 1; neuron->eval();
    neuron->clk = 0; neuron->eval();
    neuron->reset = 0;

    ++global_time;

    // Execute the hardware test.
    executeHardwareTest(neuron, 50, fixedInputs, fixedWeights);

    // Run the software test for reference.
    simulateSoftwareTest(floatInputs, floatWeights);

    // Clean up.
    delete neuron;
    return 0;
}
