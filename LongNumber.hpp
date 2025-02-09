#ifndef LG
#define LG

#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include <time.h>

class LongNumber {
public:
    int accuracy;
    int sign;
    const static int base = 2;
    static std::vector<LongNumber> ostLN;
    const static int standart_accur = 0;
    int sz_int_part;
    std::vector<int> int_part;
    std::vector<int> fract_part;

    // Конструкторы
    LongNumber();
    LongNumber(int acc);
    LongNumber(int a, int acc);
    LongNumber(long long a, int acc);
    LongNumber(long double ld, int acc);
    LongNumber(double ld, int acc);
    LongNumber(const LongNumber &other);
    ~LongNumber() = default;
    // Методы доступа
    int get_intprt(int i) const;
    void push_intprt(int i, int val);
    int get_fractprt(int i) const;
    int get_num(int i) const;
    void plus_num(int i, int val);
    void del_lead_zeros();
    void normalaize();
    long long to_int_intpart() const;

    // Операторы сравнения
    auto operator<=>(const LongNumber &other) const;
    bool operator==(const LongNumber &other) const;

    // Арифметические операторы
    LongNumber operator-() const;
    LongNumber operator+(const LongNumber &other) const;
    LongNumber operator-(const LongNumber &other) const;
    LongNumber operator*(const LongNumber &other) const;
    LongNumber operator/(const LongNumber &other) const;

    // Операторы присваивания
    LongNumber& operator=(const LongNumber& other);
    LongNumber& operator+=(const LongNumber &other);
    LongNumber& operator*=(const LongNumber &other);
    LongNumber& operator-=(const LongNumber &other);
    LongNumber& operator/=(const LongNumber &other);

    // Дружественные функции
    friend std::ostream& operator<<(std::ostream& os, const LongNumber &numb);
    friend LongNumber operator ""_longnum(long double number);
    friend void prt(LongNumber l);
};

#endif // LG
