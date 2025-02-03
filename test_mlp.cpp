#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include "Vmlp_network.h"
#include "verilated.h"

constexpr int FIX_SCALE = 262144; // 2^18 scale factor for Q2.18
constexpr float SCALE_FACTOR = 1.0f / FIX_SCALE;

// Converts a float value to a signed 20‐bit Q2.18 fixed–point number.
int convertFloat(float num)
{
    bool isNeg = (num < 0.0f);
    // Multiply the absolute value by 2^18 and round to the nearest integer.
    int fixedVal = static_cast<int>(std::round(std::fabs(num) * (1 << 18)));
    if (isNeg)
    {
        // Compute two's complement within 20 bits for negative numbers.
        fixedVal = ((~fixedVal & 0x3FFFF) + 1);
        fixedVal |= 0x80000;
    }
    return fixedVal & 0xFFFFF;
}

// Converts a Q2.18 fixed–point number back to a float.
float convertBack(int fixedNum)
{
    return fixedNum * SCALE_FACTOR;
}

// Runs one simulation test case on the MLP module.
void simulateTest(Vmlp_network *top, const int32_t inVals[3], const char *testName)
{
    // Set the network inputs.
    for (int i = 0; i < 3; ++i)
    {
        top->network_inputs[i] = inVals[i];
    }

    // Initialize the DUT by asserting reset.
    top->reset = 1;
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
    top->reset = 0;
    top->clk = 0;
    top->eval();

    // Begin the computation by pulsing the start signal.
    top->start = 1;
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
    top->start = 0;
    top->clk = 0;
    top->eval();

    // Cycle the clock until the network is no longer busy, with a safeguard on cycle count.
    int cycleCount = 0;
    while ((top->network_busy) || (cycleCount < 2))
    {
        top->clk = !top->clk;
        top->eval();
        cycleCount++;
        if (cycleCount > 2000)
        {
            std::printf("Test \"%s\": exceeded 2000 cycles. Aborting...\n", testName);
            break;
        }
    }

    // Print test results.
    std::printf("Test: %s\n", testName);
    std::printf("Input values (hex): 0x%05X, 0x%05X, 0x%05X\n",
                inVals[0] & 0xFFFFF,
                inVals[1] & 0xFFFFF,
                inVals[2] & 0xFFFFF);
    std::printf("Network output classification: %d\n", top->network_output);
    std::printf("Total cycles: %d\n", cycleCount);
    std::printf("-------------------------------\n");
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    Vmlp_network *top = new Vmlp_network;

    // Define three test cases in Q2.18 fixed–point format.
    int32_t testCaseA[3] = {convertFloat(0.3f), convertFloat(0.1f), convertFloat(0.3f)};
    int32_t testCaseB[3] = {convertFloat(0.01f), convertFloat(0.2f), convertFloat(0.03f)};
    int32_t testCaseC[3] = {convertFloat(0.04f), convertFloat(0.9f), convertFloat(0.003f)};
    int32_t testCaseD[3] = {convertFloat(-0.99f), convertFloat(0.99f), convertFloat(-0.99f)};
    int32_t testCaseE[3] = {convertFloat(0.2f), convertFloat(0.2f), convertFloat(0.03f)};

    std::printf("Starting MLP Network Simulation\n");
    std::printf("================================\n");
    simulateTest(top, testCaseD, "Test -0.99 0.99 -0.99");
    simulateTest(top, testCaseE, "Test 0.2 0.2 0.03");

    delete top;
    return 0;
}
