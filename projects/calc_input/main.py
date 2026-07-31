from calculator import add, subtract, multiply, divide, power, square_root

def main():
    print('Calculator Demo:')
    print('10 + 5 =', add(10, 5))
    print('10 - 5 =', subtract(10, 5))
    print('10 * 5 =', multiply(10, 5))
    print('10 / 5 =', divide(10, 5))
    print('2 ^ 3 =', power(2, 3))
    print('sqrt(16) =', square_root(16))

if __name__ == '__main__':
    main()
