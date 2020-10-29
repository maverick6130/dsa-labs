#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define MOD 1000000007

vector<int> h (string s, int n) {
    vector<int> kvals(n+1);
    for(int i=0;i<s.size();++i) {
        if(s[i]=='1') {
            int x = i;
            int count = 0;
            while(x) {
                count += x&1;
                x >>= 1;
            }
            kvals[count]++;
        }
    }
    return kvals;
}

int f (const int &x, const vector<int> &perm) {
    int px = 0;
    for(int i=0;i<perm.size();++i) {
        if((x>>i)&1) {
            px |= 1<<perm[i];
        }
    }
    return px;
}

string f (const string &s, const vector<int> &perm) {
    string ps = s;
    for(int i=0;i<s.size();++i) {
        ps[i] = s[f(i,perm)];
    }
    return ps;
}

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,m;
    cin >> n >> m;
    vector<int> perm;
    for(int i=0;i<n;++i) {
        perm.push_back(i);
    }
    map<vector<int>,set<string>> hashset;
    for(int i=0;i<m;++i) {
        string s;
        cin >> s;
        hashset[h(s,n)].insert(s);
    }

    int inequivalent = 0;
    for(auto H : hashset) {
        while(!H.second.empty()) {
            inequivalent++;
            string s = *H.second.begin();
            H.second.erase(s);
            while((next_permutation(perm.begin(),perm.end()))&&(!H.second.empty())) {
                H.second.erase(f(s,perm));
            }
            for(int i=0;i<n;++i) {
                perm[i] = i;
            }
        }
    }

    cout << inequivalent << endl;

    return 0;
}