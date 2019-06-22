class Product():
    """Class to represent products"""
    def __init__(self,name,amount,price,category):
        self.name = name
        self.amount = amount
        self.price = price
        self.category = category

    def __str__(self):
        return '{name=%s|amount=%s}' % (self.name,str(self.amount))
    @staticmethod
    def get_data():
        res = []
        with open('MyType/Products.txt','r') as fin:
            for chunk in iter(lambda: fin.readline(), ''):
                attributes = [x for x in chunk.rstrip().split(' ')]
                category = attributes[3]
                if category == 'pastry': category = pastry_lst
                elif category == 'fruits': category = fruits_lst
                else: category = vegetables_lst

                p = Product(attributes[0],int(attributes[1]),float(attributes[2]),category)
                category.append(p)
                res.append(p)

        return res

vegetables_lst = []
fruits_lst = []
pastry_lst = []