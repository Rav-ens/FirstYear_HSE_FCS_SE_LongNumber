#include <cassert>
#include "LongNumber.cpp"

void run_tests() {
    // Тест 1: Проверка конструктора по умолчанию
    {
        LongNumber num;
        assert(num.accuracy == 0);
        assert(num.sign == 1);
        assert(num.sz_int_part == 1);
        assert(num.int_part == std::vector<int>{0});
        assert(num.fract_part == std::vector<int>{});
        std::cout << "Test 1: Default constructor - OK\n";
    }

    // Тест 2: Проверка конструктора с целым числом
    {
        LongNumber num(123, 5);
        assert(num.accuracy == 5);
        assert(num.sign == 1);
        assert(num.sz_int_part == 7); // 123 в двоичной системе: 1111011 (7 цифр)
        assert((num.int_part == std::vector<int>{1, 1, 0, 1, 1, 1, 1}));
        assert((num.fract_part == std::vector<int>{0, 0, 0, 0, 0}));
        std::cout << "Test 2: Integer constructor - OK\n";
    }

    // Тест 3: Проверка сложения
    {
        LongNumber num1(10, 5);
        LongNumber num2(20, 5);
        LongNumber sum = num1 + num2;
        assert(sum.to_int_intpart() == 30);
        std::cout << "Test 3: Addition - OK\n";
    }

    // Тест 4: Проверка вычитания
    {
        LongNumber num1(30, 5);
        LongNumber num2(20, 5);
        LongNumber diff = num1 - num2;
        assert(diff.to_int_intpart() == 10);
        std::cout << "Test 4: Subtraction - OK\n";
    }

    // Тест 5: Проверка умножения
    {
        LongNumber num1(5, 5);
        LongNumber num2(4, 5);
        LongNumber prod = num1 * num2;
        assert(prod.to_int_intpart() == 20);
        std::cout << "Test 5: Multiplication - OK\n";
    }

    // Тест 6: Проверка деления
    {
        LongNumber num1(20, 5);
        LongNumber num2(5, 5);
        LongNumber quot = num1 / num2;
        assert(quot.to_int_intpart() == 4);
        std::cout << "Test 6: Division - OK\n";
    }

    // Тест 7: Проверка отрицательных чисел
    {
        LongNumber num1(-10, 5);
        LongNumber num2(20, 5);
        LongNumber sum = num1 + num2;
        assert(sum.to_int_intpart() == 10);
        std::cout << "Test 7: Negative numbers - OK\n";
    }


    // Тест 10: Проверка пользовательского литерала
    {
        LongNumber num = 123.456_longnum;
        assert(num.to_int_intpart() == 123);
        std::cout << "Test 8: User-defined literal - OK\n";
    }
    std::cout << "All tests passed successfully!\n";

}

