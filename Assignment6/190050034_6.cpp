#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long int ll;

int main() {
	int n;
	cin>>n;
	
	vector<int> f(n), behind(n), ahead(n),bf(n);
	
	for(int i=0;i<n;++i) cin>>f[i];

	for(int i=0;i<n;++i) {
		int j=i-1;
		while((j>=0)&&(f[j]<f[i])) j=behind[j];
		behind[i]=j;
	}

	for(int i=n-1;i>=0;--i) {
		int j=i+1;
		while((j<n)&&(f[j]<f[i])) j=ahead[j];
		ahead[i]=j;
	}

	for(int i=0;i<n;++i) {
		int j=i-1;
		while((j>=0)&&(f[j]<=f[i])) j=bf[j];
		bf[i]=j;
	}

	for(int i=0;i<n;++i) cout<<(ll)(i-behind[i])*(ll)(ahead[i]-i)<<" ";
	cout<<endl;

	ll wellformed = 0;
	vector<int> minvals, minindices;
	for(auto elem=f.begin(); elem!=f.end(); ++elem) {
		int i = elem-f.begin();
		auto valup = upper_bound(minvals.begin(),minvals.end(),*elem);
		auto indup = minindices.begin() + (valup - minvals.begin());
		minvals.erase(valup,minvals.end());
		minindices.erase(indup,minindices.end());
		minvals.push_back(*elem);
		minindices.push_back(i);
		wellformed += minindices.end()-upper_bound(minindices.begin(),minindices.end(),bf[i]);
	}

	cout<<wellformed<<endl;
}