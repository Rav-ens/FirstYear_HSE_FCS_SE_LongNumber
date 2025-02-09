#ifndef LG_cpp
#define LG_cpp
#include "LongNumber.hpp"


LongNumber::LongNumber(){
    accuracy = standart_accur;
    sign = 1;
    sz_int_part = 1;
    int_part = std::vector<int>(1, 0);
    fract_part = std::vector<int>(accuracy, 0);
}
LongNumber::LongNumber(int acc) {

    accuracy = acc;
    sign = 1;
    sz_int_part = 1;
    int_part = std::vector<int>(1, 0);
    fract_part = std::vector<int>(accuracy, 0);
}
LongNumber::LongNumber(int a,int acc) {

    accuracy = acc;
    sign = 1;
    fract_part = std::vector<int>(accuracy, 0);

    if (a < 0) sign = -1;
    a = abs(a);
    int_part.push_back(a % base);
    a /= base;
    while (a) {
        int_part.push_back(a % base);
        a /= base;
    }

    sz_int_part = int_part.size();
}
LongNumber::LongNumber(long long a,int acc) {
    accuracy = acc;
    sign = 1;
    fract_part = std::vector<int>(accuracy, 0);

    if (a < 0) sign = -1;
    a = abs(a);
    int_part.push_back(a % base);
    a /= base;
    while (a) {
        int_part.push_back(a % base);
        a /= base;
    }

    sz_int_part = int_part.size();
}
LongNumber::LongNumber(long double ld, int acc) {
    accuracy = acc;
    sign = 1;
    fract_part = std::vector<int>(accuracy, 0);

    if (ld < 0) {
        sign = -1;
        ld *= -1;
    }

    long long a = int(ld);
    ld -= a;

    int_part = std::vector<int>(1, a % base);
    a /= base;

    while (a) {
        int_part.push_back(a % base);
        a /= base;
    }

    for (int i = 0; i < accuracy; i++) {
        ld *= base;
        fract_part[i] = int(ld);
        ld -= fract_part[i];
    }

    ld *= base;
    sz_int_part = int_part.size();
}
LongNumber::LongNumber(double ld, int acc) {
    accuracy = acc;
    sign = 1;
    fract_part = std::vector<int>(accuracy, 0);

    if (ld < 0) {
        sign = -1;
        ld *= -1;
    }

    long long a = int(ld);
    ld -= a;

    int_part = std::vector<int>(1, a % base);
    a /= base;

    while (a) {
        int_part.push_back(a % base);
        a /= base;
    }

    for (int i = 0; i < accuracy; i++) {
        ld *= base;
        fract_part[i] = int(ld);
        ld -= fract_part[i];
    }

    sz_int_part = int_part.size();
}
LongNumber::LongNumber(const LongNumber &other) {
    accuracy = other.accuracy;
    sign = other.sign;
    sz_int_part = other.sz_int_part;
    int_part = other.int_part;
    fract_part = other.fract_part;
}

// Методы доступа
int LongNumber::get_intprt(int i) const {
    if (i >= sz_int_part) {
        return 0;
    }
    return int_part[i];
}

void LongNumber::push_intprt(int i, int val) {
    if (i >= sz_int_part) {
        sz_int_part++;
        int_part.push_back(val);
        return;
    }
    if (i >= sz_int_part)
        throw "КУДА ЛЕЗИШЬ СОСУНОК(push_intprt)";

    int_part[i] = val;
}

int LongNumber::get_fractprt(int i) const{
    if(i < accuracy) return fract_part[i];
    return 0;
}

int LongNumber::get_num(int i) const {
    if(i < 0 ) return 0;
    if (i < accuracy)
        return fract_part[accuracy - 1 - i];
    if (i - accuracy < sz_int_part)
        return int_part[i - accuracy];
    return 0;
}

void LongNumber::plus_num(int i, int val) {
    if (i < accuracy)
        fract_part[accuracy - 1 - i] += val;
    else if (val) {
        while (i - accuracy >= sz_int_part) {
            int_part.push_back(0);
            sz_int_part++;
        }
        int_part[i - accuracy] += val;
    }
}

void LongNumber::del_lead_zeros() {
    while (int_part[sz_int_part - 1] == 0 && sz_int_part > 1) {
        sz_int_part--;
        int_part.pop_back();
    }
}

void LongNumber::normalaize(){
    int to_nxt = 0;
    for(int i = accuracy -1; i >=0; i--){
        fract_part[i] += to_nxt;
        to_nxt = fract_part[i] / base;
        fract_part[i]%=base;
    }
    for(int i = 0; i < sz_int_part; i++){
        int_part[i] += to_nxt;
        to_nxt = int_part[i] / base;
        int_part[i]%=base;
    }
    if(to_nxt){
        int_part.push_back(to_nxt);
    }
    sz_int_part++;
}

