#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
#define all(a) a.begin(), a.end()
typedef long long ll;

vector<vector<int>> matrix;


int dp(){
    int n = size(matrix), m = size(matrix[0]);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i == 0 && j == 0) continue;
            if(i == 0) matrix[i][j] += matrix[i][j - 1];
            else if(j == 0) matrix[i][j] += matrix[i - 1][j];
            else matrix[i][j] += min(matrix[i - 1][j], matrix[i][j - 1]);
        }
    }
    return matrix[n - 1][m - 1];
}

int main(){
    ifstream in;
    string s;
    in.open("0081_matrix.txt");
    while(getline(in, s)){
        stringstream ss(s);
        matrix.push_back({});
        while(getline(ss, s, ',')){
            matrix.back().push_back(stoi(s));
        }
    }
    in.close();
    cout << dp();


    return 0;
}