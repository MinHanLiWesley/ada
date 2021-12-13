

with open("t.in", 'r') as f1:
    with open("wesley.out", 'r') as f2:
        with open("yian.out", 'r') as f3:
            with open("wesley2.in", 'w') as f4:
                with open("yian2.in", 'w') as f5:
                    Line1 = f1.readline()
                    T, flag = list(map(int,Line1.split()))
                    f4.write(f"{T} {flag}\n")
                    f5.write(f"{T} {flag}\n")
                    for _ in range(T):
                        Line1 = f1.readline()
                        N, M = list(map(int,Line1.split(" ")))
                        edges1 = []
                        for _ in range(M):
                            Line1 = f1.readline()
                            edges1.append(list(map(int,Line1.split(" "))))
                        edges_wesley = edges1.copy()
                        edges_yian = edges1.copy()
                        Mwes = int(f2.readline())
                        for _ in range(Mwes):
                            Linewes = f2.readline()
                            edges_wesley.append(list(map(int,Linewes.split(" "))))
                        Mwes += M
                        Myian = int(f3.readline())
                        for _ in range(Myian):
                            Lineyian = f3.readline()
                            edges_yian.append(list(map(int,Lineyian.split(" "))))
                        Myian += M

                        f4.write(f"{N} {Mwes}\n")
                        for i in edges_wesley:
                            f4.write(f"{i[0]} {i[1]}\n")

                        f5.write(f"{N} {Myian}\n")
                        for i in edges_yian:
                            f5.write(f"{i[0]} {i[1]}\n")