long long LongNumber::to_int_intpart() const{
    long long mod = 1;
    long long ans  = 0;
    for(int i = 0; i < sz_int_part; i++){
        ans += int_part[i] * mod;
        mod *= base;
    }
    return ans;
}
// Операторы сравнения
auto LongNumber::operator<=>(const LongNumber &other) const {
    if (sign != other.sign){
        return sign <=> other.sign;
    }

    // if(sz_int_part != other.sz_int_part){
    //     return sz_int_part * sign <=> other.sz_int_part * other.sign;
    // }

    //if(sz_int_part != std::max(sz_int_part, other.sz_int_part)) std::cout<<"huiiiii";
    for (int i = std::max(sz_int_part,other.sz_int_part) - 1; i >= 0; i--) {
        if (get_intprt(i) != other.get_intprt(i)) {
            return sign * get_intprt(i) <=> other.sign * other.get_intprt(i);
        }
    }

    int f = std::max(accuracy,other.accuracy);
    for (int i = 0; i < f; i++) {
        if (get_fractprt(i) != other.get_fractprt(i)) {
            return sign * get_fractprt(i) <=> other.sign * other.get_fractprt(i);
        }
    }
    return 1 <=> 1;
}

bool LongNumber::operator==(const LongNumber &other) const {
    
    if (sign != other.sign) {
        return false;
    }
    
    if (sz_int_part != other.sz_int_part) {
        return false;
    }
    
    for (int i = sz_int_part - 1; i >= 0; i--) {
        if (int_part[i] != other.int_part[i]) {
            return false;
        }
    }
    for (int i = 0; i < accuracy; i++) {
        if (fract_part[i] != other.fract_part[i]) {
            return false;
        }
    }
    return true;
}

// Арифметические операторы
LongNumber LongNumber::operator-() const {
    LongNumber nw = *this;
    nw.sign *= -1;
    return nw;
}

LongNumber LongNumber::operator+(const LongNumber &other) const {
    if (sign != other.sign) return *this - (-other);

    LongNumber new_numb(std::max(accuracy,other.accuracy));
    new_numb.sign = sign;

    int to_nxt = 0;

    for (int i = new_numb.accuracy - 1; i >= 0; i--) {
        new_numb.fract_part[i] += get_fractprt(i) + other.get_fractprt(i) + to_nxt;
        to_nxt = new_numb.fract_part[i] / base;
        new_numb.fract_part[i] %= base;
    }

    for (int i = 0; i < std::max(sz_int_part, other.sz_int_part); i++) {
        new_numb.push_intprt(i, get_intprt(i) + other.get_intprt(i) + to_nxt);
        to_nxt = new_numb.int_part[i] / base;
        new_numb.int_part[i] %= base;
    }

    if (to_nxt) {
        new_numb.push_intprt(std::max(sz_int_part, other.sz_int_part), to_nxt);
    }
    new_numb.del_lead_zeros();
    return new_numb;
}

LongNumber LongNumber::operator-(const LongNumber &other) const {
    if (sign != other.sign) return *this + (-other);
    if (*this < other) return -(other - *this);
    if (sign < 0) return -((-*this) -  (-other));

    LongNumber new_numb(std::max(accuracy,other.accuracy));
    new_numb.sign = + 1;

    int from_nxt = 0;

    for (int i = new_numb.accuracy - 1; i >= 0; i--) {
        new_numb.fract_part[i] += get_fractprt(i) - other.get_fractprt(i) + from_nxt;
        from_nxt = 0;
        if (new_numb.fract_part[i] < 0) {
            from_nxt = -1;
            new_numb.fract_part[i] += base;
        }
    }

    for (int i = 0; i < std::max(sz_int_part, other.sz_int_part); i++) {
        new_numb.push_intprt(i, get_intprt(i) - other.get_intprt(i) + from_nxt);
        from_nxt = 0;
        if (new_numb.int_part[i] < 0) {
            from_nxt = -1;
            new_numb.int_part[i] += base;
        }
    }
    if (from_nxt) {

        std::cout<<*this<<std::endl;
        std::cout<<other<<std::endl;
        std::cout<<int(*this > other) <<std::endl;

        throw "ЭЭЭ ВАСЯ ТЫ ИЗ МЕНЬШЕГО ВЫЧИТАЕШЬ БОЛЬШЕЕ";}

    new_numb.del_lead_zeros();

    return new_numb;
}

