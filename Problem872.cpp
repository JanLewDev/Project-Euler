#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
typedef unsigned long long ull;

ull fastpow(ull a, ull b) {
    ull res = 1;
    while(b){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

int main(){
    // upgrade
    ull n = fastpow(10, 17), k = fastpow(9, 17);
    // ull n, k;
    // cin >> n >> k;
    
    ull diff = n - k;
    bitset<64> b(diff);
    cout << b << "\n";
    cout << __builtin_clzll(n-k) << "\n";
    ull ans = n;
    ull curr = n;
    for(int i=0; i < 64 - __builtin_clzll(diff); i++){
        if(b[i]){
            ans += (curr - fastpow(2, i));
            curr -= fastpow(2, i);
        }
    }

    cout << ans << "\n";

    return 0;
}