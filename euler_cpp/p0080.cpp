#include "libs/Decimal.hpp"
#include "libs/Euler.h"
using namespace std;

const int N = 1e6;

void solve() {
	ll ans = 0;
	set<int> squares = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
	for (int i = 2; i <= 100; i++) {
		if (!squares.count(i)) {
			int lower =
				sqrt(*(--lower_bound(squares.begin(), squares.end(), i)));
			Decimal x(lower);
			Decimal y(i);
			for (int j = 0; j < 99; j++) {
				vector<short> a;
				for (int k = 0; k < j; k++) a.push_back(0);
				a.push_back(1);
				while (x * x < y) {
					x += Decimal(0, a);
					// cout << x << " " << x*x << "\n";
				}
				x -= Decimal(0, a);
			}
			cout << x << "\n";
			ans += x.sum_of_digits();
			cout << i << " " << ans << "\n";
		}
	}
}

int main() {
	solve();
	return 0;
}