LongNumber LongNumber::operator*(const LongNumber &other) const {
    LongNumber new_numb(std::max(accuracy,other.accuracy));
    new_numb.sign = sign * other.sign;

    int to_nxt = 0;
    
    int min_acc = other.accuracy + accuracy - new_numb.accuracy;
    for (int i = 0; i < accuracy + sz_int_part; i++) {
        for (int j = 0; j < other.accuracy + other.sz_int_part; j++) {
            if (i + j >= min_acc) {
                new_numb.plus_num(i + j - min_acc, get_num(i) * other.get_num(j));
            } else if (i + j == min_acc - 1) {
                to_nxt += get_num(i) * other.get_num(j);
            }
        }
    }
    to_nxt /= base;

    for (int i = new_numb.accuracy - 1; i >= 0; i--) {
        new_numb.fract_part[i] += to_nxt;
        to_nxt = new_numb.fract_part[i] / base;
        new_numb.fract_part[i] %= base;
    }

    for (int i = 0; i < new_numb.sz_int_part; i++) {
        new_numb.int_part[i] += to_nxt;
        to_nxt = new_numb.int_part[i] / base;
        new_numb.int_part[i] %= base;
    }

    if (to_nxt) {
        new_numb.int_part.push_back(to_nxt);
        new_numb.sz_int_part++;
    }
    new_numb.del_lead_zeros();

    return new_numb;
}

LongNumber LongNumber::operator/(const LongNumber &other) const {
    LongNumber new_numb(std::max(accuracy, other.accuracy)), other2(other.accuracy);
    new_numb.sign = sign * other.sign;
    other2.int_part.pop_back();
    other2.int_part.reserve(other2.accuracy + other.sz_int_part);
    other2.int_part.insert(other2.int_part.end(), other.fract_part.rbegin(), other.fract_part.rend());
    other2.int_part.insert(other2.int_part.end(), other.int_part.begin(), other.int_part.end());
    other2.sz_int_part = other2.int_part.size();
    other2.del_lead_zeros();

    int ind_this  = 0;
    LongNumber buffer(0,0);
    new_numb.int_part = std::vector(sz_int_part + other.accuracy,0);
    new_numb.sz_int_part = sz_int_part + other.accuracy;
    while (ind_this != sz_int_part + other.accuracy) {
        buffer *= ostLN[base];
        buffer += ostLN[get_num(accuracy + sz_int_part - ind_this - 1)];
        if (buffer >= other2) {
            int i = 2;
            if (base> 2) for (; ostLN[i] * other2 <= buffer; i++) {}
            new_numb.int_part[new_numb.sz_int_part - ind_this - 1] = i - 1;
            buffer = buffer - (ostLN[i - 1] * other2);
        }
        ind_this++;
    }
    new_numb.del_lead_zeros();
    for (int ind_fract = 0; ind_fract < new_numb.accuracy; ind_fract++) {
        buffer *= ostLN[base];
        buffer.int_part[0] = get_num(accuracy + sz_int_part - ind_this - 1);
        ind_this++;
        if (buffer >= other2) {
            int i = 2;
             if(base > 2) for (; ostLN[i] * other2 <= buffer; i++) {}
            new_numb.fract_part[ind_fract] = i - 1;
            buffer = buffer - (ostLN[i - 1] * other2);
        }
    }
    new_numb.del_lead_zeros();
    return new_numb;
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (&other != this) {
        sign = other.sign;
        sz_int_part = other.sz_int_part;
        int_part = other.int_part;
        fract_part = other.fract_part;
    }
    return *this;
}

LongNumber& LongNumber::operator+=(const LongNumber &other) {
    *this = *this + other;
    return *this;
}

LongNumber& LongNumber::operator*=(const LongNumber &other) {
    *this = *this * other;
    return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber &other) {
    *this = *this - other;
    return *this;
}

LongNumber& LongNumber::operator/=(const LongNumber &other) {
    *this = *this / other;
    return *this;
}


// Дружественные функции
std::ostream& operator<<(std::ostream& os, const LongNumber &numb) {
    if (numb.sign == -1) os << "-";
    for (int i = numb.sz_int_part - 1; i >= 0; i--) {
        os << numb.int_part[i];
    }
    os << ".";
    for (int i = 0; i < numb.accuracy; i++) {
        os << numb.fract_part[i];
    }
    return os;
}

LongNumber operator ""_longnum(long double number){
    return LongNumber(number,10);
};
void prt(LongNumber l){ std::cout<<"["<<l<<"]"<<std::endl;};
std::vector<LongNumber> LongNumber::ostLN = {LongNumber(0,0),LongNumber(1,0),LongNumber(2,0)};

#endif