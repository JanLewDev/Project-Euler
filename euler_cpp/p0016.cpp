#include "libs/Decimal.hpp"
#include "libs/Euler.h"
using namespace std;

void solve() {
	Decimal a(2);
	Decimal b = a ^ 1000;
	cout << b.sum_of_digits() << "\n";
}

int main() {
	solve();
	return 0;
}