#include "libs/Euler.h"
using namespace std;

void solve() {
	int ans = 0;
	for (int i = 100; i < 1000; i++) {
		for (int j = 100; j < 1000; j++) {
			int num = i * j;
			string s = to_string(num);
			string t = s;
			reverse(t.begin(), t.end());
			if (s == t) ans = max(ans, num);
		}
	}
	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}