import time

def CalcFibonacci(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return CalcFibonacci(n-1) + CalcFibonacci(n-2)
    

def CalcFibonacci2(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        a = 0
        b = 1
        for i in range(2, n+1):
            c = a + b
            a = b
            b = c
        return b

def main():
    # times = [5, 10, 20, 40]
    # for n in times:
    #     start = time.time()
    #     CalcFibonacci(n)
    #     end = time.time()
    #     print(end - start)

    print(CalcFibonacci2(999))


if __name__ == "__main__":
    main()