#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int> primes (1,2);
	for(int n=3;n<=20000;++n) {
		bool flag=true;
		for(auto x : primes) {
			if(n%x==0) {
				flag=false;
				break;
			}
		}
		if(flag)
			primes.push_back(n);
	}
	cout<<primes.size();
}
