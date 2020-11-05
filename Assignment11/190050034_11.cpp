#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define MOD 1000000007

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m,u,v;
    cin >> n >> m >> u >> v;
    vector<vector<int> > adj(n);
    for(int i=0;i<m;++i) {
        int x,y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<pair<int,int> > upath (n,pair<int,int> (-1,-1)), vpath (n,pair<int,int> (-1,-1));
    upath[u].first = 0; vpath[v].first = 0;
    queue<pair<int,bool> > bfsorder({pair<int,bool> (u,0)});
    while(!bfsorder.empty()) {
        pair<int,int> x = bfsorder.front();
        bfsorder.pop();
        if(x.second) {
            for(auto y : adj[x.first]) {
                if(upath[y].first<0) {
                    upath[y].first = upath[x.first].second + 1;
                    bfsorder.push(pair<int,int> (y,0));
                }
            }
        }
        else {
            for(auto y : adj[x.first]) {
                if(upath[y].second<0) {
                    upath[y].second = upath[x.first].first + 1;
                    bfsorder.push(pair<int,int> (y,1));
                }
            }
        }
    }
    bfsorder.push(pair<int,int> (v,0));
    while(!bfsorder.empty()) {
        pair<int,int> x = bfsorder.front();
        bfsorder.pop();
        if(x.second) {
            for(auto y : adj[x.first]) {
                if(vpath[y].first<0) {
                    vpath[y].first = vpath[x.first].second + 1;
                    bfsorder.push(pair<int,int> (y,0));
                }
            }
        }
        else {
            for(auto y : adj[x.first]) {
                if(vpath[y].second<0) {
                    vpath[y].second = vpath[x.first].first + 1;
                    bfsorder.push(pair<int,int> (y,1));
                }
            }
        }
    }
    int mintime = upath[v].first;
    if(mintime<0) cout << "impossible" << endl;
    else {
        mintime /= 2;
        cout << "possible" << endl;
        cout << mintime << endl;
        if(mintime&1) {
            for(int i=0;i<n;++i) 
                if((upath[i].second==mintime)&&(vpath[i].second==mintime))
                    cout << i << " ";
        }
        else {
            for(int i=0;i<n;++i) 
                if((upath[i].first==mintime)&&(vpath[i].first==mintime))
                    cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}