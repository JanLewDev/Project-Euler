#include <bits/stdc++.h>
using namespace std;

#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef long long ll;
const int N = 1e5;
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
    
}

void solve(){
    sieve();
    for(int i = 1e3; i < 1e4; i++){
        if(is_prime[i]){
            string s = to_string(i);
            sort(all(s));
            string original = s;
            do{
                int x = stoi(s);
                if(is_prime[x] && x > i){
                    int y = i + (2 * (x - i));
                    if(y < N && is_prime[y]){
                        string t = to_string(y);
                        sort(all(t));
                        if(t == original){
                            cout << i << x << y << "\n";
                        }
                    }
                }
            }while(next_permutation(all(s)));
        }
    }
    
}


int main(){
    solve();

    return 0;
}