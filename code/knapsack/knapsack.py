def knapSack(W, wt, val, n):
    K = [[0 for x in range(W+1)] for x in range(n+1)]

    # Build table K[][] in bottom up manner
    for i in range(n+1):
        print('\n')
        for w in range(W+1):
            if i==0 or w==0:
                K[i][w] = 0
            elif wt[i-1] <= w:
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w])
            else:
                K[i][w] = K[i-1][w]
            print(f' {K[i][w]}',end = '')

    return K[n][W]

# Driver program to test above function
val = [9, 5, 5]
wt = [3, 2, 2]
W = 4
n = len(val)
print(f'\nResult: {knapSack(W, wt, val, n)}')
