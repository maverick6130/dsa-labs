#include<iostream>
using namespace std;

void distribute(int a[],int &k,int &pos) {
	if(a[pos]==0)
		return;
	else {
		int dist = a[pos];
		a[pos] = 0;
		for(int i=0;i<k;++i) {
			a[i]+=dist/k;
		}
		for(int i=1;i<=dist%k;++i) {
			a[(pos+i)%k]+=1;
		}
		cout<<pos<<" ";
	}
}

int main() {
	int n,k;
	cin>>n>>k;
	int *a = new int[k];
	for(int i=0;i<k;++i)
		cin>>a[i];

	int mi=0;
	for(int i=1;i<k;++i)
		if(a[i]>a[mi])
			mi = i;
	
	if(a[mi]==(n+k-1)/k)
		return 0;
	
	while(a[mi]!=n){
		for(int i=0;i<k;++i)
			if(i!=mi)
				distribute(a,k,i);
	}
	distribute(a,k,mi);

	delete[] a;
	return 0;
}