#include "libs/Euler.h"
using namespace std;

void solve() {
	long long ll = 5e11, rr = 1e12;
	while (ll < rr) {
		long long b = (ll + rr) / 2;
		double r =
			0.5 * (sqrt(4 * b) * sqrt(2 * b - 2 + 1 / (4 * b)) - 2 * b + 1);
		if (r == (int)r) {
			cout << b << " " << (long long)r << "\n";
		}
		// cout << b << " " << (long long) r << "\n";
		if (b + r < 1e12)
			ll = b + 1;
		else
			rr = b;
	}
}

int main() {
	solve();
	return 0;
}