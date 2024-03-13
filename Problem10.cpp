#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef long long ll;

const int N = 2e6;
bitset<N+1> is_prime;

void sieve(){
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i <= sqrt(N); i++){
        if(is_prime[i]){
            for(int j = i * i; j <= N; j += i)
                is_prime[j] = 0;
        } 
    }

    ll ans = 0;
    for(int i=0;i<=N;i++)
        if(is_prime[i])
            ans += i;
    
    cout << ans << "\n";
    
}


int main(){
    // upgrade
    sieve();


    return 0;
}