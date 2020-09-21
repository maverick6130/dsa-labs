#include<iostream>
using namespace std;
typedef long long int ll;

void computeF(int n,ll *f,ll *F) {
	if(n==0) F[0]=f[0];
	else {
		computeF(n-1,f,F);
		computeF(n-1,f+(1<<(n-1)),F+(1<<(n-1)));
		for(int i=0;i<(1<<(n-1));++i) F[i+(1<<(n-1))] += F[i];
	}
}

void computeFf(int n,ll *f,ll *F, bool* Ff) {
	if(n==0) {
		if(Ff[0]) f[0]=F[0];
		else F[0]=f[0];
	}
	else {
		computeFf(n-1,f,F,Ff);
		for(int i=0;i<(1<<(n-1));++i) { if(Ff[i+(1<<(n-1))]) F[i+(1<<(n-1))]-=F[i];}
		computeFf(n-1,f+(1<<(n-1)),F+(1<<(n-1)),Ff+(1<<(n-1)));
		for(int i=0;i<(1<<(n-1));++i) { F[i+(1<<(n-1))]+=F[i]; }
	}
}

int main() {
	int n;
	cin>>n;
	ll *f = new ll[1<<n], *F = new ll[1<<n];
	bool *Ff = new bool[1<<n];
	for(int i=0;i<(1<<n);++i) cin>>f[i];
	for(int i=0;i<(1<<n);++i) cin>>Ff[i];
	computeF(n,f,F);
	for(int i=0;i<(1<<n);++i) cout<<F[i]<<" ";
	cout<<endl;
	for(int i=0;i<(1<<n);++i) if(Ff[i]) F[i]=f[i];
	computeFf(n,f,F,Ff);
	for(int i=0;i<(1<<n);++i) {
		if(Ff[i]) cout<<f[i]<<" ";
		else cout<<F[i]<<" ";
	}
	cout<<endl;
	delete[] Ff,f,F;
}
