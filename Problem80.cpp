#include <bits/stdc++.h>
using namespace std;

#define upgrade ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pp pair<int, int>
#define size(a) (int)a.size()
typedef long long ll;
const int N = 1e6;

struct Decimal{
    // before and after the decimal point
    vector<short> before;
    vector<short> after;

    vector<short> stringToDecimal(string s){
        vector<short> ret;
        for(auto i : s) ret.push_back(i - '0');
        return ret;
    }

    vector<string> parse_string(string num){
        vector<string> ret;
        while(size(num) && num[0] == '0') num.erase(num.begin());
        while(size(num) && num.back() == '0') num.pop_back();

        int found = (int)num.find('.');
        if(found == string::npos){
            ret.push_back(num);
            ret.push_back("");
        }
        else{
            ret.push_back(num.substr(0, found));
            ret.push_back(num.substr(found + 1));
        }
        return ret;
    }

    Decimal() {}
    Decimal(ll n) : before(stringToDecimal(to_string(n))), after({}) {}
    Decimal(ll n, ll k) : before(stringToDecimal(to_string(n))), after(stringToDecimal(to_string(k))) {}
    Decimal(ll n, vector<short> a) : before(stringToDecimal(to_string(n))), after(a) {}
    Decimal(vector<short> b, vector<short> a) : before(b), after(a) {}
    Decimal(string num) : before(stringToDecimal(parse_string(num)[0])), after(stringToDecimal(parse_string(num)[1])) {}

    Decimal prettify(){
        while(size(before) > 1 && before[0] == 0) before.erase(before.begin());
        if(!size(before)) before.push_back(0);
        while(size(after) > 1 && after.back() == 0) after.pop_back();
        return *this;
    }
    
    Decimal operator+(Decimal const& d){
        vector<short> bret, aret;
        short carry = 0;
        int n = size(after), k = size(d.after);
        for(int i = max(n, k) - 1; i >= 0; i--){
            short sum = carry;
            if(i < n) sum += after[i];
            if(i < k) sum += d.after[i];
            aret.push_back(sum % 10);
            carry = sum / 10;
        }
        reverse(aret.begin(), aret.end());
        n = size(before), k = size(d.before);
        for(int i = 0; i <= max(n, k) - 1; i++){
            short sum = carry;
            if(i < n) sum += before[n-i-1];
            if(i < k) sum += d.before[k-i-1];
            bret.push_back(sum % 10);
            carry = sum / 10;
        }
        if(carry) bret.push_back(carry);
        reverse(bret.begin(), bret.end());
        // return the prettified version
        return Decimal(bret, aret).prettify();
    }    

    Decimal operator-(Decimal const& d){
        vector<short> bret, aret;
        short carry = 0;
        int n = size(after), k = size(d.after);
        for(int i = max(n, k) - 1; i >= 0; i--){
            short sum = carry;
            if(i < n) sum += after[i];
            if(i < k) sum -= d.after[i];
            if(sum < 0){
                sum += 10;
                carry = -1;
            }
            else carry = 0;
            aret.push_back(sum);
        }
        reverse(aret.begin(), aret.end());
        n = size(before), k = size(d.before);
        for(int i = 0; i <= max(n, k) - 1; i++){
            short sum = carry;
            if(i < n) sum += before[n-i-1];
            if(i < k) sum -= d.before[k-i-1];
            if(sum < 0){
                sum += 10;
                carry = -1;
            }
            else carry = 0;
            bret.push_back(sum);
        }
        reverse(bret.begin(), bret.end());
        // return the prettified version
        return Decimal(bret, aret).prettify();
    }

    Decimal operator*(Decimal const& d){
        // TODO: implement karatsuba
        vector<short> x = before;
        x.insert(x.end(), after.begin(), after.end());
        vector<short> y = d.before;
        y.insert(y.end(), d.after.begin(), d.after.end());
        int n = size(x), k = size(y);
        int decimal_point = size(after) + size(d.after);
        reverse(x.begin(), x.end());
        reverse(y.begin(), y.end());

        vector<short> ret(n + k, 0);
        for(int i = 0; i < n; i++){
            short carry = 0;
            for(int j = 0; j < k; j++){
                short sum = ret[i+j] + x[i] * y[j] + carry;
                ret[i+j] = sum % 10;
                carry = sum / 10;
            }
            ret[i+k] += carry;
        }

        
        reverse(ret.begin(), ret.end());
        auto it = ret.end() - decimal_point;
        return Decimal(vector<short>(ret.begin(), it), vector<short>(it, ret.end())).prettify();
        
    }

    Decimal operator+=(Decimal const& d){
        *this = *this + d;
        return *this;
    }

    Decimal operator-=(Decimal const& d){
        *this = *this - d;
        return *this;
    }

    Decimal operator*=(Decimal const& d){
        *this = *this * d;
        return *this;
    }

    bool operator==(Decimal const& d){
        return before == d.before && after == d.after;
    }

    bool operator<(Decimal const& d){
        if(size(before) != size(d.before)) return size(before) < size(d.before);
        for(int i = 0; i < size(before); i++){
            if(before[i] != d.before[i]) return before[i] < d.before[i];
        }
        if(size(after) != size(d.after)) return size(after) < size(d.after);
        for(int i = 0; i < size(after); i++){
            if(after[i] != d.after[i]) return after[i] < d.after[i];
        }
        return false;
    }

    ll sum_of_decimal_digits(){
        ll ret = 0;
        for(auto i : before) ret += i;
        for(auto i : after) ret += i;
        return ret;
    }

    friend ostream& operator<<(ostream& os, const Decimal& d){
        for(auto i : d.before) os << i;
        if(size(d.after)){
            os << ".";
            for(auto i : d.after) os << i;
        }
        return os;
    }   
};


int main(){
    // upgrade

    // Testing
    // Decimal a("1");
    // while(1){
    //     string n, k;
    //     cin >> n >> k;
    //     Decimal x(n), y(k);
    //     cout << x << " " << y << "\n";
    //     cout << x * y << "\n";
    //     cout << x + y << "\n";
    //     cout << x - y << "\n";
    //     if(x < y) cout << "x < y\n";
    //     else if(x == y) cout << "x == y\n";
    //     else cout << "x > y\n";
    // }

    ll ans = 0;
    set<int> squares = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    for(int i = 2; i <= 100; i++){
        if(!squares.count(i)){
            int lower = sqrt(*(--lower_bound(squares.begin(), squares.end(), i)));
            Decimal x(lower);
            Decimal y(i);
            for(int j = 0; j < 99; j++){
                vector<short> a;
                for(int k = 0; k < j; k++) a.push_back(0);
                a.push_back(1);
                while(x * x < y){
                    x += Decimal(0, a);
                    // cout << x << " " << x*x << "\n";
                }
                x -= Decimal(0, a);
            }
            cout << x << "\n";
            ans += x.sum_of_decimal_digits();
            cout << i << " " << ans << "\n";
        }
    }
    

    return 0;
}