#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()


void solve(){
    int ans = 0;
    for(int i = 100; i < 1000; i++){
        for(int j = 100; j < 1000; j++){
            int num = i * j;
            string s = to_string(num);
            string t = s;
            reverse(t.begin(), t.end());
            if(s == t) ans = max(ans, num);
        }
    }
    cout << ans << "\n";
}


int main(){
    // upgrade
    solve();


    return 0;
}