def ks(W,wt,val,n):
    dp = [[0 for i in range(W+1)] for j in range(n+1)]
    for i in range(1,n+1):
        for w in range(1,W+1):
            if wt[i-1]<=w:
                dp[i][w] = max(val[i-1]+dp[i-1][w-wt[i-1]],dp[i-1][w])
            else:
                dp[i][w] = dp[i-1][w]
    wgt = W
    picked = []
    print(dp)
    res = dp[n][W]
    for i in range(n,0,-1):
        if res<=0:
            break
        if res==dp[i-1][wgt]:
            continue
        else:
            picked.append(wt[i-1])
            res-=val[i-1]
            wgt-=wt[i-1]
    print("max value:",dp[n][W])
    print("Picked Items:",*picked)

val = [60, 100, 120]
wt = [10, 20, 30]
W = 50
n = len(val)
ks(W, wt, val, n)
