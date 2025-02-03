import numpy as np
from dataclasses import dataclass
from typing import TextIO


@dataclass
class FixedPointConfig:
    """Configuration for fixed-point number representation"""

    int_bits: int
    frac_bits: int

    @property
    def total_bits(self) -> int:
        return self.int_bits + self.frac_bits


class FixedPointConverter:
    """Handles conversion between floating-point and fixed-point numbers"""

    def __init__(self, config: FixedPointConfig):
        self.config = config

    def float_to_fixed(self, value: float) -> int:
        """Convert floating-point number to fixed-point representation"""
        return int(value * (1 << self.config.frac_bits))

    def to_binary(self, value: int) -> str:
        """Convert fixed-point number to binary string with sign bit"""
        if value < 0:
            value = (1 << self.config.total_bits) + value
        return f"{value:0{self.config.total_bits}b}"


class TanhCalculator:
    """Handles tanh calculation and data generation"""

    def __init__(
        self,
        converter: FixedPointConverter,
        input_start: float = -1.0,
        input_end: float = 1.0,
        input_step: float = 0.01,
    ):
        self.converter = converter
        self.input_start = input_start
        self.input_end = input_end
        self.input_step = input_step

    def calculate_tanh(self, x: float) -> float:
        """Calculate tanh value for given input"""
        return np.tanh(x)

    def generate_test_data(self, input_file: TextIO, output_file: TextIO) -> int:
        """Generate test data and write to files"""
        test_count = 0
        x = self.input_start

        while x <= self.input_end:
            tanh_value = self.calculate_tanh(x)

            # Convert to fixed-point
            input_fixed = self.converter.float_to_fixed(x)
            output_fixed = self.converter.float_to_fixed(tanh_value)

            # Write binary representations
            input_file.write(f"{self.converter.to_binary(input_fixed)}\n")
            output_file.write(f"{self.converter.to_binary(output_fixed)}\n")

            x += self.input_step
            test_count += 1

        return test_count


def main():
    # Configuration
    config = FixedPointConfig(int_bits=2, frac_bits=16)
    converter = FixedPointConverter(config)
    calculator = TanhCalculator(converter)

    # Generate test data
    with open("input.txt", "w") as input_file, open("output.txt", "w") as output_file:
        num_tests = calculator.generate_test_data(input_file, output_file)

    print(f"Input and output files generated successfully! Num Of Tests = {num_tests}")


if __name__ == "__main__":
    main()
