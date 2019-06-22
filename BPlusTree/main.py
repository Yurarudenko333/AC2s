from BPlusTree import BPlusTree
from BPlusTree.BPlusTree import BPlusDot
from BPlusTree import random_data_gen
from MyType.MyType import Product

def test1():
    T = BPlusDot(2)
    random_data_gen.gen(20)
    with open('input_data\small-data.txt','r') as fin:
        for line in fin:
            key,value = line.split(' ')
            T.insert(int(key),value.rstrip())

    T.print_viz()

def test2():
    tree = BPlusTree.BPlusDot(3)

    for i in range(40):
        tree.insert(i,i)
    tree.print_viz()
    for i in range(40):
        #i = 8 error
        tree.delete(i)
        if i > 5:
            tree.print_viz()



def test3():
    product_lst = Product.get_data()

    tree = BPlusDot(5)
    for p in product_lst:
        tree[p.price] = p

    tree.print_viz()
    tree.delete(5.5)
    tree.delete(6.0)
    input()
    tree.print_viz()


if __name__ == "__main__":
    test1()