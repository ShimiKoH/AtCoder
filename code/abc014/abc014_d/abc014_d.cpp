#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <deque>
using namespace std;

namespace
{
    // 頂点の数
    int N;
    // 与えられる追加辺の数
    int Q;
    // 辺の数
    vector<list<int>> edges;
    // 頂点 0 からの距離
    vector<int> distance0;
    // 与えられる追加辺
    vector<pair<int, int>> another_edges;

    // ceil(log N)
    int M;
    // (i, j) : 頂点 j から 2^i 階登って到達する頂点
    // 既定値は -1 とする
    vector<vector<int>> upwards;
}

void read_stdin()
{
    cin >> N;
    edges = vector<list<int>>(N);
    int tmp_l, tmp_r;
    for (int i = 0; i < N - 1; i++)
    {
        cin >> tmp_l >> tmp_r;
        tmp_l--;
        tmp_r--;
        edges.at(tmp_l).push_back(tmp_r);
        edges.at(tmp_r).push_back(tmp_l);
    }

    cin >> Q;
    another_edges = vector<pair<int, int>>(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> tmp_l >> tmp_r;
        another_edges.at(i).first = --tmp_l;
        another_edges.at(i).second = --tmp_r;
    }
}

// 定数確認用関数
// デバッガー使えよってな
void show_constnace()
{
    cout << "N: " << N << ", Q: " << Q << endl;
    cout << "edges" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "from " << i+1 << " to: [";
        list<int> l = edges.at(i);
        for (auto iter = l.begin(); iter != l.end(); iter++)
        {
            cout << *iter+1 << ", ";
        }
        cout << "]" << endl;
    }

    cout << endl << "another_edges" << endl;
    for (pair<int, int> p : another_edges)
    {
        cout << p.first+1 << "---" << p.second+1 << endl;
    }

    cout << endl << "upwards" << endl;
    for (auto v : upwards)
    {
        cout << "[";
        for (auto e : v)
        {
            cout << e << ", ";
        }
        cout << "]" << endl;
    }

    cout << endl << "distance0" << endl << "[";
    for (int e : distance0)
    {
        cout << e << ", ";
    }
    cout << "]" << endl;
}

void make_data()
{
    M = ceil(log2(N));
    upwards = vector<vector<int>>(M, vector<int>(N, -1));
    upwards.at(0).at(0) = 0;
    
    // 頂点 0 からBFS
    distance0 = vector<int>(N, -1);
    distance0.at(0) = 0;
    deque<int> deq({0});
    while (!deq.empty())
    {
        int now = deq.front();
        deq.pop_front();
        list<int> l = edges.at(now);
        for (auto iter = l.begin(); iter != l.end(); iter++)
        {
            if (distance0.at(*iter) < 0)
            {
                upwards.at(0).at(*iter) = now;
                distance0.at(*iter) = distance0.at(now) + 1;
                deq.push_back(*iter);
            }
        }
    }

    for (int i = 1; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            upwards.at(i).at(j) = upwards.at(i - 1).at(upwards.at(i - 1).at(j));
        }
    }
}

int go_upward(int pos, int lvl)
{
    for (int i = 0; i < M; i++)
    {
        cout << "pos: " << pos << ", lvl: " << lvl << endl;
        if (lvl % 2)
        {
            pos = upwards.at(i).at(pos);
        }
        lvl >>= 1;
        if (!lvl) break;
    }
    return pos;
}

int sub_program(pair<int, int> pr)
{
    int left = pr.first;
    int right = pr.second;
    int dist_0_to_left = distance0.at(left);
    int dist_0_to_right = distance0.at(right);


    // 深さ調節
    if (dist_0_to_left < dist_0_to_right)
    {
        int how_many_up = distance0.at(right) - distance0.at(left);
        right = go_upward(right, how_many_up);
    }
    else if (dist_0_to_left > dist_0_to_right)
    {
        // left の方が深い場合、左右を入れかえて再帰し、答えを返す。
        return sub_program(pair{right, left});
    }

    // ここに到達した時点で、left と right は同じ深さ

    // 何階層上ったら同じ頂点に(初めて)到達するかを二分探索で求める
    // (false, true]
    pair<int, int> bin_search_range{-1, dist_0_to_left};
    while (bin_search_range.second - bin_search_range.first > 1)
    {
        int middle = (bin_search_range.first + bin_search_range.second) / 2;
        if (go_upward(left, middle) == go_upward(right, middle))
        {
            // 上る階層数はmiddle以下
            bin_search_range.second = middle;
        }
        else
        {
            // 上る階層数はmiddleより大きい
            bin_search_range.first = middle;
        }
    }
    int common_furthest_vertex = go_upward(left, bin_search_range.second);
    
    // 解答は もとのleft, right への距離から、共通部分までの距離の2倍を引き、
    // 最後に追加辺分の 1 を足した数
    return dist_0_to_left + dist_0_to_right
           - distance0.at(common_furthest_vertex) * 2 + 1;
}

void main_program()
{
    for (pair<int, int> p : another_edges)
    {
        cout << sub_program(p) << endl;
    }
}

int main()
{
    read_stdin();
    make_data();

    main_program();

    // show_constnace();
}