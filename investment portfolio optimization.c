#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void optimizePortfolio(int budget, int cost[], int profit[], char stockNames[][50], int n) {
    int dp[n + 1][budget + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (cost[i - 1] <= w)
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - cost[i - 1]], dp[i - 1][w]);  //max(selected profit, not selected)
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int maxProfit = dp[n][budget];
    printf("\nMaximum Possible Profit: Rs.%d\n", maxProfit);

    printf("\nSelected Stocks:\n");
    printf("+--------+----------------+------------+------------+\n");
    printf("| Index  | Stock Name     | Investment | Profit     |\n");
    printf("+--------+----------------+------------+------------+\n");

    int w = budget;
    for (int i = n; i > 0 && maxProfit > 0; i--) {
        if (maxProfit != dp[i - 1][w]) {
            printf("|   %-4d  | %-14s |   %-8d |   %-8d |\n", i - 1, stockNames[i - 1], cost[i - 1], profit[i - 1]);
            maxProfit -= profit[i - 1];
            w -= cost[i - 1];
        }
    }
    printf("+--------+----------------+------------+------------+\n");
}

int main() {
    int budget, n;

    printf("Enter your total investment budget: ");
    scanf("%d", &budget);
    printf("Enter the number of available stocks: ");
    scanf("%d", &n);

    int cost[n], profit[n];
    char stockNames[n][50];

    printf("\nEnter details for each stock:\n");
    for (int i=0; i < n; i++) {
        printf("Stock %d - Name: ", i);
        getchar();
        fgets(stockNames[i], sizeof(stockNames[i]), stdin);
        stockNames[i][strcspn(stockNames[i], "\n")] = '\0';

        printf("Stock %d - Cost: ", i);
        scanf("%d", &cost[i]);
        printf("Stock %d - Profit: ", i);
        scanf("%d", &profit[i]);
    }

    optimizePortfolio(budget, cost, profit, stockNames, n);

    return 0;
}
