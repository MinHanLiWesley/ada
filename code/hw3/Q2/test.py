from random import randint

with open ("t.in",'w') as f:
    T=3
    N_in=10
    flag=1
    f.write(f"{T} {flag}\n")
    for _ in range(T):
        # N = randint(1,N_in)
        N = N_in
        M = randint(0,min(1000,N*(N-1)))
        f.write(f"{N} {M}\n")
        edge = []
        for _ in range(M):
            while(1):
                u = randint(1,N)
                while(1):
                    v = randint(1,N)
                    if (v != u):
                        break
                if([u,v] not in edge):
                    edge.append([u,v])
                    break
            f.write(f"{u} {v}\n")
