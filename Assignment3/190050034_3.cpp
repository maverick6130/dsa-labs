#include<iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int in_n,t;
	cin>>in_n>>t;
	const unsigned int n = in_n;
	long long int m[n][n];
	for(int i=0;i<n;++i)
		m[i][n-1]=1;
	for(int j=n-2;j>=0;--j) {
		for(int i=0;i<=j;++i)
			m[i][j] = (i+1)*m[i][j+1] + m[i+1][j+1];
	}

	while(t--) {
		char mode;
		cin>>mode;
		if(mode=='R') {
			long long int rank=0;
			int max=0;
			int a;
			for(int i=0;i<n;++i) {
				cin>>a;
				rank+=a*m[max][i];
				if(a>max)
					max=a;
			}
			cout<<rank<<"\n";
		}
		else {
			long long int rank;
			cin>>rank;
			int *a = new int[n];
			int max=0;
			for(int i=0;i<n;++i) {
				a[i] = rank/m[max][i];
				if(a[i]>max+1)
					a[i]=max+1;
				rank-=a[i]*m[max][i];
				if(a[i]>max)
					max=a[i];
			}
			for(int i=0;i<n;++i)
				cout<<a[i]<<" ";
			cout<<"\n";
			delete[] a;
		}
	}
}
