#include <iostream>
#include <vector>
#include <limits>

using namespace std;

long long dijkstra(int n,vector<vector<long long >> &g,int vS, int vF){
    int v;
    vector<long long> d(n,LONG_LONG_MAX);
    vector<bool> used(n, false);
    d[vS] = 0;
    for (size_t i = 0; i<n; i++){
        v=-1;
        for (size_t j = 0; j<n; j++){
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == LONG_LONG_MAX)
            break;

        used[v] = true;

        for (size_t e = 0; e<n; e++)
            if (g[v][e] != -1  && d[v]+g[v][e] < d[e])
                d[e] = d[v]+g[v][e];
    }
    return d[vF];
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::freopen("pathmgep.in","r", stdin);
    std::freopen("pathmgep.out","w", stdout);

    int n,s,f;
    cin>>n>>s>>f;

    vector<vector<long long>> g(n);
    for (size_t i = 0; i<n; i++)
        g[i].resize(n);

    for (size_t i = 0; i<n; i++)
        for (size_t t = 0; t<n; t++)
            cin >> g[i][t];

    long long ans = dijkstra(n,g,s-1,f-1);

    if (ans != LONG_LONG_MAX)
        cout<<ans;
    else
        cout<<-1;

    return 0;
}