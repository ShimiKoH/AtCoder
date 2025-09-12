#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;

bool is_okay
(
    int border,
    vector<vector<int>> member
)
{
    set<int> member_binary;
    int tmp;
    for (auto person : member)
    {
        tmp = 0;
        for (int i = 0; i < 5; i++)
        {
            tmp += (person.at(i) >= border ? pow(2, 4-i) : 0);
        }
        member_binary.insert(tmp);
    }

    for (int m1 : member_binary)
    {
        for (int m2 : member_binary)
        {
            for (int m3 : member_binary)
            {
                if ((m1 | m2 | m3) == 31)
                {
                    return true;
                };
            }
        }
    }
    return false;
}

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> member(N, vector<int>(5));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> member.at(i).at(j);
        }
    }

    int low = 0;
    int high = 1e9 + 1;
    int middle;
    while (high - low > 1)
    {
        middle = (high + low) / 2;
        if (is_okay(middle, member))
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