#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
typedef long long ll;

const long double eps = 1/12345.0;
set<ll> powers;

void prep(){
    ll i = 2;
    while(i <= 1e18){
        powers.insert(i);
        i *= 2;
    }
}

int main(){
    // upgrade
    prep();
    // 4^t = 2^t + k, k is an inrteger
    // k = (2^t)^2 - 2^t
    int perf = 0, nperf = 0;
    for(ll t2=2; t2<=1e6; t2++){
        // cout << log(t2)/log(2) << "\n";
        // cout << "k = " << t2*t2 - t2 << "\n";
        if(powers.count(t2))
            perf++;
        else
            nperf++;

        if(perf/(long double)(perf+nperf) < eps){
            cout << t2*t2 - t2 << "\n";
            break;
        }
    }
    cout << perf << " " << perf + nperf << "\n";


    return 0;
}