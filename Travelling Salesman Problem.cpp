
#include <iostream>
#include <algorithm>
using namespace std;

#define INF 999999

int main()
{
    int n;

    cout << "Enter number of cities (max 15): ";
    cin >> n;

    if (n < 2 || n > 15)
    {
        cout << "Please enter between 2 and 15 cities.";
        return 0;
    }

    int cost[15][15];

    cout << "Enter the cost matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    int totalMasks = 1 << n;
    int dp[1 << 15][15];

    for (int mask = 0; mask < totalMasks; mask++)
        for (int i = 0; i < n; i++)
            dp[mask][i] = INF;

    dp[1][0] = 0;

    for (int mask = 1; mask < totalMasks; mask++)
    {
        for (int u = 0; u < n; u++)
        {
            if (dp[mask][u] == INF)
                continue;

            for (int v = 0; v < n; v++)
            {
                if (!(mask & (1 << v)) && cost[u][v] > 0)
                {
                    int newMask = mask | (1 << v);

                    dp[newMask][v] = min(
                        dp[newMask][v],
                        dp[mask][u] + cost[u][v]
                    );
                }
            }
        }
    }

    int fullMask = totalMasks - 1;
    int ans = INF;

    for (int i = 1; i < n; i++)
    {
        if (cost[i][0] > 0 && dp[fullMask][i] != INF)
        {
            ans = min(ans, dp[fullMask][i] + cost[i][0]);
        }
    }

    if (ans == INF)
        cout << "No complete tour exists.";
    else
        cout << "Minimum travelling cost: " << ans;

    return 0;
}
