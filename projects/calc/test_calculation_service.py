import unittest
from calculation_service import CalculationService

class TestCalculationService(unittest.TestCase):
    def setUp(self):
        self.calculation_service = CalculationService()

    def test_add(self):
        self.assertEqual(self.calculation_service.add(1, 2), 3)
        self.assertEqual(self.calculation_service.add(-1, -1), -2)

    def test_subtract(self):
        self.assertEqual(self.calculation_service.subtract(5, 3), 2)
        self.assertEqual(self.calculation_service.subtract(-1, 1), -2)

    def test_multiply(self):
        self.assertEqual(self.calculation_service.multiply(4, 3), 12)
        self.assertEqual(self.calculation_service.multiply(-2, -2), 4)

    def test_divide(self):
        self.assertEqual(self.calculation_service.divide(8, 2), 4)
        with self.assertRaises(ValueError):
            self.calculation_service.divide(5, 0)

if __name__ == "__main__":
    unittest.main()
