#include "libs/Euler.h"
using namespace std;

void solve() {
	int a = 0, b = 0;
	for (int i = 1; i <= 100; i++) {
		a += i * i;
		b += i;
	}
	cout << b * b - a << "\n";
}

int main() {
	solve();
	return 0;
}