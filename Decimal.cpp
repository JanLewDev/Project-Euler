#include <bits/stdc++.h>
using namespace std;

#define size(a) (int)a.size()
typedef long long ll;

// ---------------- BigNum with arbitrary precision ---------------- //

struct Decimal{

    int sign;
    vector<short> before;
    vector<short> after;

    vector<short> stringToVector(const string& s){
        vector<short> ret;
        for(auto i : s) ret.push_back((short)(i - '0'));
        return ret;
    }

    void parse_string(string num){
        sign = 1;
        if(num[0] == '-'){
            sign = -1;
            num.erase(num.begin());
        }

        while(size(num) && num[0] == '0') num.erase(num.begin());
        while(size(num) && num.back() == '0') num.pop_back();

        int found = (int)num.find('.');
        if(found == string::npos){
            before = stringToVector(num);
        }
        else{
            before = stringToVector(num.substr(0, found));
            after = stringToVector(num.substr(found + 1));
        }
    }

    Decimal() {}
    Decimal(ll n) { parse_string(to_string(n)); }
    Decimal(ll n, ll k) { parse_string(to_string(n) + "." + to_string(k)); }
    Decimal(vector<short> b, vector<short> a) : before(b), after(a) {}
    Decimal(string num) { parse_string(num); }

    Decimal prettify(){
        while(size(before) > 1 && before[0] == 0) before.erase(before.begin());
        if(!size(before)) before.push_back(0);
        while(size(after) > 1 && after.back() == 0) after.pop_back();
        return *this;
    }

    void operator=(ll n){
        *this = Decimal(n);
    }

    Decimal operator -() const {
        Decimal res = *this;
        res.sign *= -1;
        return res;
    }

    Decimal abs(Decimal const& d) const {
        Decimal res = d;
        res.sign = 1;
        return res;
    }

    
    Decimal operator+(Decimal const& d) const {
        if(sign == d.sign) {
            int n = size(after), k = size(d.after);
            Decimal ret = (*this > d) ? *this : d;
            short carry = 0;
            ret.after.resize(max(n, k), 0);
            for(int i = max(n, k) - 1; i >= 0; i--){
                short sum = carry;
                if(i < n) sum += after[i];
                if(i < k) sum += d.after[i];
                ret.after[i] = sum % 10;
                carry = sum >= 10;
            }
            n = size(before), k = size(d.before);
            for(int i = 0; i < max(n, k); i++){
                short sum = carry;
                if(i < n) sum += before[n-i-1];
                if(i < k) sum += d.before[k-i-1];
                ret.before[max(n, k)-i-1] = sum % 10;
                carry = sum >= 10;
            }
            if(carry) ret.before.insert(ret.before.begin(), carry);
            
            return ret.prettify();
        }
        return *this - (-d);
    }   

    Decimal operator+(ll n) const {
        return *this + Decimal(n);
    } 

    Decimal operator-(Decimal const& d) const {
        if(sign == d.sign){
            if(abs(*this) >= abs(d)){ 
                int n = size(after), k = size(d.after);
                Decimal ret = *this;
                ret.after.resize(max(n, k), 0);
                short carry = 0;
                for(int i = max(n, k) - 1; i >= 0; i--){
                    short sum = carry;
                    if(i < n) sum += after[i];
                    if(i < k) sum -= d.after[i];
                    if(sum < 0){
                        sum += 10;
                        carry = -1;
                    } else carry = 0;
                    ret.after[i] = sum;
                }
                n = size(before), k = size(d.before);
                ret.before.resize(max(n, k), 0);
                for(int i = 0; i < max(n, k); i++){
                    short sum = carry;
                    if(i < n) sum += before[n-i-1];
                    if(i < k) sum -= d.before[k-i-1];
                    if(sum < 0){
                        sum += 10;
                        carry = -1;
                    }
                    else carry = 0;
                    ret.before[n-i-1] = sum;
                }
                
                return ret.prettify();
            }
            return -(d - *this);
        }
        return *this + (-d);
    }

    Decimal operator-(ll n) const {
        return *this - Decimal(n);
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

    Decimal operator^(ll n){
        // fastpow
        Decimal res(1);
        while(n){
            if(n & 1) res *= *this;
            *this *= *this;
            n >>= 1;
        }
        return res;
    }

    void operator+=(Decimal const& d){
        *this = *this + d;
    }

    void operator-=(Decimal const& d){
        *this = *this - d;
    }

    void operator*=(Decimal const& d){
        *this = *this * d;
    }

    void operator^=(ll n){
        *this = *this ^ n;
    }

    bool operator==(Decimal const& d) const {
        return sign == d.sign && before == d.before && after == d.after;
    }

    bool operator<(Decimal const& d) const {
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

    bool operator>(Decimal const& d) const {
        return d < *this;
    }

    bool operator<=(Decimal const& d) const {
        return !(d < *this);
    }

    bool operator>=(Decimal const& d) const {
        return !(*this < d);
    }

    bool operator!=(Decimal const& d) const {
        return !(*this == d);
    }

    ll sum_of_digits(){
        ll ret = 0;
        for(auto i : before) ret += i;
        for(auto i : after) ret += i;
        return ret;
    }

    int length(){
        return size(before) + size(after);
    }

    friend ostream& operator<<(ostream& os, const Decimal& d){
        if(d.sign == -1) os << "-";
        for(auto i : d.before) os << i;
        if(size(d.after)){
            os << ".";
            for(auto i : d.after) os << i;
        }
        return os;
    }  

    friend istream& operator>>(istream& stream, Decimal& d){
        string s;
        stream >> s;
        d.parse_string(s);
        return stream; 
    }
};



int main(){
    while(1){
        Decimal a, b;
        cin >> a >> b;
        cout << a + b << "\n";
        cout << a - b << "\n";
    }

    return 0;

}