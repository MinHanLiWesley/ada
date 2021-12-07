import random
from math import gcd
N = 10
print(N)
input = []
ans = -1
for i in range(10):
    input.append(random.randint(2, 2000000))
for i in range(10):
    print(f"{input[i]} ",end="")
print("")
# input = [2, 3, 4, 10, 9, 8, 7, 8, 8, 7]
# input = [6, 8, 2, 4, 10, 7, 3, 6, 14, 21]
# input = [7, 5, 2, 4, 10, 15, 3, 6, 14, 21]
# input=[7 ,10, 2, 9, 3, 7 ,8, 6, 6 ,9 ]
# input=[10 ,5 ,19, 6, 11, 5 ,20 ,20, 11 ,10 ]
# input=[4 ,7 ,7 ,11 ,11 ,10 ,15 ,12 ,18 ,16  ]
# 2 2 3 3
input1 = input.copy()

for a in range(9):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(input1_a[a], input1_a[a+1]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1])
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(7):
            input1_b = input1_a.copy()
            if (gcd(input1_b[b], input1_b[b+1]) > 1):
                ans1_b = ans1_a + gcd(input1_b[b], input1_b[b+1])
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(4):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(gcd(input1_c[c], input1_c[c+1]), input1_c[c+2]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) + \
                            gcd(input1_c[c+1], input1_c[c+2])
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(gcd(input1_c[0], input1_c[1]), input1_c[2]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1]) + \
                                gcd(input1_c[1], input1_c[2])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(f"ans:{ans}")
# print(ans)


# 2 3 2 3
for a in range(9):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(input1_a[a], input1_a[a+1]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1])
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(6):
            input1_b = input1_a.copy()
            if (gcd(gcd(input1_b[b], input1_b[b+1]), input1_b[b+2]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1]) + \
                    gcd(input1_b[b+1], input1_b[b+2])
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(4):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(input1_c[c], input1_c[c+1]) > 1):
                        ans1_c = ans1_b + gcd(input1_c[c], input1_c[c+1])
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(gcd(input1_c[0], input1_c[1]), input1_c[2]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1]) + \
                                gcd(input1_c[1], input1_c[2])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(ans)

# 2 3 3 2
for a in range(9):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(input1_a[a], input1_a[a+1]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1])
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(6):
            input1_b = input1_a.copy()
            if (gcd(gcd(input1_b[b], input1_b[b+1]), input1_b[b+2]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1]) + \
                    gcd(input1_b[b+1], input1_b[b+2])
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(3):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(gcd(input1_c[c], input1_c[c+1]), input1_c[c+2]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) + \
                            gcd(input1_c[c+1], input1_c[c+2])
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(input1_c[0], input1_c[1]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(ans)

# 3 2 3 2
for a in range(8):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(gcd(input1_a[a], input1_a[a+1]),input[a+2]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1]) + gcd(input1_a[a+1],input1_a[a+2])
        input1_a.pop(a)
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(6):
            input1_b = input1_a.copy()
            if (gcd(input1_b[b], input1_b[b+1]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1])
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(3):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(gcd(input1_c[c], input1_c[c+1]), input1_c[c+2]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) + \
                            gcd(input1_c[c+1], input1_c[c+2])
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(input1_c[0], input1_c[1]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(ans)

# 3 3 2 2
for a in range(8):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(gcd(input1_a[a], input1_a[a+1]),input[a+2]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1]) + gcd(input1_a[a+1],input1_a[a+2])
        input1_a.pop(a)
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(5):
            input1_b = input1_a.copy()
            if (gcd(gcd(input1_b[b], input1_b[b+1]), input1_b[b+2]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1]) + gcd(input1_b[b+1], input1_b[b+2])
                print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(3):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(input1_c[c], input1_c[c+1]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) 
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(input1_c[0], input1_c[1]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(ans)

# 3 2 2 3
for a in range(8):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(gcd(input1_a[a], input1_a[a+1]),input[a+2]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1]) + gcd(input1_a[a+1],input1_a[a+2])
        input1_a.pop(a)
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(6):
            input1_b = input1_a.copy()
            if (gcd(input1_b[b], input1_b[b+1]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1]) 
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(4):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(input1_c[c], input1_c[c+1]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) 
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        if(gcd(gcd(input1_c[0], input1_c[1]), input1_c[2]) > 1):
                            ans1_d = ans1_c + \
                                gcd(input1_c[0], input1_c[1]) + \
                                gcd(input1_c[1], input1_c[2])
                            # print(ans1_d)
                            # print("end")
                            ans = max(ans, ans1_d)
# print(ans)

# 2 2 2 2 2
for a in range(9):
    # print("new")
    ans1 = 0
    input1_a = input1.copy()
    if (gcd(input1_a[a], input1_a[a+1]) > 1):
        # print(f"a:{a}")
        # print(ans1_a)
        ans1_a = ans1 + gcd(input1_a[a], input1_a[a+1])
        input1_a.pop(a)
        input1_a.pop(a)
        for b in range(7):
            input1_b = input1_a.copy()
            if (gcd(input1_b[b], input1_b[b+1]) > 1):
                ans1_b = ans1_a + \
                    gcd(input1_b[b], input1_b[b+1]) 
                # print(f"b:{b}")
                # print(ans1_b)
                input1_b.pop(b)
                input1_b.pop(b)
                for c in range(5):
                    input1_c = input1_b.copy()
                    # print(len(input1_c))
                    if(gcd(input1_c[c], input1_c[c+1]) > 1):
                        ans1_c = ans1_b + \
                            gcd(input1_c[c], input1_c[c+1]) 
                        # print(f"c:{c}")
                        # print(ans1_c)
                        input1_c.pop(c)
                        input1_c.pop(c)
                        for d in range(3):
                            input1_d = input1_c.copy()
                            if(gcd(input1_d[d], input1_d[d+1]) > 1):
                                ans1_d = ans1_c + \
                                    gcd(input1_d[d], input1_d[d+1])
                                input1_d.pop(d)
                                input1_d.pop(d)
                                if(gcd(input1_d[0], input1_d[1]) > 1):
                                    ans1_e = ans1_d + \
                                    gcd(input1_d[0], input1_d[1])
                                # print(ans1_d)
                                # print("end")
                                    ans = max(ans, ans1_e)
# print(f"\nans: {ans}")
with (open("ans.txt",'w')) as f:
    f.write(str(ans))
# print(f"\n{ans}")