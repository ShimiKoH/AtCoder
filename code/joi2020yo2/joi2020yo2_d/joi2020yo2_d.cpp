#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

namespace
{
    int M;
    int R;

    vector<vector<int>> tenkey = {
        {7, 8, 9},
        {4, 5, 6},
        {1, 2, 3},
        {0, -1, -1},
    };

    struct coord
    {
        int h;
        int w;
    };

    vector<coord> direct = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
    };

    vector<set<int>> connect;
    vector<set<int>> memory;

    int answer;
}

void read_stdin()
{
    cin >> M >> R;
}

void form_data()
{
    // initialize memory
    memory = vector<set<int>>(M);
    
    // initialize connect
    connect = vector<set<int>>(10);
    for (int h = 0; h < 3; h++)
    {
        for (int w = 0; w < 3; w++)
        {
            int key = tenkey.at(h).at(w);
            for (coord d : direct)
            {
                int nexh = h + d.h;
                int nexw = w + d.w;
                if(nexh < 0 || 3 <= nexh || nexw < 0 || 3 <= nexw) continue;
                connect.at(key).insert(tenkey.at(nexh).at(nexw));
            }
        }
    }
    connect.at(0).insert(1);
    connect.at(1).insert(0);
}

void run()
{
    // pair<int, int>
    // ::first      amari
    // ::second     key
    queue<pair<int, int>> que({{0, 0}});
    queue<pair<int, int>> nexque;

    int step = 0;
    while (true)
    {
        step++;
        
        while (!que.empty())
        {
            int amari = que.front().first;
            int key = que.front().second;
            que.pop();

            // この amari のまま移動する
            for (int nexkey: connect.at(key))
            {
                if (memory.at(amari).count(nexkey)) continue;
                memory.at(amari).insert(nexkey);
                nexque.push({amari, nexkey});
            }

            // この key を押す
            amari = (amari * 10 + key) % M;
            if (amari == R)
            {
                answer = step;
                return;
            }
            if (memory.at(amari).count(key)) continue;
            nexque.push({amari, key});
        }

        que.swap(nexque);
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