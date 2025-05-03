#include "libs/Euler.h"
using namespace std;

const int N = 1e7 + 5;
bitset<N> primes;
vector<int> vprimes;

int sieve(int lim) {
	primes.set();
	primes[0] = primes[1] = 0;
	for (int i = 2; i < N; i++) {
		if (primes[i]) {
			vprimes.push_back(i);
			if (size(vprimes) == lim) return i;
			for (int j = (i < sqrt(N) ? i * i : N); j < N; j += i) {
				primes[j] = 0;
			}
		}
	}
	return 0;
}

void solve() { cout << sieve(10001) << "\n"; }

int main() {
	solve();
	return 0;
}