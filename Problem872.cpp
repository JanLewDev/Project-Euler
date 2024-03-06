#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
const int N = 1e6;

vector<int> subsets;
vector<pp> squares = {{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};

int main(){
    // upgrade
    int n = 10, m = 6;
    for(int i=0; i<(1 << n); i++)
        if(__builtin_popcount(i) == m)
            subsets.push_back(i);

    int ans = 0;
    for(int i=0; i<size(subsets); i++){
        for(int j=i; j<size(subsets); j++){
            int a = subsets[i], b = subsets[j];
            
            vector<int> cube1, cube2;
            for(int l=0; l<10; l++){
                if(a & (1<<l)) cube1.push_back(l);
                if(b & (1<<l)) cube2.push_back(l);
            } 

            bool ok = true;
            if(count(cube1.begin(), cube1.end(), 6) && !count(cube1.begin(), cube1.end(), 9))
                cube1.push_back(9);
            if(count(cube1.begin(), cube1.end(), 9) && !count(cube1.begin(), cube1.end(), 6))
                cube1.push_back(6);
            if(count(cube2.begin(), cube2.end(), 6) && !count(cube2.begin(), cube2.end(), 9))
                cube2.push_back(9);
            if(count(cube2.begin(), cube2.end(), 9) && !count(cube2.begin(), cube2.end(), 6))
                cube2.push_back(6);
            for(int k=0; k<size(squares); k++){
                if((!count(cube1.begin(), cube1.end(), squares[k].first) || !count(cube2.begin(), cube2.end(), squares[k].second)) && (
                    !count(cube1.begin(), cube1.end(), squares[k].second) || !count(cube2.begin(), cube2.end(), squares[k].first)
                ))
                    ok = false;
            }
            if(ok){
                ans++;
                // cout << "a: ";
                // for(auto x: cube1)
                //     cout << x << " ";
                // cout << "\nb: ";
                // for(auto x: cube2)
                //     cout << x << " ";
                // cout << "\n\n";
            }
        }
    }

    cout << ans << "\n";

    return 0;
}