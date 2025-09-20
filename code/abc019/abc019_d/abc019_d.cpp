#include <iostream>
using namespace std;

namespace
{
    int N;
    int diameter = 0;
    int furthest;
}

void read_stdin()
{
    cin >> N;
}

int get_distance(int a, int b)
{
    int dist;
    cout << "? " << a << " " << b << endl;
    cin >> dist;
    return dist;
}

void proceed()
{
    int a = 1;
    for (int i = 0; i < 2; i++)
    {
        for (int b = 1; b <= N; b++)
        {
            if (a == b) continue;
            int dist = get_distance(a, b);
            if (diameter < dist)
            {
                diameter = dist;
                furthest = b;
            }
        }
        a = furthest;
    }
}

int main()
{
    read_stdin();
    proceed();
    cout << "! " << diameter << endl;
}