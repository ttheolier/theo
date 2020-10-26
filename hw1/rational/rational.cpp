#include "rational.h"
#include <stdexcept>
//used algorithm because numeric wasnt allowing gcd to work
#include <algorithm>
// Libraries may be included as necessary

using namespace std;


Rational::Rational() : n(0), d(1) {}

Rational::Rational(int n, int d) {
    // Since the denominator cannot be zero an exception is thrown
    if (d == 0) {
        throw std::invalid_argument("division by zero");
    }


    // TODO: continue your implementation below.
    // You should likely set the member variables ad then call this->reduce()
    // and this->normalize().
    //normailzes or reduces based on case
    if (n==0)
    {
        this->n = n;
        this->d = d;
        this->normalize();
    }
    else
    {
    
        this->n = n;
        this->d = d;
        this->reduce();
    
    }
}

void Rational::normalize() {
    // In C++ you don't always have to use this-> to denote a member variable.
    // If you omit it, the compiler will infer that n and d are indeed members
    // of Rational. There are two reasons you will see or use this->:
    //
    // 1. If you have a local variable that has the same name as a member
    //    variable, you need to use this-> to differentiate the two. If you
    //    created `int n` on this next line, the compiler would decide that
    //    any consequent uses of that variable refer to the local n, not our
    //    member variable. To specifically access the member n in this
    //    scenario, we'd use this->n.
    //
    // 2. Style. Some people (like me, Noah, the guy writing this) prefer to
    //    to use this-> to make it clear what variables are members when
    //    reading through the code. Others use a prefix (m_, i.e. m_member) or
    //    a suffix (_, i.e. member_) to denote it. In assignments where you
    //    write your own classes, this will be up to you. For now, do as you
    //    wish, but don't forget readability :)
    //
    // And feel free to delete this huge comment.
    if (n == 0 && d != 1) {
        d = 1;
    }
}

Rational Rational::operator+(const Rational& rhs) const {
    // TODO
    int denom = this->d*rhs.d;
    int leftn= this->n*rhs.d;
    int rightn = rhs.n *this->d;
    int finaln = leftn+rightn;
    return Rational(finaln,denom);
    //this->n = num;
    //this->d = den;
}

Rational& Rational::operator+=(const Rational& rhs) {
    // TODO
    int denom = this->d*rhs.d;
    int leftn= this->n*rhs.d;
    int rightn = rhs.n *this->d;
    int finaln = leftn+rightn;
    this->n = finaln;
    this->d = denom;
    //cout<<this->n<<this->d<<endl;
    if (n==0)
    {
        this->normalize();
    }
    else
    {

        this->reduce();
    }
    return *this;
}

Rational Rational::operator*(int rhs) const {
    // TODO
    int num=this->n*rhs;
    return Rational(num,this->d);
    //int num = this->n*rhs->n;
    //int den = this->d*rhs->d;
}

// This operator isn't prefixed by Rational:: because it's not actually a
// member of Rational. It just tells the compiler what to do when it sees
// multiplication between an int on the left and a Rational on the right. Our
// friend declaration simply enabled us to access private members on the const
// Rational& rhs in the function body.
//
// Note that we could implement any of the other operators above this same way
// using the corresponding global operator and passing a const Rational& lhs as
// the first argument, it's just a matter of convenience.
Rational operator*(int lhs, const Rational& rhs) {
    // TODO
    int num=rhs.n*lhs;
    return Rational(num,rhs.d);
}

