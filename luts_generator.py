import math
from typing import Final


def generate_atanh_lut(iter_num: int) -> None:
    """
    Generate Verilog lookup table for hyperbolic arctangent values.

    Args:
        iter_num (int): Number of iterations/entries in lookup table
    """
    SCALE_FACTOR: Final = 0x7FFFF  # 17-bit scale factor

    print("\n// Hyperbolic arctangent lookup table")
    print("function [16:0] atanh_lut([3:0] n);")
    print("    begin")
    print("        case (n)")

    for i in range(1, iter_num - 1):
        value = int(math.atanh(2**-i) * SCALE_FACTOR)
        print(f"            {i:2d}: atanh_lut = 17'h{value:05x};")

    print("            default: atanh_lut = 17'h00000;")
    print("        endcase")
    print("    end")
    print("endfunction")


def generate_linear_lut(iter_num: int) -> None:
    """
    Generate Verilog lookup table for linear scaling values.

    Args:
        iter_num (int): Number of iterations/entries in lookup table
    """
    SCALE_FACTOR: Final = 0x7FFFF  # 17-bit scale factor

    print("\n// Linear scaling lookup table")
    print("function [16:0] linear_lut([3:0] n);")
    print("    begin")
    print("        case (n)")

    for i in range(iter_num):
        value = int((2**-i) * SCALE_FACTOR)
        print(f"            {i:2d}: linear_lut = 17'h{value:05x};")

    print("        endcase")
    print("    end")
    print("endfunction")


def main() -> None:
    """Main function to generate both lookup tables."""
    try:
        iter_num = int(input("Enter number of iterations: "))

        generate_atanh_lut(iter_num)
        generate_linear_lut(iter_num)

    except ValueError as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()
