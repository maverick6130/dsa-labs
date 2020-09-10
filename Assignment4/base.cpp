#include<iostream>
#include<string>
#include<random>
#include<chrono>
using namespace std;

int main() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,19891);
	char s[149];
	char out[149*137];
	for(int i=0;i<149;++i)
		s[i]=char('a'+distribution(generator)%26);
	for(int i=0;i<137;++i)
		for(int j=0;j<149;++j)
			out[149*i+j]=s[j];
	for(int i=0;i<1900;++i)
		out[distribution(generator)] = char(distribution(generator)%26+'a');
	for(int i=0;i<19891;++i)
		cout<<out[i];
	cout<<endl;
	cout<<137;
}
