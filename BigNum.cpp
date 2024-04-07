#include <bits/stdc++.h>
using namespace std;

#define size(a) (int)a.size()
typedef long long ll;
typedef vector<long long> vll;

// -------------------------------- BigNum  -------------------------------- //

const int base = 1000000000;
const int base_digits = 9;

struct BigNum{
    int sign;
    // reverse order of digits
    vector<int> digits;

    void parse_string(const string& num){
        sign = 1;
        digits.clear();
        int pos = 0;
        if(num[0] == '-') sign = -1, ++pos;

        for(int i = size(num) - 1; i >= pos; i -= base_digits){
            int x = 0;
            for(int j = max(pos, i - base_digits + 1); j <= i; j++) x = x * 10 + num[j] - '0';
            digits.push_back(x);
        }
        prettify();
    }

    string to_string() {
        stringstream stream;
        stream << *this;
        string ret;
        stream >> ret;
        return ret;
    }

    BigNum() : sign(1) {}
    BigNum(ll n) { *this = n; }
    BigNum(const string& num) { parse_string(num); }

    BigNum prettify(){
        while(!digits.empty() && !digits.back()) digits.pop_back();
        if(digits.empty()) sign = 1;
        return *this;
    }

    int length() const {
        if(digits.empty()) return 0;
        int ret = (size(digits) - 1) * base_digits;
        int temp = digits.back();
        while(temp) ret++, temp /= 10;
        return ret;
    }

    void operator=(ll n){
        sign = 1;
        if(n < 0) sign = -1, n = -n;
        for(; n > 0; n /= base)
            digits.push_back((int) (n % base));
    }

    void operator=(const string& num){
        parse_string(num);
    }

    // void operator=(const BigNum& d){
    //     sign = d.sign;
    //     digits = d.digits;
    // }

    BigNum operator -() const {
        BigNum res = *this;
        res.sign *= -1;
        return res;
    }

    BigNum abs() const {
        BigNum res = *this;
        res.sign = 1;
        return res;
    }
    
    
    BigNum operator+(BigNum const& d) const {
        if(sign == d.sign) {
            BigNum res = d;
            int carry = 0;
            for(int i = 0; i < max(size(digits), size(d.digits)) || carry; i++){
                if(i == size(res.digits))
                    res.digits.push_back(0);
                res.digits[i] += carry + (i < size(digits) ? digits[i] : 0);
                carry = res.digits[i] >= base;
                if(carry)
                    res.digits[i] -= base;
            }
            
            return res;
        }
        return *this - (-d);
    }   

    BigNum operator+(ll n) const {
        return *this + BigNum(n);
    } 

    BigNum operator-(BigNum const& d) const {
        if(sign == d.sign){
            if(abs() >= d.abs()){ 
                BigNum res = *this;
                int carry = 0;
                for(int i = 0; i < max(size(digits), size(d.digits)) || carry; i++){
                    res.digits[i] -= carry + (i < size(d.digits) ? d.digits[i] : 0);
                    carry = res.digits[i] < 0;
                    if(carry)
                        res.digits[i] += base;
                }
                
                return res.prettify();
            }
            return -(d - *this);
        }
        return *this + (-d);
    }

    BigNum operator-(ll n) const {
        return *this - BigNum(n);
    }

    // BigNum operator*(BigNum const& d) const {
    //     // TODO: implement karatsuba
    //     vll a(digits.begin(), digits.back());
    //     vll b(d.digits.begin(), d.digits.back());
        
    // }

    // void operator*=(BigNum const& d){
    //     *this = *this * d;
    // }

    void operator*=(int n){
        if(n < 0) sign = -sign, n = -n;
        int carry = 0;
        for (int i = 0; i < size(digits) || carry; i++) {
			if (i == size(digits))
				digits.push_back(0);
			long long cur = digits[i] * (long long) n + carry;
			carry = (int) (cur / base);
			digits[i] = (int) (cur % base);
		}
		prettify();
    }

    BigNum operator*(int n) const {
        BigNum res = *this;
        res *= n;
        return res;
    }

    // BigNum operator^(ll n) const {
    //     // fastpow
    //     BigNum res(1), b = *this;
    //     while(n){
    //         if(n & 1) res *= b;
    //         b *= b;
    //         n >>= 1;
    //     }
    //     return res;
    // }

    void operator+=(BigNum const& d){
        *this = *this + d;
    }

    void operator-=(BigNum const& d){
        *this = *this - d;
    }

    // void operator^=(ll n){
    //     *this = *this ^ n;
    // }

    bool operator==(BigNum const& d) const {
        return !(*this < d) && !(d < *this);
    }

    bool operator==(ll n) const {
        if(n == 0 && digits.empty()) return true;
        return (*this) == BigNum(n);
    }

    bool operator<(BigNum const& d) const {
        if(sign != d.sign) return sign < d.sign;
        if(size(digits) != size(d.digits)) return size(digits) * sign < size(d.digits) * d.sign;
        for(int i = size(digits) - 1; i >= 0; i--)
            if(digits[i] != d.digits[i])
                return digits[i] * sign < d.digits[i] * d.sign;
        return false;
    }

    bool operator>(BigNum const& d) const {
        return d < *this;
    }

    bool operator<=(BigNum const& d) const {
        return !(d < *this);
    }

    bool operator>=(BigNum const& d) const {
        return !(*this < d);
    }

    bool operator!=(BigNum const& d) const {
        return !(*this == d);
    }


    int sum_of_digits() {
        int ret = 0;
        string s = to_string();
        for(auto i : s) ret += (i - '0');
        return ret;
    }

    static BigNum factorial(int n) {
        BigNum res(1);
        for(int i = 2; i <= n; ++i) res *= i, cout << i << "\n";
        return res;
    }
    
    friend ostream& operator<<(ostream& stream, const BigNum& d){
        if(d.sign == -1) stream << "-";
        stream << (d.digits.empty() ? 0 : d.digits.back());
        for(int i = size(d.digits) - 2; i >= 0; --i){
            stream << setw(base_digits) << setfill('0') << d.digits[i];
        }
        return stream;
    }  

    friend istream& operator>>(istream& stream, BigNum& d){
        string s;
        stream >> s;
        d.parse_string(s);
        return stream; 
    }
};



int main(){
    // while(1){
    //     BigNum a, b;
    //     cin >> a >> b;
    //     cout << a << "\n" << b << "\n";
    //     cout << a + b << "\n";
    //     cout << a - b << "\n";
    //     cout << (a < b) << "\n";
    //     cout << (a == b) << "\n";
    //     a = b;     
    // }
    int n; //cin>>n;
    n = 100000;
    BigNum essa = BigNum::factorial(n);
    cout << essa << "\n";
    cout << essa.length() << "\n";
    cout << essa.sum_of_digits() << "\n";

    return 0;

}