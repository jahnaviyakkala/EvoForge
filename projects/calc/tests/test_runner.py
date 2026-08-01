import unittest
from calculator import add, subtract, multiply, divide

class TestCalculator(unittest.TestCase):

    def test_add(self):
        self.assertEqual(add(1.0, 2.0), 3.0)
        self.assertEqual(add(-1.0, -1.0), -2.0)
        self.assertEqual(add(0.0, 0.0), 0.0)

    def test_subtract(self):
        self.assertEqual(subtract(5.0, 3.0), 2.0)
        self.assertEqual(subtract(-1.0, -1.0), 0.0)
        self.assertEqual(subtract(0.0, 0.0), 0.0)

    def test_multiply(self):
        self.assertEqual(multiply(4.0, 2.0), 8.0)
        self.assertEqual(multiply(-1.0, -1.0), 1.0)
        self.assertEqual(multiply(0.0, 5.0), 0.0)

    def test_divide(self):
        self.assertEqual(divide(6.0, 3.0), 2.0)
        self.assertEqual(divide(-4.0, 2.0), -2.0)
        self.assertEqual(divide(0.0, 1.0), 0.0)

    def test_divide_by_zero(self):
        with self.assertRaises(ValueError):
            divide(5.0, 0.0)

if __name__ == '__main__':
    unittest.main()
