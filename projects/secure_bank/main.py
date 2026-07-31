from secure_bank import Secure_bank

def main():
    obj = Secure_bank('demo')
    obj.set_value('status', 'active')
    print('Status:', obj.get_value('status'))

if __name__ == '__main__':
    main()
