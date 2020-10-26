#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define MOD 1000000007

struct first_lesser {
    bool operator() (pair<int,int> x1, pair<int,int> x2) const{
        if(x1.first!=x2.first) return x1.first < x2.first;
        return x1.second < x2.second;
    }
};

struct first_greater {
    bool operator() (pair<int,int> x1, pair<int,int> x2) const{
        if(x1.first!=x2.first) return x1.first > x2.first;
        return x1.second > x2.second; 
    }
};

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> a (n);
    for(int i=0;i<n;++i) cin >> a[i];
    vector<int> b (n);
    for(int i=0;i<n;++i) cin >> b[i];
    vector<int> c (n);
    for(int i=0;i<n;++i) cin >> c[i];
    vector<int> d (n);
    for(int i=0;i<n;++i) cin >> d[i];
    
    vector<int> p,q;
    map<int,set<pair<int,int>,first_lesser>> S1;
    map<int,set<pair<int,int>,first_greater>> S2;

    for(int i=0;i<n;++i) {
        S1[a[i]].insert(pair<int,int> (b[i],i+1)); 
        S2[c[i]].insert(pair<int,int> (d[i],i+1));
    }

    auto A = S1.begin();
    auto C = S2.begin();

    bool flag = true;

    while (A!=S1.end()) {
        if(A->second.size()>C->second.size()) {
            while(!C->second.empty()) {
                auto x = C->second.begin();
                auto y = A->second.lower_bound(*x);
                if (y==A->second.end()) {
                    y--;
                    if(y->first<x->first) {
                        flag = false;
                        break;
                    }
                }
                p.push_back(y->second);
                q.push_back(x->second);
                A->second.erase(y);
                C->second.erase(x);
            }
            if(!flag) break;
            C++;
        }
        else if(C->second.size()>A->second.size()) {
            while(!A->second.empty()) {
                auto x = A->second.begin();
                auto y = C->second.lower_bound(*x);
                if (y==C->second.end()) {
                    y--;
                    if(y->first>x->first) {
                        flag = false;
                        break;
                    }
                }
                p.push_back(x->second);
                q.push_back(y->second);
                A->second.erase(x);
                C->second.erase(y);
            }
            if(!flag) break;
            A++;
        }
        else {
            while((!A->second.empty())&&(!C->second.empty())) {
                auto x = A->second.begin();
                auto y = C->second.lower_bound(*x);
                if (y==C->second.end()) {
                    y--;
                    if(y->first>x->first) {
                        flag = false;
                        break;
                    }
                }
                p.push_back(x->second);
                q.push_back(y->second);
                A->second.erase(x);
                C->second.erase(y);
            }
            if(!flag) break;
            A++;
            C++;
        }
    }

    if(!flag) {
        cout << "impossible" << endl;
    }
    else {

        for(int i=0;i<n;++i) {
            cout << p[i] << " ";
        }
        cout << endl;
        for(int i=0;i<n;++i) {
            cout << q[i] << " ";
        }
        cout << endl;
        
        vector<pair<int,int> > ab;
        vector<pair<int,int> > cd;
        for(int i=0;i<n;++i) {
            ab.push_back(pair<int,int> (a[p[i]-1],b[p[i]-1]));
            cd.push_back(pair<int,int> (c[q[i]-1],d[q[i]-1]));
        }
        ab.push_back(pair<int,int> (-1,-1));
        cd.push_back(pair<int,int> (-1,-1));
        
        for(int i=0;i<n-1;++i) {
            if((ab[i].first==ab[i+1].first)&&(cd[i].first==cd[i+1].first)) {
                cout << "not unique" << endl;
                return 0;
            }
        }
        
        int curra = -1;
        vector<pair<int,int> > db;
        for(int i=0;i<=n;++i) {
            if(ab[i].first!=curra) {
                if(!db.empty()) {
                    sort(db.begin(),db.end(),first_greater());
                    for(int j=0;j<db.size()-1;++j) {
                        if(db[j].first<=db[j+1].second) {
                            cout << "not unique" << endl;
                            return 0;
                        }
                    }
                }
                db.clear();
                curra = ab[i].first;
            }
            db.push_back(pair<int,int> (cd[i].second,ab[i].second));
        }

        int currc = -1;
        vector<pair<int,int> > bd;
        for(int i=0;i<=n;++i) {
            if(cd[i].first!=currc) {
                if(!bd.empty()) {
                    sort(bd.begin(),bd.end(),first_lesser());
                    for(int j=0;j<bd.size()-1;++j) {
                        if(bd[j].first>=bd[j+1].second) {
                            cout << "not unique" << endl;
                            return 0;
                        }
                    }
                }
                bd.clear();
                currc = cd[i].first;
            }
            bd.push_back(pair<int,int> (ab[i].second,cd[i].second));
        }

        cout << "unique" << endl;
    }

    return 0;
}