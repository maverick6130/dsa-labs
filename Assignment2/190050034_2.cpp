#include<iostream>
using namespace std;

int main() {
	int n,k;
	cin>>n>>k;
	int *a = new int[k];
	for(int i=0;i<k;++i)
		cin>>a[i];
	
	if(k==1)
		return 0;
	
	int max2,mi2,max,mi;
	do {
		max=0;mi=k;
		for(int i=0;i<k;++i) {
			if(a[i]>max) {
				max = a[i];
				mi = i;
			}
		}
		max2=0;mi2=k;
		for(int i=0;i<k;++i) {
			if(i==mi)
				continue;
			if(a[i]>max2) {
				max2 = a[i];
				mi2 = i;
			}
		}
		if(max2!=0) {
			a[mi2] = 0;
			for(int i=0;i<k;++i) {
				a[i]+=max2/k;
			}
			for(int i=1;i<=max2%k;++i) {
				a[(mi2+i)%k]+=1;
			}
			cout<<mi2<<" ";
		}
		else {
			cout<<mi<<" ";
		}
	}while(max2!=0);
	
	delete[] a;
	return 0;
}