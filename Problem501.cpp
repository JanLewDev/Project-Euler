#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef unsigned long long ull;
typedef long long ll;

vector<int> primes;
const int N = 1e6+5;

// PrimePi function from https://am-just-a-nobody.blogspot.com/2015/11/c-code-for-primepi-function.html
// I modified it to suit my needs

ull PrimePi(ull n){
    // quick binsearch for small n
    if(n < primes.back()){
        auto it = upper_bound(all(primes), n);
        return it - primes.begin();
    }

    int v = sqrt(n);
    vector<ull> Lower(v+5, 0), Higher(v+5, 0);
    vector<bool> Used(v+5, 0);
    
    // assume all numbers are primes, then subtract the non-primes
    ull res = n - 1;

    for(int p = 2; p <= v; p++) {
        Lower[p] = p - 1;
        Higher[p] = n / p - 1;
    }

    for(ull p = 2; p <= v; p++) {
        // non-prime?
        if(Lower[p] == Lower[p-1])
            continue;

        ull temp = Lower[p-1];
        ull q = p * p;
        res -= Higher[p] - temp;

        int j = 1 + (p & 1);
        ull end = (v <= n/q) ? v : n/q;

        for(int i = p + j; i <= 1 + end; i += j) {
            if(Used[i])
                continue;

            ull d = i * p;
            if(d <= v)
                Higher[i] -= Higher[d] - temp;
            else 
                Higher[i] -= Lower[n / d] - temp;
        }
        for(ull i = q; i <= end; i += p*j)
            Used[i] = 1;

        for(ull i = v; i >= q; i--) 
            Lower[i] -= Lower[i / p] - temp;

    }
    return res;
}

void sieve(){
    bitset<N+1> is_prime;
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i <= sqrt(N); i++){
        if(is_prime[i]){
            for(int j = i * i; j <= N; j += i)
                is_prime[j] = 0;
        } 
    }

    for(int i=0;i<=N;i++)
        if(is_prime[i])
            primes.push_back(i);
    
}

ull fastpow(ull a, ull b) {
    ull res = 1;
    while(b){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

ll eightDivisors(ll n){
    ll ans = 0;
    sieve();
    // check for p1^7
    for(auto i : primes){
        if(fastpow(i, 7) <= n) ans++;
        else break;
    }
    cout << "Stage 1: " << ans << "\n";
    // check for p1^3 * p2
    for(auto i : primes){
        if(fastpow(i, 3) <= n){
            ull deficit = n / fastpow(i, 3);
            if(deficit <= 1) break;
            ull add = PrimePi(deficit);
            if(deficit > i)
                add--;
            ans += add;
            // cout << i << " " << deficit << " " << PrimePi(deficit) << " " << ans << "\n";
        }
        else break;
    }

    cout << "Stage 2: " << ans << "\n";
    // check for p1 * p2 * p3
    for(int i = 0; i < size(primes); i++){
        if(fastpow(primes[i], 3) > n) break;

        for(int j = i + 1; j < size(primes); j++){
            ull deficit = n / (primes[i] * primes[j]);
            if(deficit < j) break;
            ll add = PrimePi(deficit) - j - 1;
            if(add > 0) ans += add;
            else break;
            // cout << primes[i] << " " << primes[j] << " " << deficit << " " << PrimePi(deficit) << " " << ans << "\n";
        }
    }

    cout << "Stage 3: " << ans << "\n";
    return ans;
}

int main(){
    // upgrade
    // eight divisors
    // only possibilities p1 * p2 * p3, p1^3 * p2, p1^7
    // p1, p2, p3 are primes
    ll n = 1e12; 
    
    cout << eightDivisors(n) << "\n";
    // cout << PrimePi(n) << "\n";
    // stage 2 - 7297845295
    return 0;
}