#include<iostream>
#include <map>
#include <unordered_map>
using namespace std;

// FRACTION CLASS START --------------------------
template<typename T>
T gcd(T a, T b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

template<typename T>
class Fraction {
	
public:
	T a;
	T b; /*   a/b  */
	Fraction() {
		a = b = T();
	}
	Fraction(T a, T b = 1) {
		this->a = a;
		this->b = b;
	}
	Fraction operator=(const Fraction& rhs) {
		this->a = rhs.a;
		this->b = rhs.b;
		return *this;
	}
	bool operator < (const Fraction & rhs) const {
		return this->a* rhs.b < rhs.a * this->b;
	}
	bool operator==(const Fraction& rhs) const {
		return this->a * rhs.b == rhs.a * this->b;
	}
    friend T gcd(T a, T b);
    Fraction normalize() const {
        Fraction t = *this;
        T gc = gcd(this->a, this->b);
        t.a /= gc;
        t.b /= gc;
        return t;
    }
	Fraction operator-(const Fraction& rhs) const {
		Fraction t;
		t.a = this->a * rhs.b - rhs.a * this->b;
		t.b = this->b * rhs.b;
		return this->normalize();
	}
	Fraction operator+(const Fraction& rhs) const {
		Fraction t;
		t.a = this->a * rhs.b + rhs.a * this->b;
		t.b = this->b * rhs.b;
		return this->normalize();
	}
	Fraction operator*(const Fraction& rhs) const {
		Fraction t;
		t.a = this->a * rhs.a;
		t.b = this->b * rhs.b;
		return this->normalize();
	}
	Fraction operator/(const Fraction& rhs) const {
		Fraction t = *this;
		swap(t.a, t.b);
		t = t * rhs;
		return this->normalize();
	}
	Fraction operator*=(const Fraction& rhs) {
		*this = (*this) * rhs;
		return *this;
	}
	Fraction operator+=(const Fraction& rhs) {
		*this = (*this) + rhs;
		return *this;
	}
	Fraction operator-=(const Fraction& rhs) {
		*this = (*this) - rhs;
		return *this;
	}
	Fraction operator/=(const Fraction& rhs) {
		*this = (*this) / rhs;
		return *this;
	}
	friend ostream& operator << (ostream& out, const Fraction& rhs) {
		out << rhs.a << "/" << rhs.b;
		return out;
	}
};
namespace std {
	template<typename T> struct hash<Fraction<T>>
	{
		size_t operator()(const Fraction<T>& rhs) const {
			Fraction<T> rhs_normalize = rhs.normalize();
			return hash<T>()(rhs_normalize.a ^ rhs_normalize.b);
		}
	};
}
// FRACTION CLASS END --------------------------


int main() {
	unordered_map<Fraction<int>, int> mp;
	Fraction<int> f1(2, 4);
	Fraction<int> f2(1, 2);
    cout << f1 << endl;
	cout << f2 << endl;
	if (f1 == f2) {
		cout << f1 << " == " << f2 << endl;
	}
	Fraction<int> f3 = f1 * f2;
	cout << f3 << endl;
	mp[f1]++;
	mp[f2]++;
	mp[f3]++;
	cout << f1 << " " << mp[f1] << endl;
	cout << f2 << " " << mp[f2] << endl;
	cout << f3 << " " << mp[f3] << endl;
	cout << mp.size() << endl; // should output 1 because all the fractions are same....
	return 0;
}