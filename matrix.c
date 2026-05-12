#include <stdio.h>
#include <limits.h>

#define MAX 100

int m[MAX][MAX];
int s[MAX][MAX];

void printOptimal(int i, int j)
{
    if(i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        printOptimal(i, s[i][j]);
        printOptimal(s[i][j] + 1, j);
        printf(")");
    }
}

int MatrixChainOrder(int p[], int n)
{
    int i, j, k, L, q;

    for(i = 1; i < n; i++)
        m[i][i] = 0;

    for(L = 2; L < n; L++)
    {
        for(i = 1; i < n - L + 1; i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;

            for(k = i; k <= j - 1; k++)
            {
                q = m[i][k] + m[k + 1][j]
                    + p[i - 1] * p[k] * p[j];

                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    return m[1][n - 1];
}

void printMTable(int n)
{
    int i, j;

    printf("\nM TABLE:\n\n");

    for(i = 1; i < n; i++)
    {
        for(j = 1; j < n; j++)
        {
            if(i > j)
                printf("   -   ");
            else
                printf("%7d ", m[i][j]);
        }
        printf("\n");
    }
}

void printSTable(int n)
{
    int i, j;

    printf("\nS TABLE:\n\n");

    for(i = 1; i < n; i++)
    {
        for(j = 1; j < n; j++)
        {
            if(i >= j)
                printf("   -   ");
            else
                printf("%7d ", s[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n, i;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];

    printf("Enter dimensions:\n");

    for(i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    int minCost = MatrixChainOrder(p, n + 1);

    printMTable(n + 1);
    printSTable(n + 1);

    printf("\nMinimum Scalar Multiplications = %d\n", minCost);

    printf("\nOptimal Parenthesization = ");
    printOptimal(1, n);

    return 0;
}
