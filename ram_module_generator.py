import math
from typing import List


def float_to_fixed20(value: float) -> int:
    """Convert float to Q1.18 fixed-point format."""
    if value < -2.0 or value >= 2.0:
        raise ValueError("Value must be in range [-2, 2) for Q1.18 format")

    sign = 1 if value < 0 else 0
    scaled_value = int(round(abs(value) * (1 << 18)))

    if sign:
        scaled_value = (~scaled_value & 0x3FFFF) + 1
        scaled_value |= 0x80000

    return scaled_value & 0xFFFFF


def generate_verilog_ram(weights: List[float], filename: str) -> None:
    """Generate Verilog RAM module file from weights."""
    try:
        with open(f"{filename}.v", "w", newline="\n") as file:
            file.write(f"module {filename} (\n")
            file.write("    input [7:0] addr,\n")
            file.write("    output reg [19:0] dout\n")
            file.write(");\n\n")

            file.write("    reg [19:0] ram [255:0]; // 256 x 20-bit weights\n\n")

            file.write("    initial begin\n")
            for i, weight in enumerate(weights):
                fixed_value = float_to_fixed20(weight)
                ram_entry = f"        ram[{i}] = 20'h{fixed_value:05X};"
                file.write(f"{ram_entry}\n")
                print(ram_entry)

            file.write("    end\n\n")

            file.write("    always @(*) begin\n")
            file.write("        dout = ram[addr];\n")
            file.write("    end\n\n")

            file.write("endmodule\n")

        print(f"Verilog weight memory file {filename}.v generated successfully.")

    except IOError as e:
        print(f"Error writing to file {filename}.v: {e}")


def main():
    """Main function to generate RAM modules."""
    weights_L1 = [
        0.2,
        -0.4,
        0.1,
        -0.5,
        0.7,
        -0.6,
        0.8,
        -0.1,
        0.3,
        -0.3,
        0.9,
        -0.8,
        0.6,
        -0.2,
        0.5,
    ]

    weights_L2 = [
        0.3,
        -0.2,
        0.5,
        -0.6,
        0.4,
        -0.7,
        0.6,
        -0.1,
        0.2,
        -0.8,
        0.4,
        -0.5,
        0.8,
        -0.9,
        0.7,
    ]

    weights_L3 = [0.1, -0.3, 0.2]

    filenames = ["layer1_weights", "layer2_weights", "layer3_weights"]

    for weights, filename in zip([weights_L1, weights_L2, weights_L3], filenames):
        generate_verilog_ram(weights, filename)


if __name__ == "__main__":
    main()
