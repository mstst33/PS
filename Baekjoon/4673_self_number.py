# Source: https://www.acmicpc.net/problem/4673

N = 10000
slist = [False for i in range(N)]

def d(n: int) -> int:
    tmp = n
    while tmp > 0:
        n += int(tmp % 10)
        tmp = int(tmp / 10)

    return n

def solve(n: int):
    if slist[n - 1]: return

    while n <= N:
        n = d(n)
        if n <= N and not slist[n - 1]:
            slist[n - 1] = True
        else:
            break

if __name__ == "__main__":
    for i in range(1, N + 1):
        solve(i)
    
    for i in range(N):
        if not slist[i]:
            print(i + 1)
