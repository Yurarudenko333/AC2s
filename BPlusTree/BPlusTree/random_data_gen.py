import random

def gen(amount:int):
	num = amount
	ch_list = [chr(i) for i in range(ord('a'), ord('z') + 1)] 
	length = 15
	with open("input_data/small-data.txt", "w") as F:
		for i in range(num):
			key = random.randint(-1000000, 1000000)
			F.write(str(key))
			F.write(" " + "".join([random.choice(ch_list) for i in range(length)]) + "\n")

