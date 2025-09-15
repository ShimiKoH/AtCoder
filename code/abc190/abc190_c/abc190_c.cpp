#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

namespace // 入力される定数およびそれに類するコンテナ
{
    int N;
    int M;
    vector<pair<int, int>> condition;
    int K;
    vector<pair<int, int>> selector;
}

// 二進数bitに対応する、条件の満たされた数を返す
int count_condition(int bit)
{
    vector<int> dishes(N, 0);
    int select_dish;
    for (int i = 0; i < K; i++)
    {
        select_dish = bit % 2;
        dishes.at(
            select_dish
            ? selector.at(i).first - 1
            : selector.at(i).second - 1
        ) |= 1;
        bit >>= 1;
    }

    int cnt = 0;
    int dish1, dish2;
    for (int i = 0; i < M; i++)
    {
        dish1 = condition.at(i).first - 1;
        dish2 = condition.at(i).second - 1;
        if (dishes.at(dish1) & dishes.at(dish2)) cnt++;
    }
    return cnt;
}

int main()
{
    cin >> N >> M;
    condition = vector<pair<int, int>>(M, pair{0, 0});
    for (int i = 0; i < M; i++)
    {
        cin >> condition.at(i).first >> condition.at(i).second;
    }
    cin >> K;
    selector = vector<pair<int, int>>(K, pair{0, 0});
    for (int i = 0; i < K; i++)
    {
        cin >> selector.at(i).first >> selector.at(i).second;
    }

    int maxi = 0;
    for (int i = 0; i < pow(2, 16); i++)
    {
        maxi = max(maxi, count_condition(i));
    }
    cout << maxi << endl;
}