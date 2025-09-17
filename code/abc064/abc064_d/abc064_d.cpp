#include <iostream>
#include <string>
using namespace std;

namespace
{
    int N;
    string S;
    string answer;
}

void read_stdin()
{
    cin >> N >> S;
    answer = S;
}

void program()
{
    int cnt = 0;
    // ( で+1, )で-1
    // cnt < 0になったら ) の方が多いことになるので、( を先頭に付与し、cnt+=1
    for (int i = 0; i < N; i++)
    {
        if (S.at(i) == '(')
        {
            cnt++;
        }
        else
        {
            cnt--;
        }

        if (cnt < 0)
        {
            answer = "(" + answer;
            cnt++;
        }
    }
    
    if (cnt < 0)
    {
        throw 0;
    }
    
    answer = answer + string(cnt, ')');

    cout << answer << endl;
}

int main()
{
    read_stdin();

    program();
}