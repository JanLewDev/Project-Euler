#include "libs/Euler.h"
using namespace std;

void solve() {
	ll ans = 0;
	for (int i = 1; i <= 1e6; i++) {
		string s = to_string(i);
		string t = s;
		reverse(t.begin(), t.end());
		if (s == t) {
			string b = bitset<32>(i).to_string();
			int lz = __builtin_clz(i);
			b = b.substr(lz);
			string c = b;
			reverse(c.begin(), c.end());
			if (b == c) ans += i;
		}
	}
	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}