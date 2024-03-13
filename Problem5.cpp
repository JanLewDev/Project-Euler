#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef long long ll;

void solve(int n){
    int lcm = 1;
    for(int i = 2; i <= n; i++){
        lcm *= (i / __gcd(i, lcm));
    }

    cout << lcm << "\n";
}


int main(){
    // upgrade
    solve(20);


    return 0;
}