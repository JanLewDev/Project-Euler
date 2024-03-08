#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()

const int N = 4e6;

void solve(){
    int a = 0, b = 1, ans = 0;
    while(b < N){
        if(b % 2 == 0) ans += b;
        b = a + b;
        a = b - a;
    }
    cout << ans << "\n";
}


int main(){
    // upgrade
    solve();


    return 0;
}