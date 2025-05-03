#include "libs/Euler.h"
using namespace std;

const int digits = 10;
int n = 5;
const int max_sum = 9;
const int previous_digit = 10;

// ll dp[n][digits][max_sum + 1][previous_digit];
ll dp[20][digits][previous_digit];

void solve() {
	cin >> n;
	for (int i = 1; i < digits; i++) dp[0][i][0] = 1;
	for (int j = 0; j < digits; j++) {
		for (int l = 0; l < digits; l++) {
			if (j + l <= max_sum) dp[1][j][l] += dp[0][l][0];
		}
	}

	for (int i = 2; i < n; i++) {
		for (int j = 0; j < digits; j++) {		// current digit
			for (int l = 0; l < digits; l++) {	// previous digit
				for (int m = 0; m < previous_digit; m++) {
					if (m + j + l <= max_sum) dp[i][j][l] += dp[i - 1][j][m];
				}
			}
		}
	}
	// for(int i = 1; i < digits; i++) dp[0][i][i] = 1;
	// for(int i = 1; i < n; i++){
	//     for(int j = 0; j < digits; j++){
	//         for(int k = 0; k <= max_sum; k++){
	//             for(int l = 0; l < digits; l++){
	//                 if(k + l <= max_sum) dp[i][l][k + l] += dp[i - 1][j][k];
	//             }
	//         }
	//     }
	// }
	ll ans = 0;
	for (int i = 0; i < digits; i++) {
		for (int j = 0; j < previous_digit; j++) {
			ans += dp[n - 1][i][j];
			cout << dp[n - 1][i][j] << " ";
		}
		cout << "\n";
	}

	cout << ans << "\n";
}

int main() {
	solve();
	return 0;
}