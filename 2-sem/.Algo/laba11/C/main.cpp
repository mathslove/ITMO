#include <iostream>
#include <vector>
#include <limits>
#include <set>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::freopen("pathbgep.in","r", stdin);
    std::freopen("pathbgep.out","w", stdout);

    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>> g(n);

    int s,f,w;
    for (size_t i = 0; i<m; i++){
        cin >>s>>f>>w;
        g[s-1].push_back(make_pair(f-1,w));
        g[f-1].push_back(make_pair(s-1,w));
    }

    vector<int> d(n,INT_MAX),p(n);
    d[0]=0;
    set<pair<int,int>> q;
    q.insert(make_pair(d[0],0));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase (q.begin());

        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (d[v] + len < d[to]) {
                q.erase (make_pair (d[to], to));
                d[to] = d[v] + len;
                p[to] = v;
                q.insert (make_pair (d[to], to));
            }
        }
    }

    for (int i = 0; i<n;i++)
        cout<<d[i]<<" ";

    return 0;
}