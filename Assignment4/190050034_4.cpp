#include<string>
#include<iostream>
using namespace std;

int min_ops(const string &s,int n,int min_curr) {
	int oper = 0;
	int k = (s.length()+n-1)/n;
	if ((k*(s.length()/k)-s.length())>min_curr)
		return min_curr+1;
	for(int i=0;i<n;++i) {
		int c[26]={0};
		int mo=0;
		for(int j=i;j<s.length();j+=n)
			mo=max(++c[s[j]-'a'],mo);
		oper+=(k-mo);
	}
	return oper;
}

int main() {
	string s; int k;
	cin>>s>>k;
	cout<<min_ops(s,s.length()/k,s.length()+1)<<endl;
	int min=s.length()+1, min_k=0;
	for(int len=s.length()-1;len>0;len--) {
		int ml = min_ops(s,len,min);
		if(ml<min) {
			min = ml;
			min_k = (s.length()+len-1)/len;
		}
	}
	cout<<min<<" "<<min_k<<endl;
}
