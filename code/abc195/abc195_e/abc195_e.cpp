#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

namespace 
{
    int N;
    string S;
    string X;
}

void read_stdin()
{
    cin >> N >> S >> X;
}

int get_sk()
{
    static string::reverse_iterator s_iter = S.rbegin();
    return *(s_iter++) - '0';
}

char get_xk()
{
    static string::reverse_iterator x_iter = X.rbegin();
    return *(x_iter++);
}

void run()
{
    set<int> dpk({0});
    set<int> dpk_1;

    for (int i = N; i > 0; i--)
    {
        dpk_1.clear();
        
        char xk = get_xk();
        int sk = get_sk();

        for (int rk_1 = 0; rk_1 < 7; rk_1++)
        {
            int cnt1 = dpk.count((rk_1 * 10 + sk) % 7);
            int cnt2 = dpk.count((rk_1 * 10 + 0) % 7);
                
            if (xk == 'T')
            {
                if (cnt1 + cnt2)
                {
                    dpk_1.insert(rk_1);
                }
            }
            else
            {
                if (cnt1 * cnt2)
                {
                    dpk_1.insert(rk_1);
                }
            }
        }
        
        dpk.swap(dpk_1);
    }

    if (dpk.count(0))
    {
        cout << "Takahashi" << endl;
    }
    else
    {
        cout << "Aoki" << endl;
    }
}

int main()
{
    read_stdin();
    
    run();
}