#include "libs/Euler.h"
using namespace std;

const int N = 1e6;

bitset<N + 1> is_prime;
vector<int> primes;

void SieveofEratosthenes() {
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i <= sqrt(N); i++) {
		if (is_prime[i]) {
			for (int j = i * i; j <= N; j += i) is_prime[j] = false;
		}
	}
	for (int i = 0; i <= N; i++)
		if (is_prime[i]) primes.push_back(i);
}

void solve() {
	is_prime.set();
	SieveofEratosthenes();

	int maxsum = 0;
	int longest = -1;

	for (int i = 0; i < size(primes); i++) {
		int sum = 0;
		for (int j = i; j < size(primes); j++) {
			sum += primes[j];
			if (sum > N) break;

			if (is_prime[sum] && sum > maxsum && j - i > longest) {
				longest = j - i;
				maxsum = sum;
			}
		}
	}

	cout << maxsum << "\n";
}

int main() {
	solve();
	return 0;
}