#include "libs/Euler.h"
using namespace std;

vector<int> continued_fraction(int n) {
	int a0 = sqrt(n);
	if (a0 * a0 == n) return {};
	int m = 0, d = 1, a = a0;
	vector<int> v;
	while (a != 2 * a0) {
		m = d * a - m;
		d = (n - m * m) / d;
		a = (a0 + m) / d;
		v.push_back(a);
	}
	return v;
}

void solve() {
	int ans = 0;
	for (int i = 2; i <= 1e4; i++) {
		vector<int> v = continued_fraction(i);
		if (size(v) % 2) ans++;
	}
	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}