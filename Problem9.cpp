#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()


void solve(){
    for(int i = 1; i < 1000; i++){
        for(int j = i; j < 1000; j++){
            for(int k = j; k < 1000; k++){
                if(i * i + j * j == k * k && i + j + k == 1000){
                    cout << i * j * k << "\n";
                    return;
                }
            }
        }
    }
}


int main(){
    // upgrade
    solve();


    return 0;
}