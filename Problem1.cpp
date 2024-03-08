#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()


void solve(){
    int ans = 0;
    for(int i = 3; i < 1000; i += 3){
        ans += i;
    }
    for(int i = 5; i < 1000; i += 5){
        if(i % 3 != 0) ans += i;
    }
    cout << ans << "\n";
}


int main(){
    // upgrade
    solve();


    return 0;
}