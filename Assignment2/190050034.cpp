#include<iostream>
using namespace std;

int main() {
	int n,k;
	cin>>n>>k;
	int *a = new int[k];
	for(int i=0;i<k;++i)
		cin>>a[i];
	
	int min,mi;
	do {
		min = n+1;
		mi = k;
		for(int i=0;i<k;++i) {
			if((a[i]!=0) && (a[i]<min)) {
				min = a[i];
				mi = i;
			}
		}
		a[mi] = 0;
		for(int i=0;i<k;++i) {
			a[i]+=min/k;
		}
		for(int i=1;i<=min%k;++i) {
			a[(mi+i)%k]+=1;
		}
		cout<<mi<<" ";
	}while(min!=n);
	
	delete[] a;
	return 0;
}