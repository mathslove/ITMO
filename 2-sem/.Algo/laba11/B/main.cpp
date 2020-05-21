#include <iostream>
#include <vector>
#include <limits>

using namespace std;
#define INT_MAX 100000

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::freopen("pathsg.in","r", stdin);
    std::freopen("pathsg.out","w", stdout);

    int n,m;
    cin>>n>>m;

    vector<vector<int>> d(n);
    for (size_t i =0; i<n ; i++){
        d[i].resize(n,INT_MAX);
    }

    int s,f,w;
    for (size_t i = 0; i<m; i++){
        cin>>s>>f>>w;
        d[s-1][f-1] = w;
    }

    for (int k=0; k<n; ++k)
        for (int i=0; i<n; ++i)
            for (int j=0; j<n; ++j)
                d[i][j] = min (d[i][j], d[i][k] + d[k][j]);

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i==j) d[i][j]=0;
            cout<<d[i][j]<<" ";
        }
    cout<<endl;
    }

    return 0;
}