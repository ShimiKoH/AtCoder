#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct ability
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int maxi;
};

int get_team_score
(
    ability& m1,
    ability& m2,
    ability& m3
)
{
    ability team;
    for (auto m : {m1, m2, m3})
    {
        team.a = max(team.a, m.a);
        team.b = max(team.b, m.b);
        team.c = max(team.c, m.c);
        team.d = max(team.d, m.d);
        team.e = max(team.e, m.e);
    }
    return min({team.a, team.b, team.c, team.d, team.e});
}

bool is_ok
(
    int border,
    vector<ability> member
)
{
    for
    (
        auto iter1 = member.begin();
        iter1 != member.end();
        iter1++
    )
    {
        for 
        (
            auto iter2 = next(iter1); 
            iter2 != member.end(); 
            iter2++
        )
        {
            for
            (
                auto iter3 = next(iter2);
                iter3 != member.end();
                iter3++
            )
            {
                if (border <= get_team_score(*iter1, *iter2, *iter3)) return true;
            }
        }
    }
    return false;
}

int main()
{
    int N;
    cin >> N;
    vector<ability> member(N);
    for (int i = 0; i < N; i++)
    {
        ability& m = member.at(i);
        cin >> m.a >> m.b >> m.c >> m.d >> m.e;
        m.maxi = max({m.a, m.b, m.c, m.d, m.e});
    }

    // 二分探索
    // 最大値の探索なので true [true, false) false
    int low = 0;
    int high = 1e9 + 1;
    int middle;
    while (high - low > 1)
    {
        middle = (low + high) / 2;
        if (is_ok(middle, member))
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