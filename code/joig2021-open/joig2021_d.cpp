#include <iostream>
#include <map>
using namespace std;

bool judge_gorgeous
(
    int g,                              // 華やかさ gorgeous
    map<int, int> data,                 // 標準入力で読み取った絵のデータ(x, v)
    int dist,                           // 標準入力で受け取った、開けるべき間隔(距離)
    int M                               // 残す絵の数
)
{
    int left = -dist;
    int cnt = 0;
    cout << "distance must be geqq [" << dist << "] and gorgeous must be geqq [" << g << "]" << endl;
    for (auto iter = data.begin(); iter != data.end(); iter++)
    {
        if (iter->first - left >= dist && iter->second >= g)
        {
            cout << left << "___" << iter->first << ", " << iter->second << " >" << g << "\t: ";
            left = iter->first;
            cnt++;
            cout << cnt << "つ目" << endl;
            if (cnt >= M) return true;
        }
    }
    return false;
}

int main()
{
    int N, M, D;
    cin >> N >> M >> D;
    map<int, int> data;
    int tmp_x, tmp_v;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp_x >> tmp_v;
        data[tmp_x] = tmp_v;
    }

    // 二分探索
    // 華やかさをできるだけ大きくしたいので、true [true, false) false で左閉右開半開区間を用いる
    int left = -1;
    int right = 1e9+1;
    int middle;
    while (right - left > 1)
    {
        middle = (left + right) / 2;
        if (judge_gorgeous(middle, data, D, M))
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }
    cout << left << endl;
}