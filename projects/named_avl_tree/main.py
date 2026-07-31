from named_avl_tree import Named_avl_tree

def main():
    obj = Named_avl_tree('demo')
    obj.set_value('status', 'active')
    print('Status:', obj.get_value('status'))

if __name__ == '__main__':
    main()
