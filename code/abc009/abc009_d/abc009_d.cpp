#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;
using ui = unsigned int;

namespace 
{
    int K;
    int M;

    vector<ui> seqA;

    vector<ui> seqC;

    vector<vector<vector<ui>>> powerC;

    vector<vector<ui>> answer_matrix;

    ui answer;
}

void read_stdin()
{
    cin >> K >> M;
    
    seqA = vector<ui>(K);
    seqC = vector<ui>(K);

    for (int i = 0; i < K; i++)
    {
        cin >> seqA.at(i);
    }

    for (int i = 0; i < K; i++)
    {
        cin >> seqC.at(i);
    }
}

void matrix
(
    vector<vector<ui>>& left,       // a x b 行列
    vector<vector<ui>>& right,      // b x c 行列
    vector<vector<ui>>& result      // a x c 行列
)
{
    int a = left.size();
    int b = left.at(0).size();
    int c = right.at(0).size();

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < c; j++)
        {
            ui tmp = 0;
            for (int k = 0; k < b; k++)
            {
                tmp ^= (left.at(i).at(k) & right.at(k).at(j));
            }
            result.at(i).at(j) = tmp;
        }
    }
}

void form_data()
{
    int m = ceil(log2(M));
    powerC = vector<vector<vector<ui>>>(m + 1, vector<vector<ui>>(K, vector<ui>(K, 0)));
    // ###########################################################
    // ここで行列の数を m + 1 にしておかないと、
    // M = 1 の場合に m = 0 となってしまって行列を格納できなくなるため
    // この後の処理で out_of_range 例外が送られてしまう。
    // ###########################################################


    vector<vector<ui>>& pC1 = powerC.at(0);
    pC1.at(0).at(K - 1) = seqC.at(K - 1);
    for (int i = 1; i < K; i++)
    {
        pC1.at(i).at(i - 1) = pow(2, 32) - 1;
        pC1.at(i).at(K - 1) = seqC.at(K - 1 - i);
    }

    for (int i = 0; i < m - 1; i++)
    {
        matrix(powerC.at(i), powerC.at(i), powerC.at(i + 1));
    }

    answer_matrix = {seqA};
}

void run()
{
    if (M <= K)
    {
        answer = seqA.at(M - 1);
    }
    else
    {
        M -= K;
        int fig = 0;
        set<int> set_fig;
        while (M > 0)
        {
            if (M % 2) set_fig.insert(fig);
            fig++;
            M /= 2;
        }
    
        vector<vector<ui>> tmp = {seqA};
        for (auto iter = set_fig.begin(); iter != set_fig.end(); iter++)
        {
            matrix(tmp, powerC.at(*iter), answer_matrix);
            tmp = answer_matrix;
        }
        answer = answer_matrix.at(0).at(K - 1);
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