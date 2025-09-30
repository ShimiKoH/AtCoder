#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

namespace 
{
    int N;
    string S;
    string X;

    vector<vector<int>> rk1_from_rk_sk(7, vector<int>(7));

    // amari[s_k][r_k] = set(r_k_1)
    // amari[s_k] : k手目 s_k を選ぶことで、あまりが r_k となるようなあまり r_k_1
    vector<vector<set<int>>> amari = vector<vector<set<int>>>(10, vector<set<int>>(7));
}

void read_stdin()
{
    cin >> N >> S >> X;
}

void form_data()
{
    for (int rk_1 = 0; rk_1 < 7; rk_1++)
    {
        for (int sk = 0; sk < 7; sk++)
        {
            int rk = (rk_1 * 10 + sk) % 7;
            rk1_from_rk_sk.at(rk).at(sk) = rk_1;
        }
    }
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

        set<int> tmp_sk;
        set<int> tmp_0;
        for (int rk: dpk)
        {
            tmp_sk.insert(rk1_from_rk_sk.at(rk).at(sk % 7));
            tmp_0.insert(rk1_from_rk_sk.at(rk).at(0));
        }

        if (xk == 'T')
        {
            set_union(
                tmp_sk.begin(),
                tmp_sk.end(),
                tmp_0.begin(),
                tmp_0.end(),
                inserter(dpk_1, dpk_1.end())
            );
        }
        else
        {
            set_intersection(
                tmp_sk.begin(),
                tmp_sk.end(),
                tmp_0.begin(),
                tmp_0.end(),
                inserter(dpk_1, dpk_1.end())
            );

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
    form_data();
    
    run();
}