#include <iostream>
#include <fstream>
#include <vector>
#include "algorithm"
#define max 100000
enum color {
    white,
    grey,
    black
};
std::vector<unsigned> res;
std::vector<std::vector<unsigned>> graph;
std::vector<short> color;
bool cycle = false;

void dfs(unsigned v){
    color[v] = grey;
    for (unsigned u : graph[v]){
        if (color[u] == grey){
            cycle = true;
            return;}
        if (color[u] == white)
            dfs(u);
    }
    color[v] = black;
    res.push_back(v+1);
}

void topsort(unsigned n){
    for (int i = 0; i<n; i++){
        if (not cycle and color[i] == white){
            dfs(i);
        }
    }
    reverse(begin(res), end(res));
}

int main(){
    std::freopen("topsort.in","r", stdin);
    std::freopen("topsort.out","w", stdout);

    unsigned n,m;
    std::cin >> n >> m;

    graph.resize(n);
    color.resize(n);

    for (int i = 0; i<n; i++){
        color[i] = white;
    }

    unsigned b,e;
    while(!std::cin.eof()){
        std::cin>>b>>e;
        graph[b-1].push_back(e-1);
    }

    topsort(n);

    if (not cycle){
        for (unsigned x : res)
            std::cout << x << " ";
    } else{
        std::cout << "-1";
    }

    return 0;
}