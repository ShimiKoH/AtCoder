#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using Integer = long long;
// 与えられた数値border[以下]のペナルティですべての的を打ち切ることが可能か
bool border(
    const Integer line,
    const vector<pair<Integer, Integer>>& target,
    const Integer N
)
{
    static int call_cnt = 0;
    call_cnt++;
    // t[i] : i秒目に打つことでぎりぎり違反を免れる的の個数
    vector<Integer> time_clear(N + 1 , 0);
    Integer t;
    for (auto [h, s] : target)
    {
        if (line - h < 0) return false;
        t = min((line - h) / s, N);
        // cout << "\th = " << h << endl << "\ts = " << s << endl << "\tt = " << t << endl;
        time_clear.at(t) += 1;
    }

    Integer cnt = 0;
    for (int i = 0; i <= N; i++)
    {
        cnt += time_clear.at(i);
        if (cnt > i + 1) return false;
    }
    return true;
}


int main()
{
    Integer N, h, s;
    cin >> N;

    vector<pair<Integer, Integer>> target(N);

    for (int i = 0; i < N; i++)
    {
        cin >> h >> s;
        target.at(i) = pair{h, s};
    }

    // nポイント以下に収めることができるときのnの最小値
    // false (false true] true
    Integer high = 1e15l;
    Integer low = -1l;
    Integer middle;
    bool res;
    while (high - low > 1)
    {
        middle = (high + low) / 2;
        // cout << "[" << low << " " << middle << " " << high << "] " << endl;
        res = border(middle, target, N);
        if (res)  // 可能 -> 正解はmiddle以下である
        {
            // cout << "true" << endl;
            high = middle;
        }
        else                            // 不可能 -> 正解はmiddleより大きい
        {
            // cout << "false" << endl;
            low = middle;
        }
    }
    cout << high << endl;
}