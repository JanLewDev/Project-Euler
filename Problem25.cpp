#include <bits/stdc++.h>
#include "Decimal.cpp"
using namespace std;

#define size(a) (int)a.size()
typedef long long ll;

int main(){
    Decimal a(1);
    Decimal b(1);
    for(int i = 3; ; i++){
        Decimal c = a + b;
        a = b;
        b = c;
        if(c.count_digits() >= 1000){
            cout << i << "\n";
            break;
        }
    }
        

    return 0;
}