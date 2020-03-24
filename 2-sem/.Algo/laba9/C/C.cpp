
#include <iostream>
#include <vector>
#include "list"

enum color {
    white = -1,
    neutral = 0,
    black = 1
};

int main() {

    std::freopen("bipartite.in","r", stdin);
    std::freopen("bipartite.out","w", stdout);

    int n,m;
    std::cin >> n >> m;

    std::vector<std::vector<int> > graph(n);
    std::vector<int> clr;
    bool f = true;

    clr.assign(n, neutral);

    int b,e;
    while(!std::cin.eof()){
        std::cin>>b>>e;
        graph[b-1].push_back(e-1);
        graph[e-1].push_back(b-1);
    }

    std::list<int> q;
    for (int i = 0; i<n; i++){
        if (clr[i] == neutral){
            q.push_back(i);
            clr[i] = white;
            while(!q.empty()){
                int v = q.front();
                q.pop_front();
                for (int u : graph[v]){
                    if (clr[u] == neutral){
                        clr[u] = -clr[v];
                        q.push_back(u);
                    } else if (clr[u] == clr[v]){
                        f = false;
                    }
                }
            }
        }
    }


    std::cout << (f ? "YES" : "NO");

    return 0;
}
