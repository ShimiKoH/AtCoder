#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

namespace
{
    int N;
    int M;
    int X;
    vector<vector<int>> store;
    int answer = INT_MAX;
}

pair<bool, int> get_cost(int bit)
{
    int cost = 0;
    vector<int> skill(M);
    for (int i = 0; i < N; i++)
    {
        if (bit % 2)
        {
            for (int j = 0; j < M; j++)
            {
                skill.at(j) += store.at(i).at(j + 1);
            }
            cost += store.at(i).at(0);
        }
        bit >>= 1;
    }

    for (int e: skill)
    {
        if (e < X) return pair{false, -1}; 
    }
    return pair{true, cost};
}

void read_stdin()
{
    cin >> N >> M >> X;
    store = vector<vector<int>>(N, vector<int>(M + 1));
    for (int i = 0; i < N; i++)
    {
        cin >> store.at(i).at(0);
        for (int j = 0; j < M; j++)
        {
            cin >> store.at(i).at(j + 1);
        }
    }
}

int main()
{
    read_stdin();

    bool cnt = false;
    for (long b; b < pow(2, N); b++)
    {
        auto [boolean, cost] = get_cost(b);
        if (boolean)
        {
            answer = min(answer, cost);
        }
        cnt |= boolean;
    }
    cout << (cnt ? answer : -1) << endl;
}