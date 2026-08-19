from calc import Calc

def main():
    obj = Calc('demo')
    obj.set_value('status', 'active')
    print('Status:', obj.get_value('status'))

if __name__ == '__main__':
    main()
