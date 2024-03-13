#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()


void solve(){
    int a = 0, b = 0;
    for(int i = 1; i <= 100; i++){
        a += i * i;
        b += i;
    }
    cout << b * b - a << "\n";
}


int main(){
    // upgrade
    solve();


    return 0;
}