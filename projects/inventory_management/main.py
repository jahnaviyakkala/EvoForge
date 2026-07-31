from inventory_management import Inventory_management

def main():
    obj = Inventory_management('demo')
    obj.set_value('status', 'active')
    print('Status:', obj.get_value('status'))

if __name__ == '__main__':
    main()
