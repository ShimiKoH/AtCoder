#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iterator>
using namespace std;

namespace 
{
    int H;
    int W;

    vector<string> field;

    // y 行目に存在する壁 "#" の位置
    vector<vector<int>> wall_in_row;
    // x 列目に存在する壁 "#" の位置
    vector<vector<int>> wall_in_col;

    struct binary_search_index
    {
        size_t left;
        size_t right;
        size_t top;
        size_t bottom;
    };

    int answer = 0;
}

void read_stdin()
{
    cin >> H >> W;
    field = vector<string>(H);
    wall_in_row = vector<vector<int>>(H, vector<int>({-1}));
    wall_in_col = vector<vector<int>>(W, vector<int>({-1}));

    for (int h = 0; h < H; h++)
    {
        cin >> field.at(h);
        for (int w = 0; w < W; w++)
        {
            if (field.at(h).at(w) == '#')
            {
                wall_in_row.at(h).push_back(w);
                wall_in_col.at(w).push_back(h);
            }
        }
    }

    for (vector<int>& vec: wall_in_row)
    {
        vec.push_back(W);
    }
    for (vector<int>& vec: wall_in_col)
    {
        vec.push_back(H);
    }
}

int get_area(int y, int x)
{
    binary_search_index index
    {
        0,
        wall_in_row.at(y).size() - 1,
        0,
        wall_in_col.at(x).size() - 1
    };

    while (index.right - index.left > 1)
    {
        size_t index_mid = (index.right + index.left) / 2;
        int value_mid = wall_in_row.at(y).at(index_mid);
        if (value_mid < x)
        {
            index.left = index_mid;
        }
        else
        {
            index.right = index_mid;
        }
    }

    while (index.bottom - index.top > 1)
    {
        size_t index_mid = (index.bottom + index.top) / 2;
        int value_mid = wall_in_col.at(x).at(index_mid);
        if (value_mid < y)
        {
            index.top = index_mid;
        }
        else
        {
            index.bottom = index_mid;
        }
    }

    int count_row = wall_in_row.at(y).at(index.right)
                    - wall_in_row.at(y).at(index.left)
                    - 1;
    int count_col = wall_in_col.at(x).at(index.bottom)
                    - wall_in_col.at(x).at(index.top)
                    - 1;
    return count_row + count_col - 1;
}

void put_lamp()
{
    for (int h = 0; h < H; h++)
    {
        for (int w = 0; w < W; w++)
        {
            int tmp = get_area(h, w);
            answer = max(tmp, answer);
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
    put_lamp();

    show_answer();
}