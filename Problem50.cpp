#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int N = 1e6;

bitset<N+1> is_prime;
vector<int> primes;

void SieveofEratosthenes(){
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= sqrt(N); i++){
        if(is_prime[i]){
            for(int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        } 
    }
    for(int i=0;i<=N;i++)
        if(is_prime[i])
            primes.push_back(i);

}

int main(){
    // upgrade
    is_prime.set();
    SieveofEratosthenes();
    
    int maxsum = 0;
    int longest = -1;

    for(int i = 0; i < (int)primes.size(); i++){

        int sum = 0;
        for(int j = i; j < (int)primes.size(); j++){
            sum += primes[j];
            if(sum > N)
                break;
            
            if(is_prime[sum] && sum > maxsum && j - i > longest){
                longest = j - i;
                maxsum = sum;
            }
        } 
    }

    cout << maxsum << "\n";
    return 0;
}