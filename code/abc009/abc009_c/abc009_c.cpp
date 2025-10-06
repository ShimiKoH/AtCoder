#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

namespace 
{
    int N;
    int K;
    string S;

    string answer;

    map<char, int> count_char;
    multiset<char> mset_of_char;
}

void read_stdin()
{
    cin >> N >> K >> S;
}

void form_data()
{
    for (char c = 'a'; c <= 'z'; c++)
    {
        count_char.insert({c, 0});
    }

    for (auto iter = S.begin(); iter != S.end(); iter++)
    {
        count_char.at(*iter)++;
        mset_of_char.insert(*iter);
    }
}

bool replace_with_m(string front, int m)
{
    map<char, int> cnt_ch = count_char;
    for (auto iter = front.begin(); iter != front.end(); iter++)
    {
        cnt_ch.at(*iter)--;
    }

    for (size_t i = front.size(); i < S.length(); i++)
    {
        char c = S.at(i);
        if (cnt_ch.at(c) > 0)
        {
            cnt_ch.at(c)--;
        }
        else
        {
            m--;
        }
    }
    return m >= 0;
}

void run()
{
    int cnt = 0;
    while (answer.length() != S.length())
    {
        int index = answer.length();
        multiset<char>::iterator iter = mset_of_char.begin();

        // multiset 内の文字を順に判定するループ
        while (iter != mset_of_char.end())
        {
            // answer の index文字目が、Sのindex文字目と一致するか否か
            if (*iter == S.at(index))   // 場合は、無条件にtrueなので次に進む
            {
                answer += *iter;
                mset_of_char.erase(iter);
                break;
            }
            else                        // それ以外の場合は、その位置に*iterを配置した際に、それより後ろを m 文字の入れ替えで収まるかを判定
            {
                if (replace_with_m(answer + *iter, K - cnt - 1))
                {
                    answer += *iter;
                    mset_of_char.erase(iter);
                    cnt++;
                    break;
                }
                else
                {
                    iter++;
                    continue;
                }
            }
        }
    }
}

void show_answer()
{
    cout << answer << endl;
}

int main()
{
    read_stdin();
    form_data();

    run();

    show_answer();
}