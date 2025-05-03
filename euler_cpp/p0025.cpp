#include "libs/Decimal.hpp"
#include "libs/Euler.h"
using namespace std;

void solve() {
	Decimal a(1);
	Decimal b(1);
	for (int i = 3;; i++) {
		Decimal c = a + b;
		a = b;
		b = c;
		if (c.sum_of_digits() >= 1000) {
			cout << i << "\n";
			break;
		}
	}
}

int main() {
	solve();
	return 0;
}