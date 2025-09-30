#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

namespace
{
    long N;
    vector<long> sequence;
}

// 標準入力を取得
void read_stdin();

// 二進数による部分数列を処理
long process_binary(long);

// 二進数を走査
void create_binary();


void read_stdin()
{
    cin >> N;
    sequence = vector<long>(N);
    for (int i = 0; i < N; i++)
    {
        cin >> sequence.at(i);
    }
}

void create_binary()
{
    long mini = pow(2, 31) - 1;
    for (long i = 0; i < pow(2, N - 1); i++)
    {
        mini = min(mini, process_binary(i));
    }
    cout << mini << endl;
}

long process_binary(long bit)
{
    long res = 0;
    long tmp = sequence.at(0);
    long amari;
    for (int i = 1; i < N; i++)
    {
        amari = bit % 2;
        if (amari)
        {
            res ^= tmp;
            tmp = sequence.at(i);
        }
        else
        {
            tmp |= sequence.at(i);
        }
        bit >>= 1;
    }
    res ^= tmp;
    return res;
}

int main()
{
    read_stdin();

    create_binary();
}