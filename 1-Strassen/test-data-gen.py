import random

def main():

    # c1 should == r2
    r1 = 8
    c1 = 8

    r2 = 8
    c2 = 8
    
    A = create(r1, c1)
    B = create(r2, c2)

    print(0)
    print(r1, c1)
    print("")
    printMatrix(A)

    print()
    print(r2, c2)
    print("")
    printMatrix(B)

    print("---")
    C = multiply(r1, c1, A, r2, c2, B)
    printMatrix(C, True)

def create(row, col):
    M = [[0 for _ in range(col)] for _ in range(row)]

    for y in range(row):
        for x in range(col):
            # M[y][x] = randInt(10, 1000)
            # M[y][x] = 1
            M[y][x] = x + y
    
    return M

def multiply(r1, c1, A, r2, c2, B):
    M = [[0 for _ in range(c2)] for _ in range(r1)]
    for x in range(r1):
        for y in range(c2):
            for z in range(r2):
                M[x][y] += A[x][z] * B[z][y]
    return M

def printMatrix(M, writeToFile=False):
    r = len(M)
    c = len(M[0])

    s = ""

    for y in range(r):
        for x in range(c):
            print(M[y][x], end=" ")
            s += f"{M[y][x]} "

        print("")
        s += "\n"
    
    if (writeToFile):
        import time
        timestamp = str(time.time()).split(".")[0]
        fileName = f"{timestamp}_output.txt"
        with open(fileName, "w+") as f:
            f.write(s)

def randInt(start, end):
    return int(random.randrange(start, end))

if (__name__ == "__main__"):
    main()

