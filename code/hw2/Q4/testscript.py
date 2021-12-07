# -*- coding: utf-8 -*-
"""
Created on Tue Oct  5 15:04:22 2021

@author: Wesley
"""
import random
from itertools import combinations

def check_rule(we,n):
    if n == 0:
        return False
    if n== 1:
        return True
    for i in range(n-1):
        if (we[i] * we[i+1]) < 0:
            return False
    return True
    

if __name__ == '__main__':
    
    T = 10
    flag = 0
    print(f"{T} {flag}")
    with open("ans.txt",'w') as f:
        for cnt in range(T):
            input = []
            input_idx=[]
            n = 20
            for i in range(n):
                while(1):
                    tmp = random.randint(-20,20)
                    if tmp !=0:
                        break
                input.append(tmp)
                input_idx.append(i)
            print(len(input))
            print(" ".join(map(str,input)))
            # output = sum([list(map(list, combinations(input, i))) for i in range(len(input) + 1)], [])
            # # print(output)
            # a = len(output)
            # a-=1
            # remove_lst=[]
            # for i in range(a):
            #     # print(i)
            #     # print(output[i])
            #     if  check_rule(output[i],len(output[i])):
            #         remove_lst.append(i)
            
            # new_input =[]
            # for idx in remove_lst:
            #     new_input.append(output[idx])
            # # print(new_input)
            
            # Max_sum = -1000000
            # final_lst = []
            # for lst in new_input:
            #     if (Max_sum < sum(lst)):
            #         Max_sum = sum(lst)
            #         final_lst = lst
            
            # f.write(f"{Max_sum}\n")
            # if flag == 1:
            #     f.write(f"{len(final_lst)} ")
            #     f.write(" ".join(map(str,final_lst)))
            #     f.write("\n")
