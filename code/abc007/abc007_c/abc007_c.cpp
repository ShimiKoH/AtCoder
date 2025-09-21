#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

namespace 
{
    // 行数
    int R;
    // 列数
    int C;
    
    // 座標の構造体
    struct coord
    {
        int x;
        int y;
    };

    // スタート地点の座標
    coord start;
    // ゴール地点の座標
    coord goal;
    
    // 迷路
    vector<string> maze;
    // 最小移動手数
    vector<vector<int>> step;

    // 上下左右
    vector<coord> direct =
    {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
}

void read_stdin()
{
    cin >> R >> C >> start.y >> start.x >> goal.y >> goal.x;
    start.x--;
    start.y--;
    goal.x--;
    goal.y--;
    maze = vector<string>(R);
    step = vector<vector<int>>(R, vector<int>(C, 0));

    for (int i = 0; i < R; i++)
    {
        cin >> maze.at(i);
    }
}

void breadth_first_search()
{
    queue<coord> que({start});
    while (!que.empty())
    {
        coord now = que.front();
        que.pop();

        if (now.x == goal.x && now.y == goal.y)
        {
            cout << step.at(now.y).at(now.x) << endl;
            return;
        }

        for (coord d: direct)
        {
            coord next;
            next.x = now.x + d.x;
            next.y = now.y + d.y;
            if (next.y == 0 || next.y == R || next.x == 0 || next.x == C) continue;
            if (maze.at(next.y).at(next.x) == '#') continue;
            if (step.at(next.y).at(next.x) != 0) continue;

            step.at(next.y).at(next.x) = step.at(now.y).at(now.x) + 1;
            que.push(next);
        }
    }
}

int main()
{
    read_stdin();
    breadth_first_search();
}