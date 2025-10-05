#include <iostream>
#include <string>
#include <set>
#include <iterator>
using namespace std;

namespace 
{
    string S;
    string T;
}

void read_stdin()
{
    cin >> S >> T;
}

pair<bool, bool> is_replacable(int k)
{
    // 入れ替えるまでもなく、部分文字列が含まれている
    bool already = true;
    for (int i = 0; i < T.size(); i++)
    {
        if (S.at(i + k) == '?' || S.at(i + k) == T.at(i))
        {
            if (S.at(i + k) == '?')
            {
                already = false;
            }
        }
        else
        {
            return {false, false};
        }
    }
    return {true, already};
}

void run()
{
    // 入れ替え可能な部分の最初のインデックス
    set<int> repl;
    // 既に部分文字列が変換無しで入っているか
    bool already = false;

    for (int i = 0; i < S.size() - T.size() + 1; i++)
    {
        auto [replacable, alr] = is_replacable(i);
        if (replacable)
        {
            repl.insert(i);
            already = (already || alr);
        }
    }

    if (repl.empty()) 
    {
        S = "UNRESTORABLE";
        return;
    }

    
    int begin = *(repl.rbegin());
    auto iter_begin = next(S.begin(), begin);

    for (auto iter = S.begin(); iter != S.end(); iter++)
    {
        if (*iter == '?')
        {
            S.replace(iter, iter + 1, "a");
        }
    }

    if (already) return;

    S.replace(iter_begin, iter_begin + T.length(), T);
}

void show_answer()
{
    cout << S << endl;
}

int main()
{
    read_stdin();

    run();
    show_answer();
}