#include<iostream>
#include<random>
#include<sstream>
using namespace std;

int main(int argc, char *argv[]) {
	int n_approx,k;
	stringstream(argv[1])>>n_approx;
	stringstream(argv[2])>>k;
	random_device device;
	uniform_int_distribution<int> distribution(1,n_approx/k);
	int *a = new int[k];
	for(int i=0;i<k;++i) {
		a[i] = distribution(device);
	}
	int n=0;
	for(int i=0;i<k;++i) {
		n+=a[i];
	}
	cout<<n<<" "<<k<<endl;
	for(int i=0;i<k;++i)
		cout<<a[i]<<" ";
	delete[] a;
	return 0;
}