import math
from dataclasses import dataclass
from typing import Final, Set, Tuple


@dataclass(frozen=True)
class CordicOutput:
    """Holds the output of the CORDIC tanh calculation."""

    tanh: float
    int_bits: int
    frac_bits: int
    iterations: int


class TanhCordic:
    """
    Computes hyperbolic tangent using the CORDIC algorithm with iterative refinement.
    """

    EPSILON_MIN: Final[float] = 1e-10
    START_ITER: Final[int] = -3
    MAX_ITER: Final[int] = 14
    SPECIAL_STEPS: Final[Set[int]] = {4, 13}

    def __init__(self, max_val: float, tol: float) -> None:
        """
        Initialize the CORDIC tanh calculator.

        Args:
            max_val (float): The maximum absolute input value.
            tol (float): The required precision for the tanh output.
        """
        self.max_val = abs(max_val)
        self.tol = abs(tol)
        self.int_bits = self._required_bits(self.max_val)
        self.frac_bits = self._required_bits(1.0 / (2 * self.tol))

    @staticmethod
    def _required_bits(num: float) -> int:
        """Determine the number of bits needed to represent the given number."""
        return math.ceil(math.log2(num + 1))

    @staticmethod
    def _delta(factor: float) -> float:
        """
        Compute the delta for z using the given factor.

        Returns:
            The computed delta using atanh; if an error occurs, returns a minimum value.
        """
        try:
            return math.atanh(factor)
        except ValueError:
            return TanhCordic.EPSILON_MIN

    def _iteration_params(self, idx: int) -> Tuple[int, float]:
        """
        Determine the parameters for the current iteration.

        Args:
            idx (int): The current iteration index.

        Returns:
            A tuple (shift, scaling) where shift is the bit-shift value and scaling is 1/(2^shift).
        """
        shift_val = -(idx - 2) if idx < 1 else idx
        return shift_val, 1.0 / (1 << shift_val)

    def compute_tanh(self, z_initial: float) -> CordicOutput:
        """
        Calculate the hyperbolic tangent using iterative CORDIC steps.

        Args:
            z_initial (float): The input value for which tanh is calculated.

        Returns:
            CordicOutput: Contains the tanh result and the bit precision and iteration count.
        """
        x, y = 1.0, 0.0
        z = z_initial
        current_iter = self.START_ITER
        iter_count = 0

        special_tracker = {step: 0 for step in self.SPECIAL_STEPS}
        last_tanh = 0.0
        error = float("inf")

        while current_iter <= self.MAX_ITER and error > self.tol:
            shift, scale = self._iteration_params(current_iter)
            delta_z = self._delta(scale)

            if z >= 0:
                new_x = x + y * scale
                new_y = y + x * scale
                z -= delta_z
            else:
                new_x = x - y * scale
                new_y = y - x * scale
                z += delta_z

            x, y = new_x, new_y
            tanh_est = y / x if abs(x) > self.EPSILON_MIN else math.copysign(1.0, y)

            if iter_count > 0:
                error = abs(tanh_est - last_tanh)
            last_tanh = tanh_est
            iter_count += 1

            if current_iter in special_tracker and special_tracker[current_iter] < 1:
                special_tracker[current_iter] += 1
            else:
                current_iter += 1

        return CordicOutput(
            tanh=last_tanh,
            int_bits=self.int_bits,
            frac_bits=self.frac_bits,
            iterations=iter_count,
        )


def main() -> None:
    """Main routine to run the CORDIC-based tanh calculation."""
    max_input = float(input("Enter maximum absolute value for input (z): "))
    precision = float(input("Enter desired precision (epsilon): "))

    calculator = TanhCordic(max_input, precision)
    result = calculator.compute_tanh(max_input)

    print("\nResults:")
    print(f"Integer bits required: {result.int_bits}")
    print(f"Fractional bits required: {result.frac_bits}")
    print(f"Iterations performed: {result.iterations}")
    print(f"Calculated tanh: {result.tanh}")


if __name__ == "__main__":
    main()
