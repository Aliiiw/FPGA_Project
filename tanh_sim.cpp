#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstdint>

#include "Vcordic.h"
#include "verilated.h"

// Fixed-point parameters and constants
#define FIXED_MAX_POS 0x1FFFF // Maximum positive 20‐bit value
#define FIXED_MAX_NEG 0x20000 // Maximum negative value mask
#define ITER_COUNT 20         // Number of iterations (only first 16 LUT entries provided)
#define GAIN_K 0.82816f       // Gain constant for hyperbolic mode
#define INV_HYP_GAIN (1.0f / GAIN_K)
#define FIX_SCALE 262144 // 2^18: scaling factor for Q2.18
#define FIX_TO_FLT (1.0f / 262144.0f)

// Operation modes
#define MODE_HYP 0 // Hyperbolic rotation mode (for sinh/cosh)
#define MODE_LIN 1 // Linear vectoring mode (for tanh)

// Lookup tables (only 16 entries provided; remaining iterations unused)
uint32_t linearLUT[ITER_COUNT] = {
    0x3FFFF, 0x1FFFF, 0x0FFFF, 0x07FFF,
    0x03FFF, 0x01FFF, 0x00FFF, 0x007FF,
    0x003FF, 0x001FF, 0x000FF, 0x0007F,
    0x0003F, 0x0001F, 0x0000F, 0x00007};

uint32_t atanhLUT[ITER_COUNT] = {
    0x232D2, 0x1054E, 0x0802A, 0x04001,
    0x02000, 0x01000, 0x00800, 0x00400,
    0x00200, 0x00100, 0x00080, 0x00040,
    0x00020, 0x00010, 0x00000, 0x00000};

uint8_t hyperIdxLUT[ITER_COUNT] = {
    1, 2, 3, 4, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 13, 14};

// Extend a 20-bit fixed-point value to a 32-bit signed integer.
int32_t signExtend20(uint32_t val)
{
    if (val & (1 << 20))
    { // If the 21st bit is set, number is negative.
        return (int32_t)(val | 0xFFF00000);
    }
    else
    {
        return (int32_t)(val & 0x001FFFFF);
    }
}

// Structure holding the CORDIC variables.
struct CordicValues
{
    int32_t x;
    int32_t y;
    int32_t z;
};

typedef struct CordicValues CordicVars;

// Global instance of the CORDIC hardware module.
Vcordic *gCordic = new Vcordic;

// Toggle the CORDIC clock for one full cycle.
void tickClock()
{
    gCordic->clk = 0;
    gCordic->eval();
    gCordic->clk = 1;
    gCordic->eval();
}

// Run the hardware CORDIC loop and return the result.
CordicVars runHardwareCordic(CordicVars initVals, uint8_t mode)
{
    gCordic->reset = 1;
    tickClock();

    gCordic->reset = 0;
    gCordic->calc_mode = mode;
    // Sign-extend the provided 20-bit values to 32 bits.
    gCordic->x_0 = (initVals.x << 12) >> 12;
    gCordic->y_0 = (initVals.y << 12) >> 12;
    gCordic->z_0 = (initVals.z << 12) >> 12;
    gCordic->start = 1;
    tickClock();
    gCordic->start = 0;

    // Wait until the hardware module is finished.
    while (gCordic->busy == 1)
    {
        tickClock();
    }

    CordicVars hwResult;
    hwResult.x = signExtend20(gCordic->x);
    hwResult.y = signExtend20(gCordic->y);
    hwResult.z = signExtend20(gCordic->z);
    return hwResult;
}

// Display the results in human–readable format.
void displayResults(CordicVars vals, uint8_t mode)
{
    if (mode == MODE_HYP)
    {
        // Scale the outputs back with the inverse gain.
        vals.x = (int32_t)((float)vals.x * INV_HYP_GAIN);
        vals.y = (int32_t)((float)vals.y * INV_HYP_GAIN);
        // printf("\tsinh = %f (0x%04hx), cosh = %f (0x%04hx)\n",
        //        (float)vals.y * FIX_TO_FLT, (int16_t)vals.y,
        //        (float)vals.x * FIX_TO_FLT, (int16_t)vals.x);
    }
    else if (mode == MODE_LIN)
    {
        printf("\ttanh = %f (0x%04hx)\n",
               (float)vals.z * FIX_TO_FLT, (int16_t)vals.z);
    }
}

// Software implementation of the CORDIC algorithm.
CordicVars runSoftwareCordic(CordicVars startVals, uint8_t mode)
{
    int32_t X = startVals.x;
    int32_t Y = startVals.y;
    int32_t Z = startVals.z;

    for (int i = 0; i < ITER_COUNT; i++)
    {
        int32_t prevX = X;
        int32_t prevY = Y;
        int32_t prevZ = Z;
        if (mode == MODE_LIN)
        {
            if (prevY < 0)
            {
                X = prevX;
                Y = prevY + (prevX / (1 << i));
                Z = prevZ - linearLUT[i];
            }
            else
            {
                X = prevX;
                Y = prevY - (prevX / (1 << i));
                Z = prevZ + linearLUT[i];
            }
        }
        else if (mode == MODE_HYP)
        {
            int shiftVal = hyperIdxLUT[i];
            if (prevZ < 0)
            {
                X = prevX - (prevY / (1 << shiftVal));
                Y = prevY - (prevX / (1 << shiftVal));
                Z = prevZ + atanhLUT[shiftVal];
            }
            else
            {
                X = prevX + (prevY / (1 << shiftVal));
                Y = prevY + (prevX / (1 << shiftVal));
                Z = prevZ - atanhLUT[shiftVal];
            }
        }
    }
    CordicVars swResult = {X, Y, Z};
    return swResult;
}

// Perform both software and hardware CORDIC calculations and print the outcomes.
CordicVars performCalculation(CordicVars inputVals, uint8_t mode)
{
    // printf("Software result:\n");
    // CordicVars swRes = runSoftwareCordic(inputVals, mode);
    // displayResults(swRes, mode);

    printf("result: ");
    CordicVars hwRes = runHardwareCordic(inputVals, mode);
    displayResults(hwRes, mode);

    return hwRes;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <angle as float between -2 and 2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse the input angle.
    float angleVal = strtof(argv[1], nullptr);
    if (angleVal < -2.0f || angleVal > 2.0f)
    {
        printf("Error: Angle must be between -2 and 2.\n");
        return EXIT_FAILURE;
    }

    // Convert the angle to Q2.18 fixed–point format.
    int32_t fixedAngle = (int32_t)round(angleVal * FIX_SCALE);

    // Prepare input for hyperbolic rotation (sinh/cosh computation)
    CordicVars hypInput;
    hypInput.x = FIXED_MAX_POS; // Starting approximation for cosh
    hypInput.y = 0;             // Starting value for sinh
    hypInput.z = fixedAngle;    // Angle in fixed–point

    CordicVars hypResult = performCalculation(hypInput, MODE_HYP);

    // Prepare input for linear vectoring (tanh computation)
    CordicVars linInput;
    linInput.x = hypResult.x; // Use cosh from hyperbolic result
    linInput.y = hypResult.y; // Use sinh from hyperbolic result
    linInput.z = 0;           // Initialize z to zero

    printf("Reference: tanh(%f) = %f\n", angleVal, tanh(angleVal));
    printf("Computing tanh (linear vectoring mode):\n");
    CordicVars linResult = performCalculation(linInput, MODE_LIN);

    return EXIT_SUCCESS;
}