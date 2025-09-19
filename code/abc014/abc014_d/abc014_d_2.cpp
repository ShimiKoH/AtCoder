#include <iostream>
#include <queue>
#include <vector>
#include <list>
using namespace std;

namespace 
{
    int N;
    int Q;
    vector<list<int>> edges;
    vector<pair<int, int>> another_edges;
}

void read_stdin()
{
    cin >> N;
    edges = vector<list<int>>(N);
    int tmp_x, tmp_y;
    for (int i = 0; i < N - 1; i++)
    {
        cin >> tmp_x >> tmp_y;
        edges.at(tmp_x - 1).push_back(tmp_y - 1);
        edges.at(tmp_y - 1).push_back(tmp_x - 1);
    }
    cin >> Q;
    another_edges = vector<pair<int, int>>(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> tmp_x >> tmp_y;
        another_edges.at(i).first = tmp_x - 1;
        another_edges.at(i).second = tmp_y - 1;
    }
}

int get_answer(pair<int, int> search_edge)
{
    int start = search_edge.first;
    int goal = search_edge.second;
    vector<int> step(N, 0);
    deque<int> deq({start});

    while (true)
    {
        int now = deq.front();  // 頂点now に到達
        deq.pop_front();

        // 頂点nowから伸びる枝を順にdeqに追加
        for (auto iter = edges.at(now).begin(); iter != edges.at(now).end(); iter++)
        {
            if (*iter == goal)
            {
                return step.at(now) + 2;
            }
            
            step.at(*iter) = step.at(now) + 1;
            deq.push_back(*iter);
        }
    }
}

void program()
{
    for (auto e: another_edges)
    {
        cout << get_answer(e) << endl;
    }
}

int main()
{
    read_stdin();
    program();
}