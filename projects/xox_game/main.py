from xox_game import Xox_game

def main():
    obj = Xox_game('demo')
    obj.set_value('status', 'active')
    print('Status:', obj.get_value('status'))

if __name__ == '__main__':
    main()
