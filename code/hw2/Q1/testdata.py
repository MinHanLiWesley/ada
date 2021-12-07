import random

def gen_data(data : list, limit_m : int, limit_n : int, limit_k : int):
	m = random.randint(1, limit_m)
	n = random.randint(1, limit_n)
	while(m == 1 and n == 1):
		m = random.randint(1, limit_m)
		n = random.randint(1, limit_n)
	k = random.randint(1, limit_k)
	
	res = str(m)
	res = res + " " + str(n)
	res = res + " " + str(k) + "\n"
	for i in range(m):
		for j in range(n):
			if(i == 0 and j == 0):
				if j != n-1:
					res += "0 "
				else:
					res += "0\n"
			elif(i == m-1 and j == n-1):
				res += "0\n"
			elif(j == n-1):
				if(random.randint(1, 100) <= 45):
					res += "X\n"
				else:
					res += str(random.randint(-50, 50))+"\n"
			else:
				if(random.randint(1, 100) <= 45):
					res += "X "
				else:
					res += str(random.randint(-50, 50))+" "
			
	data.append(res)
	return data




if __name__ == '__main__':
	t = int(input())
	limit_m = int(input())
	limit_n = int(input())
	limit_k = int(input())
	data = []
	data.append(str(t)+"\n")
	for i in range(t):
		gen_data(data, limit_m, limit_n, limit_k)
	
	for i in range(len(data)):
		if i != len(data) - 1:
			print(data[i])
		else:
			print(data[i], end = "")
		