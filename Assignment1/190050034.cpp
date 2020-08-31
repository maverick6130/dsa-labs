#include <iostream>
using namespace std;

typedef long long ll;

ll J(ll n,int k) {
    if(k>n) {
        if(n==1) return 1;
        return (k+J(n-1,k)-1)%n + 1;
    }
    else {
        ll m=n/k;
        ll j=J(n-m,k);
        int p=n%k;
 		if(j<=p) return m*k+j;
		ll l = j-p;
		return (m*k+j+(l-1)/(k-1)-1)%n + 1;       
    }
}

int main() {
    ll n;
    int k;
    cin>>n>>k;
    cout<<J(n,k);
}