bool Rational::operator==(const Rational& other) const {
    // TODO
    //Need to do more for this
    if (double(this->n)/double(this->d) == double(other.n)/double(other.d))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TODO: implement the rest of your prototyped methods
//Insertion Operator
istream& operator>>(istream& in, Rational& r){

    char dummy;
    in >> r.n>>dummy>>r.d;
    if (r.n==0)
    {
        r.normalize();
    }
    else
    {
        r.reduce();
    }

    return in;
}
//os operator
ostream& operator<<(ostream& out, const  Rational& r) {
     out <<  r.n <<"/"<<r.d;

     return out;
}
//not equals comparion compares two doubles
bool Rational::operator!=(const Rational& other) const
{
    if (double(this->n)/double(this->d) == double(other.n)/double(other.d))
    {
        return false;
    }
    else
    {
        return true;
    }
}
//if gcd is zero
void Rational::reduce()
{
    //both posistive
    if (this->n>0 && this->d>0)
    {
        int gcd = __gcd(this->n,this->d);
        if (gcd <0)
        {
            gcd=-gcd;
        }
   
        if (gcd==0)
        {
            return;
        }
        else
        {
            this->n = this->n / gcd;
            this->d = this->d / gcd;
        }
    }
    //both negative
    if (this->n<0 && this->d<0)
    {
        int gcd = -(__gcd(this->n,this->d));
        if (gcd <0)
        {
            gcd=-gcd;
        }
        if (gcd==0)
        {
            return;
        }
        else
        {
            this->n = -(this->n / gcd);
            this->d = -(this->d / gcd);
        }
    }
    //only num negative
    if ((n<0 && d>0))
    {
        int gcd = -(__gcd(this->n,this->d));
        if (gcd <0)
        {
            gcd=-gcd;
        }
        if (gcd==0)
        {
            return;
        }
        else
        {
            this->n = this->n / gcd;
            this->d = this->d / gcd;
        }
    }
    //only denominator negative
    if ((n>0 && d<0))
    {
        int gcd = -(__gcd(this->n,this->d));
        if (gcd <0)
        {
            gcd=-gcd;
        }
        if (gcd==0)
        {
            return;
        }
        else
        {
            this->n = -(this->n / gcd);
            this->d = -(this->d / gcd);
        }
    }
    
    
}
//adds int to rational
Rational Rational::operator+(int rhs) const 
{
    int rhsd = this->d;
    int rhsn = rhsd*rhs;
    int finaln = rhsn + this->n;
    return Rational(finaln,rhsd);
}
//global for adding int on lhs
Rational operator+(int lhs, const Rational& rhs)
{
    int lhsd = rhs.d;
    int lhsn = lhsd*lhs;
    int finaln = lhsn + rhs.n;
    return Rational(finaln,lhsd);
}
//multiply two rationals
Rational Rational::operator*(const Rational& rhs) const
{
    int num = this->n*rhs.n;
    int den = this->d*rhs.d;
    return Rational(num,den);   

}
//exponentiation
Rational Rational::operator^(int rhs) const 
{
    //raised to zero
    if (rhs == 0)
    {
        int num = 1;
        int den =1;
        return Rational(num,den);
    }
    //raised to a positive
    if (rhs>0)
    {
        int onum = this->n;
        int oden = this->d;
        int num = this->n;
        int den = this->d;
        for (int i=1;i<rhs;i++)
        {
            num= num *onum;
            den = den * oden;
            //cout<<den<<endl;
        }
        return Rational(num,den);
    }
    //raised to a a negative
    else
    {
        int onum = this->n;
        int oden = this->d;
        int num = this->n;
        int den = this->d;
        for (int i=1;i<-rhs;i++)
        {
            num= num *onum;
            den = den * oden;
            //cout<<den<<endl;
        }
        int temp= num;
        num=den;
        den=temp;
        return Rational(num,den);
    }
    
}
//less than comparison, makes fractions have same den
bool Rational::operator<(const Rational& other) const
{
    int lhsn = this->n * other.d;
    int rhsn = other.n *this->d;
    if (lhsn<rhsn)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//adds to a current rational an int
Rational& Rational::operator+=(int rhs) {
    // TODO
    int rhsd = this->d;
    int rhsn = rhsd*rhs;
    //int leftn= this->n*rhs.d;
    //int rightn = rhs.n *this->d;
    int finaln = this->n+rhsn;
    this->n = finaln;
    this->d = rhsd;
    //must normalize or reduce
    if (n==0)
    {
        this->normalize();
    }
    else
    {

        this->reduce();
    }
    return *this;
}
//chnge current rational by rational multiplication
Rational& Rational::operator*=(const Rational& rhs)
{
    this->n = this->n*rhs.n;
    this->d = this->d*rhs.d;
    //normalize or reduce
    if (n==0)
    {
        this->normalize();
    }
    else
    {

        this->reduce();
    }
    return *this;
}
//change current rational by int multiplication
Rational& Rational::operator*=(int rhs)
{
    this->n = this->n*rhs;
    this->d = this->d;
    //normalize or reduce
    if (n==0)
    {
        this->normalize();
    }
    else
    {

        this->reduce();
    }
    return *this;
}