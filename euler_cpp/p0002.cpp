#include "libs/Euler.h"
using namespace std;

const int N = 4e6;

void solve() {
	int a = 0, b = 1, ans = 0;
	while (b < N) {
		if (b % 2 == 0) ans += b;
		b = a + b;
		a = b - a;
	}
	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}