#include <bits/stdc++.h>
#include "Decimal.cpp"
using namespace std;

#define size(a) (int)a.size()
typedef long long ll;


int main(){
    Decimal a(2);
    Decimal b = a^1000;
    cout << b.sum_of_digits() << "\n";

    return 0;
}