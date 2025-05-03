#include "libs/Euler.h"
using namespace std;

void solve(int n) {
	int lcm = 1;
	for (int i = 2; i <= n; i++) {
		lcm *= (i / gcd(i, lcm));
	}

	cout << lcm << "\n";
}

int main() {
	solve(20);
	return 0;
}