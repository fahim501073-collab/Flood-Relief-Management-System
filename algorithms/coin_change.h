5.algorithms/coin_change.h



#ifndef COIN_CHANGE_H
#define COIN_CHANGE_H

#include <algorithm>
#include <limits>
#include <vector>

struct CoinChangeResult {
    bool possible = false;
    int minimumCoins = -1;
    std::vector<int> coinsUsed;
};

inline CoinChangeResult coinChange(
    int amount,
    std::vector<int> denominations
) {
    CoinChangeResult result;

    if (amount < 0) {
        return result;
    }

    denominations.erase(
        std::remove_if(
            denominations.begin(),
            denominations.end(),
            [](int coin) {
                return coin <= 0;
            }
        ),
        denominations.end()
    );

    std::sort(
        denominations.begin(),
        denominations.end()
    );

    denominations.erase(
        std::unique(
            denominations.begin(),
            denominations.end()
        ),
        denominations.end()
    );

    const int INF =
        std::numeric_limits<int>::max() / 2;

    std::vector<int> dp(amount + 1, INF);
    std::vector<int> previousCoin(amount + 1, -1);

    dp[0] = 0;

    for (int value = 1; value <= amount; value++) {
        for (int coin : denominations) {
            if (coin <= value &&
                dp[value - coin] + 1 < dp[value]) {

                dp[value] = dp[value - coin] + 1;
                previousCoin[value] = coin;
            }
        }
    }

    if (dp[amount] == INF) {
        return result;
    }

    result.possible = true;
    result.minimumCoins = dp[amount];

    int remaining = amount;

    while (remaining > 0) {
        int coin = previousCoin[remaining];

        if (coin <= 0) {
            return CoinChangeResult{};
        }

        result.coinsUsed.push_back(coin);
        remaining -= coin;
    }

    return result;
}

#endif
