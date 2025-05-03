#include "libs/Euler.h"
using namespace std;

void solve() {
	int ans = 0;
	for (int i = 3; i < 1000; i += 3) {
		ans += i;
	}
	for (int i = 5; i < 1000; i += 5) {
		if (i % 3 != 0) ans += i;
	}
	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}