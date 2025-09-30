#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

namespace 
{
    int H;
    int W;
    vector<string> field;
    vector<vector<int>> count_in_row;
    vector<vector<int>> count_in_column;

    int answer = 0;
}

void read_stdin()
{
    cin >> H >> W;
    field = vector<string>(H);
    count_in_row = vector<vector<int>>(H, vector<int>(W, 0));
    count_in_column = vector<vector<int>>(H, vector<int>(W, 0));
    for (int i = 0; i < H; i++)
    {
        cin >> field.at(i);
    }
}

void count_period()
{
    // 0 <= h <= H であるi行目について、`.`が横にいくつ続くかを数える
    for (int h = 0; h < H; h++)
    {
        int cnt = 0;
        int left = 0;
        for (int right = 0; right < W; right++)
        {
            if (field.at(h).at(right) == '.')
            {
                // `.`なら加算
                cnt++;
            }
            else
            {
                // `#`ならそれより手前までをcntで埋め、
                // `#`に該当する位置を0にし(既定値なのでスキップ)、
                // つぎの判定の開始を次のマスに移す
                for (int w = left; w < right; w++)
                {
                    count_in_row.at(h).at(w) = cnt;
                }
                cnt = 0;
                left = right + 1;
                right++;
            }
            // もし、最後が`.`のときに埋める操作が必要
            // 最後が`#`のとき left は Wであるため、この中には入らない
            for (int w = left; w < W; w++)
            {
                count_in_row.at(h).at(w) = cnt;
            }
        }
    }

    // 0 <= w <= C であるw列目について、`.`が縦にいくつ続くかを数える
    for (int w = 0; w < W; w++)
    {
        int cnt = 0;
        int top = 0;
        for (int bottom = 0; bottom < H; bottom++)
        {
            if (field.at(bottom).at(w) == '.')
            {
                cnt++;
            }
            else
            {
                for (int h = top; h < bottom; h++)
                {
                    count_in_column.at(h).at(w) = cnt;
                }
                count_in_column.at(bottom).at(w) = 0;
                cnt = 0;
                top = bottom + 1;
                bottom++;
            }
            for (int h = top; h < H; h++)
            {
                count_in_column.at(h).at(w) = cnt;
            }
        }
    }
}

void get_area()
{
    for (int h = 0; h < H; h++)
    {
        for (int w = 0; w < W; w++)
        {
            int area = count_in_row.at(h).at(w)
                        + count_in_column.at(h).at(w)
                        - 1;
            answer = max(answer, area);
        }
    }
}

// 変数確認
void show()
{
    cout << "H: " << H << ", W:" << W << endl;
    
    cout << "field" << endl;
    for (auto t: field)
    {
        cout << t << endl;
    }

    cout << "count_in_row" << endl;
    for (auto v: count_in_row)
    {
        for (auto e: v)
        {
            cout << e << " ";
        }
        cout << endl;
    }

    cout << "count_int_colums" << endl;
    for (auto v: count_in_column)
    {
        for (auto e: v)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}

int main()
{
    read_stdin();
    count_period();
    get_area();

    show();

    cout << endl << "answer" << endl;
    cout << answer << endl;
}