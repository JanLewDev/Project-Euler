#include "libs/Euler.h"
using namespace std;

const int N = 1e7 + 5;
bitset<N> primes;

bool prime(ll n) {
	for (ll i = 3; i <= sqrt(n); i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}

ll factor(ll lim) {
	ll ans;
	primes.set();
	primes[0] = primes[1] = 0;
	for (int i = 2; i <= sqrt(lim); i++) {
		if (primes[i]) {
			if (lim % i == 0)
				if (prime(lim / i))
					ans = lim / i;
				else
					ans = i;
			for (int j = (i < sqrt(N) ? i * i : N); j < N; j += i) {
				primes[j] = 0;
			}
		}
	}
	return ans;
}

void solve() { cout << factor(600851475143) << "\n"; }

int main() {
	solve();
	return 0;
}