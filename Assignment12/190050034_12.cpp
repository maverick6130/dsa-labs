#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define MOD 1000000007

struct  Edge {
    int both;
    int first;
    int second;
    int none;
    Edge() {
        both = 0;
        second = 0;
        first = 0;
        none = 0;
    }
};

struct Vertex {
    int with;
    int without;
    Vertex() {
        with = 1;
        without = 0;
    }
};

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m;
    cin >> n >> m;
    vector<unordered_set<int> > edg(n);
    vector<unordered_map<int,Edge> > adj(n);
    vector<Vertex> v(n);
    for(int i=0;i<m;++i) {
        int u,v;
        cin >> u >> v;
        adj[u][v] = Edge();
        adj[v][u] = Edge();
        edg[u].insert(v);
        edg[v].insert(u);
    }

    int nodes = n;
    vector<bool> queued(n,false);
    vector<bool> deleted(n,false);

    queue<int> process;
    for(int i=0;i<n;++i) {
        if(adj[i].size()<3) {
            process.push(i);
            queued[i] = true;
        }
    }

    while(!process.empty()) {
        int p = process.front();
        process.pop();
        queued[p] = false;
        if(adj[p].size()==1) {
            int x = adj[p].begin()->first;
            v[x].with += max(
                (v[p].with + adj[p][x].both)*(edg[p].find(x)==edg[p].end()),
                v[p].without + adj[p][x].second
            );
            v[x].without += max(
                v[p].with + adj[p][x].first,
                v[p].without + adj[p][x].none
            );
            adj[x].erase(p);
            edg[x].erase(p);
            if((!queued[x])&&(adj[x].size()<3)) {
                process.push(x);
                queued[x] = true;
            }
            adj[p].clear();
            edg[p].clear();
            deleted[p] = true;
            nodes--;
        }
        else if (adj[p].size()==2) {
            int x = adj[p].begin()->first;
            int y = (++adj[p].begin())->first;
            adj[x].erase(p);
            adj[y].erase(p);
            edg[x].erase(p);
            edg[y].erase(p);
            bool xy = edg[x].find(y)==edg[x].end();
            bool px = edg[p].find(x)==edg[p].end();
            bool py = edg[p].find(y)==edg[p].end();
            adj[x][y].both += max(
                (v[p].with + adj[p][x].both + adj[p][y].both)*xy*px*py,
                (v[p].without + adj[p][x].second + adj[p][y].second)*xy
            );
            adj[x][y].second += max(
                (v[p].with + adj[p][x].first + adj[p][y].both)*py,
                v[p].without + adj[p][x].none + adj[p][y].second
            );
            adj[x][y].first += max(
                (v[p].with + adj[p][x].both + adj[p][y].first)*px,
                v[p].without + adj[p][x].second + adj[p][y].none
            );
            adj[x][y].none += max(
                v[p].with + adj[p][x].first + adj[p][y].first,
                v[p].without + adj[p][x].none + adj[p][y].none
            );
            adj[y][x].both = adj[x][y].both;
            adj[y][x].first = adj[x][y].second;
            adj[y][x].second = adj[x][y].first;
            adj[y][x].none = adj[x][y].none;
            if((!queued[x])&&(adj[x].size()<3)) {
                process.push(x);
                queued[x] = true;
            }
            if((!queued[y])&&(adj[y].size()<3)) {
                process.push(y);
                queued[y] = true;
            }
            adj[p].clear();
            edg[p].clear();
            deleted[p] = true;
            nodes--;
        }
    }

    if(nodes==1) {
        cout << "yes" << endl;
        for(int i=0;i<n;++i) {
            if(!deleted[i]) {
                cout << max(v[i].with,v[i].without) << endl;
                break;
            }
        }
    }
    else cout << "no" << endl;

    return 0;
}
