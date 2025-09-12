#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <iterator>
#include <iomanip>
using namespace std;

// 2点のデータからその2点が作る最小半径の最大値を返す
float get_radius
(
    tuple<float, float, float> dotA,
    tuple<float, float, float> dotB
)
{
    auto [ax, ay, ar] = dotA;
    auto [bx, by, br] = dotB;
    float dist = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
    if (ar > 0 && br > 0)
    {
        return min(ar, br);
    }
    else if (ar == 0.0f && br == 0.0f)
    {
        return dist / 2;
    }
    else
    {
        return dist - (ar + br);
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<tuple<float, float, float>> dot(N+M);
    
    for (int i = 0; i < N; i++)
    {
        auto& [x, y, r] = dot.at(i);
        cin >> x >> y >> r;
    }
    for (int i = 0; i < M; i++)
    {
        auto& [x, y, r] = dot.at(i + N);
        cin >> x >> y;
        r = 0;
    }

    float minimum = 1e15;
    for (int i = 0; i < N+M; i++)
    {
        for (int j = i + 1; j < N+M; j++)
        {
            minimum = min(minimum, get_radius(dot.at(i), dot.at(j)));
        }
    }

    cout << setprecision(12) << minimum << endl;
}