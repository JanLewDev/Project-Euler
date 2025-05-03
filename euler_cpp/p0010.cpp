#include "libs/Euler.h"
using namespace std;

const int N = 2e6;
bitset<N + 1> is_prime;

// Sieve of Eratosthenes
void solve() {
	is_prime.set();
	is_prime[0] = is_prime[1] = 0;
	for (int i = 2; i <= sqrt(N); i++) {
		if (is_prime[i]) {
			for (int j = i * i; j <= N; j += i) is_prime[j] = 0;
		}
	}

	ll ans = 0;
	for (int i = 0; i <= N; i++)
		if (is_prime[i]) ans += i;

	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}