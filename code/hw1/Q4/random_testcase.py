import random

T = 20
flag = 1

print(f"{T} {flag}")
N=20
cnt=0
while(cnt < N):
    input=[]
    for i in range(N):
        input.append(random.randint(-2000000000,2000000000))
        