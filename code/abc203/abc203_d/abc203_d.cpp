#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

namespace constance
{
    int N;
    int K;
    int amount;
    vector<vector<int>> park;
};
using namespace constance;

// paramters
// 
bool judge(int value)
{
    // 二次元配列の累積和
    vector<vector<int>> cumulative(N + 1, vector<int>(N + 1, 0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cumulative.at(i + 1).at(j + 1)
                = (park.at(i).at(j) >= value ? 1 : 0)
                + cumulative.at(i).at(j + 1)
                + cumulative.at(i + 1).at(j)
                - cumulative.at(i).at(j);
        }
    }
    
    // 起点を(i, j) = (K, K)とし、(N, N)に到達するまで、
    // (i - K, j - K), (i, j - K), (i - K, j), (i, j)を4頂点とする正方形の内部の合計値が
    //      [K^2/2]+1 未満のときにfalseを返し、最後まで到達したらtrueを返す
    int median;
    for (int i = K; i <= N; i++)
    {
        for (int j = K; j <= N; j++)
        {
            median
                = cumulative.at(i).at(j)
                - cumulative.at(i).at(j - K)
                - cumulative.at(i - K).at(j)
                + cumulative.at(i - K).at(j - K);
            if (median < amount) return false;
        }
    }
    return true;
}

int main()
{
    cin >> N >> K;
    park = vector<vector<int>>(N, vector<int>(N, 0));
    amount = (K * K) / 2 + 1;
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> park.at(i).at(j);
        }
    }

    // 二分探索
    // 最も低いものを探すが、judge 関数は
    //  「すべて区画の中央値はmiddle以上であるか？」
    // の問いに答えるので、true [true, false) false
    // を設定することで、存在する中央値でもっとも低いものを探せる
    int low = 0;
    int high = 1e9 + 1;
    int middle;
    while (high - low > 1)
    {
        middle = (high + low) / 2;
        if (judge(middle))
        {
            low = middle;
        }
        else
        {
            high = middle;
        }
    }
    cout << low << endl;
}