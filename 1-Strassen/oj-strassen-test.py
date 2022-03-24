import math
s1 = """
11 4
1075 1970 1026 1577 
615 1791 1040 378 
381 1821 779 1238 
79 289 284 566 
1541 223 512 117 
13 1615 1823 1529 
1782 397 1975 1823 
519 666 1435 778 
420 1432 993 1842 
1683 1089 947 571 
1567 709 1912 848
"""

s2 = """
4 28 
457 71 1941 1563 386 1354 1042 840 326 481 1915 1240 502 145 374 450 1975 1139 1199 533 1829 1029 1019 1311 510 1019 1223 356 
647 1560 267 319 508 282 1338 160 797 1079 1982 70 1242 1504 121 463 1789 590 1713 553 646 603 1070 557 1894 511 434 1499 
1434 1566 221 397 845 184 1425 1466 27 873 730 577 880 460 122 504 1325 1072 938 466 603 797 1104 1925 1092 1382 275 889 
1771 891 371 390 1047 569 477 761 653 552 1894 233 1865 1438 1160 163 1271 1940 841 839 1367 195 624 456 57 581 1098 429
"""

def main():
    A = create(s1)
    B = create(s2)

    print(A)
    print(B)

    r1 = len(A)
    c1 = len(A[0])

    # print(r1, c1)

    r2 = len(B)
    c2 = len(B[0])

    # print(r2, c2)

    # Result matrix size: r1 c2
    M = multiply(r1, c1, A, r2, c2, B)
    print(M)

    r3 = len(M)
    c3 = len(M[0])
    print(r3, c3)

    # OK Here is my thought
    # Step 1: Find the greatest number in r1 c1 r2 c2, lets call it N
    # Step 2: Find the closest 2^n thats greater than the N
    # Step 3: Make A and B into square matrix with size N x N and pad the new entries with 0
    # ---
    # Hope this will work

    N = findGreatest(r1, c2, r2, c2)
    N = findClosest(N)
    print(N)

    A = padMatrix(r1, c1, A, N)
    B = padMatrix(r2, c2, B, N)

    print(A)
    print(B)

    # M2 = multiply(r1, c1, A, r2, c2, B)
    M2 = multiply(N, N, A, N, N, B)
    print(M2)
    
    # M2 is 32x32 matrix and it will return False
    print(M == M2)
    
    # What if we pad 0 to M and compare? It returns True
    print(padMatrix(r3, c3, M, N) == M2)

    # Result: The method above works

def padMatrix(r, c, M, N):
    M2 = [[0 for _ in range(N)] for _ in range(N)]
    for y in range(N):
        for x in range(N):
            # Still in original size's range
            if (y < r and x < c):
                M2[y][x] = M[y][x]
            
            else:
                M2[y][x] = 0
    
    return M2

# https://math.stackexchange.com/questions/3381728/find-closest-power-of-2-to-a-specific-number

def findClosest(N):
    n = math.log(N, 2)
    n = math.ceil(n)

    n = math.pow(2, n)
    n = int(n)
    return n

def findGreatest(r1, c1, r2, c2):
    maxR = max(r1, r2)
    maxC = max(c1, c2)
    
    N = max(maxR, maxC)
    return N

def create(s):
    l = [i for i in s.split("\n") if (i != "")]
    
    size = l.pop(0)
    size = size.split(" ")
    
    # x dir
    row = int(size[0])

    # y dir
    col = int(size[1])

    M = [[0 for _ in range(col)] for _ in range(row)]

    for y, line in enumerate(l):
        nums = [int(i) for i in line.split(" ") if (i != "")]
        for x, n in enumerate(nums):
            M[y][x] = n

    return M

def multiply(r1, c1, A, r2, c2, B):
    M = [[0 for _ in range(c2)] for _ in range(r1)]
    for x in range(r1):
        for y in range(c2):
            for z in range(r2):
                M[x][y] += A[x][z] * B[z][y]
    return M


if (__name__ == "__main__"):
    main()