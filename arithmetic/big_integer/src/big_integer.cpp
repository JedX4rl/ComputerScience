#include <cstring>
#include <stdexcept>
#include <vector>
#include "big_integer.h"
#include "not_implemented.h"


big_integer &big_integer::trivial_multiplication::multiply(
        big_integer &first_multiplier,
        big_integer const &second_multiplier) const
{
    if (first_multiplier.is_equal_to_zero())
    {
        return first_multiplier;
    }

    if (second_multiplier.is_equal_to_zero())
    {
        return first_multiplier = second_multiplier;
    }

    if (second_multiplier.is_equal_to_one())
    {
        return first_multiplier;
    }

    if (first_multiplier.is_equal_to_one())
    {
        return first_multiplier = second_multiplier;
    }

    if (first_multiplier.sign() == -1)
    {
        first_multiplier.change_sign();
        first_multiplier *= second_multiplier;
        return first_multiplier.change_sign();
    }

    if (second_multiplier.sign() == -1)
    {
        first_multiplier *= -second_multiplier;
        return first_multiplier.change_sign();
    }

    auto const first_value_digits_count = first_multiplier.get_digits_count();
    auto const second_value_digits_count = second_multiplier.get_digits_count();


    constexpr int shift = sizeof(unsigned int) << 2;
    constexpr int mask = (1 << shift) - 1; //max value in a half

    big_integer result(std::vector<int>{0});//101 122

    for (int i = 0; i < first_value_digits_count; ++i) //first value digits
    {
        std::vector<int> result_digits(second_value_digits_count + i + 1, 0);
        unsigned int first_value_digit = first_multiplier.get_digit(i);
        unsigned int operation_result = 0;
        for (int k = 0; k < second_value_digits_count; ++k) //
        {
            unsigned int second_value_digit = second_multiplier.get_digit(k);

            unsigned young_young = (first_value_digit & mask) * (second_value_digit & mask); // 9
            unsigned young_old = (first_value_digit & mask) * (second_value_digit >> shift); //9
            unsigned old_young = (first_value_digit >> shift) * (second_value_digit & mask); //
            unsigned old_old = (first_value_digit >> shift) * (second_value_digit >> shift);

            operation_result += young_young & mask;
            result_digits[i + k] |= *reinterpret_cast<int*>(&operation_result) & mask;
            operation_result >>= shift;
            operation_result += (young_young >> shift) + (young_old & mask) + (old_young & mask);
            result_digits[i + k] |= *reinterpret_cast<int*>(&operation_result) << shift;
            operation_result >>= shift;
            operation_result += (young_old >> shift) + (old_young >> shift) + old_old;
        }

        result_digits.back() = *reinterpret_cast<int*>(&operation_result);
        result += big_integer(result_digits);
    }
    return first_multiplier = result;
}

big_integer &big_integer::Karatsuba_multiplication::multiply(
        big_integer &first_multiplier,
        big_integer const &second_multiplier) const
{
    throw not_implemented("big_integer &big_integer::Karatsuba_multiplication::multiply(big_integer &, big_integer const &)", "your code should be here...");
}

big_integer &big_integer::Schonhage_Strassen_multiplication::multiply(
        big_integer &first_multiplier,
        big_integer const &second_multiplier) const
{
    throw not_implemented("big_integer &big_integer::Schonhage_Strassen_multiplication::multiply(big_integer &, big_integer const &)", "your code should be here...");
}

big_integer &big_integer::trivial_division::divide(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    big_integer tmp_zero("0");
    big_integer tmp_one("1");
    if (divisor == tmp_zero)
    {
        throw std::logic_error("Division by zero error!");
    }
    if (dividend == tmp_zero)
    {
        return dividend = tmp_zero;
    }
    if (divisor == tmp_one)
    {
        return dividend;
    }


    if (dividend.sign() == -1)
    {
        divide(dividend.change_sign(), divisor, multiplication_rule::trivial);
        return dividend.change_sign();
    }

    if (divisor.sign() == -1)
    {
        divide(dividend, -divisor, multiplication_rule::trivial);
        return dividend.change_sign();
    }

    auto const first_value_digits_count = dividend.get_digits_count();

    big_integer minuend("0");
    big_integer res("0");

    for (int i = first_value_digits_count - 1; i >= 0; --i)
    {
        big_integer subtrahend = tmp_zero;
        unsigned int curr_digit = dividend.get_digit(i);


        minuend <<= sizeof(int) << 3;
        minuend += big_integer(std::vector<int>{*reinterpret_cast<int*>(&curr_digit), 0});

        res <<= (sizeof(int) << 3);

        if (minuend < divisor)
        {
            continue;
        } // 15 string

        for (int j = 31; j >= 0; --j)
        {
            big_integer tmp = tmp_one << j;
            big_integer a = multiply(divisor, tmp,nullptr,  multiplication_rule);

            if (subtrahend + a <= minuend)
            {
                subtrahend += a;
                res += tmp;
            }
        }
        minuend -= subtrahend;

    }
    return dividend = res;
}

big_integer &big_integer::trivial_division::modulo(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    big_integer tmp_zero("0");
    big_integer tmp_one("1");
    if (divisor == tmp_zero)
    {
        throw std::logic_error("Division by zero error!");
    }
    if (dividend == tmp_zero)
    {
        return dividend = tmp_zero;
    }
    if (divisor == tmp_one)
    {
        return dividend;
    }
    if (dividend < divisor)
    {
        return dividend = tmp_zero;
    }


    if (dividend.sign() == -1)
    {
        divide(dividend.change_sign(), divisor, multiplication_rule::trivial);
        return dividend.change_sign();
    }

    if (divisor.sign() == -1)
    {
        divide(dividend, -divisor, multiplication_rule::trivial);
        return dividend.change_sign();
    }

    auto const first_value_digits_count = dividend.get_digits_count();

    big_integer minuend("0");
    big_integer res("0");

    for (int i = first_value_digits_count - 1; i >= 0; --i)
    {
        big_integer subtrahend = tmp_zero;
        unsigned int curr_digit = dividend.get_digit(i);


        minuend <<= sizeof(int) << 3;
        minuend += big_integer(std::vector<int>{*reinterpret_cast<int*>(&curr_digit), 0});

        res <<= (sizeof(int) << 3);

        if (minuend < divisor)
        {
            continue;
        } // 15 string

        for (int j = 31; j >= 0; --j)
        {
            big_integer tmp = tmp_one << j;
            big_integer a = multiply(divisor, tmp,nullptr,  multiplication_rule);

            if (subtrahend + a <= minuend)
            {
                subtrahend += a;
                res += tmp;
            }
        }
        minuend -= subtrahend;

    }
    big_integer tmp = multiply(divisor, res, nullptr, multiplication_rule);
    return dividend = dividend - tmp;
}

//return *this = *this - other * res;

big_integer &big_integer::Newton_division::divide(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    throw not_implemented("big_integer &big_integer::Newton_division::divide(big_integer &, big_integer const &, big_integer::multiplication_rule)", "your code should be here...");
}

big_integer &big_integer::Newton_division::modulo(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    throw not_implemented("big_integer &big_integer::Newton_division::modulo(big_integer &, big_integer const &, big_integer::multiplication_rule)", "your code should be here...");
}

big_integer &big_integer::Burnikel_Ziegler_division::divide(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    throw not_implemented("big_integer &big_integer::Burnikel_Ziegler_division::divide(big_integer &, big_integer const &, big_integer::multiplication_rule)", "your code should be here...");
}

big_integer &big_integer::Burnikel_Ziegler_division::modulo(
        big_integer &dividend,
        big_integer const &divisor,
        big_integer::multiplication_rule multiplication_rule) const
{
    throw not_implemented("big_integer &big_integer::Burnikel_Ziegler_division::modulo(big_integer &, big_integer const &, big_integer::multiplication_rule)", "your code should be here...");
}


void big_integer::clear()
{
    _oldest_digit = 0;
    allocator = nullptr;
    deallocate_with_guard(_other_digits);
    _other_digits = nullptr;
}

void big_integer::copy_from(
        big_integer const &other)
{
    _oldest_digit = other._oldest_digit;
    _other_digits = nullptr;
    allocator = nullptr;
    if (other._other_digits == nullptr)
    {
        return;
    }

    _other_digits = reinterpret_cast<unsigned int*>(allocate_with_guard(sizeof(unsigned int), *other._other_digits));

    _other_digits = new unsigned int[*other._other_digits];
    std::memcpy(_other_digits, other._other_digits, sizeof(unsigned int) * (*other._other_digits));
}

void big_integer::initialize_from(
        int const *digits,
        size_t digits_count)
{
    if (digits == nullptr)
    {
        throw std::logic_error("pointer to digits array must not be nullptr");
    }

    if (digits_count == 0)
    {
        throw std::logic_error("digits array length must  be GT 0");
    }

    _oldest_digit = digits[digits_count - 1];
    _other_digits = (digits_count == 1
                     ? nullptr
                     : new unsigned int[digits_count]);

    if (_other_digits == nullptr)
    {
        return;
    }

    *_other_digits = (unsigned int)digits_count;

    std::memcpy(_other_digits + 1, digits, sizeof(unsigned int) * (digits_count - 1));
}

void big_integer::initialize_from(
        std::vector<int> const &digits,
        size_t digits_count)
{
    _other_digits = nullptr;

    if (digits.empty() || digits_count == 0)
    {
        throw std::logic_error("std::vector<int> of digits should not be empty");
    }


    _oldest_digit = digits_count > digits.size() ? 0 : digits[digits_count - 1];

    if (digits_count == 1)
    {
        return;
    }

    _other_digits = new unsigned int[digits_count];
    *_other_digits = digits_count;

    for (auto i = 0; i < digits_count - 1; ++i)
    {
        if (i < digits_count)
        {
            _other_digits[i + 1] = *reinterpret_cast<unsigned int const *>(&digits[i]);
        }
        else
        {
            _other_digits[i + 1] = 0;
        }
    }
}

int char_to_int(char ch)
{
    if (isdigit(ch))
    {
        return ch - '0';
    }
    if (isalpha(ch))
    {
        if (isupper(ch))
        {
            return ch - 'A' + 10;
        }
        return ch - 'a' + 36;
    }
    throw std::logic_error("Undefined digit");
}

void big_integer::initialize_from( //123456
        std::string const &value,
        size_t base)
{
    if (value.empty())
    {
        throw std::logic_error("String cannot be empty");
    }
    if (base < 2)
    {
        throw std::logic_error("Base should be greater than 2");
    }
    if (value == "0")
    {
        int l = 0;
    }
    this->_oldest_digit = 0;
    this->_other_digits = nullptr;
    big_integer _base(std::vector<int>{*reinterpret_cast<int*>(&base)}); //TODO
    int sign = value[0] == '-' ? -1 : 1;
    size_t value_size = value.size();

    for (int i = sign == -1 ? 1 : 0 ; i < value_size; ++i)
    {
        *this *= _base;
        *this += big_integer(std::vector<int>{char_to_int(value[i])});
    }
    if (sign == -1)
    {
        this->change_sign();
    }
}

void big_integer::print_byte(
        std::ostream &stream,
        unsigned char byte_value)
{
    for (int i = 0; i < 8; i++)
    {
        stream << ((byte_value >> (7 - i)) & 1);
    }
}

void big_integer::dump_int_value(
        std::ostream &stream,
        int value)
{
    auto *p = (unsigned char *)&value;
    for (int i = 0; i < sizeof(int); i++)
    {
        print_byte(stream, *p++);
        stream << ' ';
    }
}

big_integer &big_integer::change_sign()
{
    _oldest_digit ^= (1 << ((sizeof(int) << 3) - 1));
    return *this;
}

inline int big_integer::get_digits_count() const noexcept
{
    return static_cast<int>(_other_digits == nullptr
                            ? 1
                            : *_other_digits);
}

inline int big_integer::sign() const noexcept
{
    if (is_equal_to_zero())
    {
        return 0;
    }

    return 1 - (static_cast<int>((*reinterpret_cast<unsigned int const *>(&_oldest_digit) >> ((sizeof(int) << 3) - 1))) << 1);
}

inline bool big_integer::is_equal_to_zero() const noexcept
{
    return _oldest_digit == 0 && _other_digits == nullptr;
}

inline bool big_integer::is_equal_to_one() const noexcept
{
    return _oldest_digit == 1 && _other_digits == nullptr;
}

inline unsigned int big_integer::get_digit(
        int position) const noexcept
{
    if (_other_digits == nullptr)
    {
        return position == 0
               ? _oldest_digit
               : 0;
    }

    int const digits_count = get_digits_count();
    if (position < digits_count - 1)
    {
        return _other_digits[position + 1];
    }

    if (position == digits_count - 1)
    {
        return _oldest_digit;
    }

    return 0;
}

big_integer::big_integer(
        int const *digits,
        size_t digits_count,
        class allocator* allocator)
{
    initialize_from(digits, digits_count);
}

big_integer::big_integer(
        std::vector<int> const &digits,
        class allocator* allocator)
{
    initialize_from(digits, get_significant_digits_count(digits));
}

big_integer::big_integer(
        std::string const &value,
        size_t base,
        class allocator* allocator)
{
    initialize_from(value, base);
}

big_integer &big_integer::move_from(
        big_integer &&other)
{
    _oldest_digit = other._oldest_digit;
    _other_digits = other._other_digits;
    allocator = other.allocator;

    other._oldest_digit = 0;
    other._other_digits = nullptr;
    other.allocator = nullptr;

    return *this;
}

big_integer::big_integer(
        big_integer const &other)
{
    copy_from(other);
}

big_integer::big_integer(
        big_integer &&other) noexcept
{
    move_from(std::move(other));
}


big_integer &big_integer::operator=(
        big_integer const &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }

    return *this;
}

big_integer &big_integer::operator=(
        big_integer &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move_from(std::move(other));
    }

    return *this;
}

big_integer::~big_integer()
{
    clear();
}


big_integer &big_integer::operator+=(
        big_integer const &other)
{
    if (other.is_equal_to_zero())
    {
        return *this;
    }

    if (is_equal_to_zero())
    {
        return *this = other;
    }

    if (sign() == -1)
    {
        change_sign();
        *this += -other;
        return change_sign();
    }

    if (other.sign() == -1)
    {
        return *this -= -other;
    }

    auto const first_value_digits_count = get_digits_count();
    auto const second_value_digits_count = other.get_digits_count();
    auto const digits_count = std::max(first_value_digits_count, second_value_digits_count);

    unsigned int operation_result = 0;

    constexpr int shift = sizeof(unsigned int) << 2;
    constexpr int mask = (1 << shift) - 1; //max value in a half

    std::vector<int> result_digits(digits_count + 1, 0);

    for (int i = 0; i < digits_count; ++i)
    {
        unsigned int first_value_digit = get_digit(i);
        unsigned int second_value_digit = other.get_digit(i);

        for (int j = 0; j < 2; ++j)
        {
            operation_result += (first_value_digit & mask) + (second_value_digit & mask);
            first_value_digit >>= shift;
            second_value_digit >>= shift;
            *reinterpret_cast<unsigned int *>(&result_digits[i]) |= ((operation_result & mask) << shift * j); // = a | b
            operation_result >>= shift;
        }
    }

    if (operation_result == 1)
    {
        result_digits.back() = 1;
    }

    clear();

//    auto significant_numbers = ((*reinterpret_cast<unsigned int *>(&result_digits[digits_count - 1]) >> ((sizeof(unsigned int) << 3) - 1)) == 0)
//            ? get_significant_digits_count(result_digits, true)
//            : get_significant_digits_count(result_digits, true) + 1;

    initialize_from(result_digits, get_significant_digits_count(result_digits, true));

    return *this;
}

big_integer big_integer::operator+(
        big_integer const &other) const
{
    return big_integer(*this) += other;
}

big_integer &big_integer::operator-=(
        big_integer const &other)
{
    if (other.is_equal_to_zero())
    {
        return *this;
    }

    if (is_equal_to_zero())
    {
        return *this = -other;
    }

    if (sign() == -1 && other.sign() != -1)
    {
        change_sign();
        *this += other;
        return change_sign();
    }

    if (other.sign() == -1)
    {
        return *this += -other;
    }

    if (*this < other)
    {
        return *this = -(other - *this);
    }

    auto const first_value_digits_count = get_digits_count();
    auto const second_value_digits_count = other.get_digits_count();
    auto const digits_count = std::max(first_value_digits_count, second_value_digits_count);
    int taken = 0;

    std::vector<int> result_digits(digits_count + 1, {0});

    for (int i = 0; i < digits_count; ++i)
    {
        unsigned int first_value_digit = get_digit(i);
        unsigned int second_value_digit = other.get_digit(i);
        result_digits[i] = 0;
        if (second_value_digit == UINT_MAX)
        {
            if (first_value_digit == UINT_MAX)
            {
                *reinterpret_cast<unsigned int*>(&result_digits[i]) = taken ? UINT_MAX : 0;
            }
            else
            {
                *reinterpret_cast<unsigned int*>(&result_digits[i]) = first_value_digit - taken + 1;
                taken = 1;
            }
        }
        else if (first_value_digit < second_value_digit + taken)
        {
            *reinterpret_cast<unsigned int*>(&result_digits[i]) = first_value_digit + (UINT_MAX - second_value_digit - taken) + 1;
            taken = 1;
        }
        else
        {
            *reinterpret_cast<unsigned int*>(&result_digits[i]) = first_value_digit - second_value_digit - taken;
            taken = 0;
        }
    }

    auto result_digits_count = result_digits.size();

    if ((*reinterpret_cast<unsigned int *>(&result_digits[digits_count - 1]) >> ((sizeof(unsigned int) << 3) - 1)) == 0) //not 1 bit ? - ok : --
    {
        --result_digits_count;
    }

    clear();
    initialize_from(result_digits, get_significant_digits_count(result_digits, true)); //res.sign.cnt

    return *this;
}

big_integer big_integer::operator-(
        big_integer const &other) const
{
    return big_integer(*this) -= other;
}

big_integer big_integer::operator-() const
{
    return big_integer(*this).change_sign();
}

big_integer &big_integer::operator*=( //TODO here we are
        big_integer const &other)
{
    if (this->is_equal_to_zero())
    {
        return *this;
    }

    if (other.is_equal_to_zero())
    {
        return *this = other;
    }

    if (other.is_equal_to_one())
    {
        return *this;
    }

    if (is_equal_to_one())
    {
        return *this = other;
    }

    if (sign() == -1)
    {
        change_sign();
        *this *= other;
        return change_sign();
    }

    if (other.sign() == -1)
    {
        *this *= -other;
        return change_sign();
    }

    auto const first_value_digits_count = get_digits_count();
    auto const second_value_digits_count = other.get_digits_count();


    constexpr int shift = sizeof(unsigned int) << 2;
    constexpr int mask = (1 << shift) - 1; //max value in a half

    big_integer result(std::vector<int>{0});//101 122

    for (int i = 0; i < first_value_digits_count; ++i) //first value digits
    {
        std::vector<int> result_digits(second_value_digits_count + i + 1, 0);
        unsigned int first_value_digit = get_digit(i);
        unsigned int operation_result = 0;
        for (int k = 0; k < second_value_digits_count; ++k) //
        {
            unsigned int second_value_digit = other.get_digit(k);

            unsigned young_young = (first_value_digit & mask) * (second_value_digit & mask); // 9
            unsigned young_old = (first_value_digit & mask) * (second_value_digit >> shift); //9
            unsigned old_young = (first_value_digit >> shift) * (second_value_digit & mask); //
            unsigned old_old = (first_value_digit >> shift) * (second_value_digit >> shift);

            operation_result += young_young & mask;
            result_digits[i + k] |= *reinterpret_cast<int*>(&operation_result) & mask;
            operation_result >>= shift;
            operation_result += (young_young >> shift) + (young_old & mask) + (old_young & mask);
            result_digits[i + k] |= *reinterpret_cast<int*>(&operation_result) << shift;
            operation_result >>= shift;
            operation_result += (young_old >> shift) + (old_young >> shift) + old_old;
        }

        result_digits.back() = *reinterpret_cast<int*>(&operation_result);
        result += big_integer(result_digits);
    }
    return *this = result;
}

big_integer big_integer::operator*(
        big_integer const &other) const
{
    return big_integer(*this) *= other;
}

big_integer &big_integer::operator/=(
        big_integer const &other)
{
    big_integer tmp_zero("0");
    big_integer tmp_one("1");
    if (other == tmp_zero)
    {
        throw std::logic_error("Division by zero error!");
    }
    if (*this == tmp_zero)
    {
        return *this = tmp_zero;
    }
    if (other == tmp_one)
    {
        return *this;
    }


    if (sign() == -1)
    {
        change_sign();
        *this /= other;
        return change_sign();
    }

    if (other.sign() == -1)
    {
        *this /= -other;
        return change_sign();
    }

    if (*this < other)
    {
        return *this = tmp_zero;
    }

    auto const first_value_digits_count = get_digits_count();

    big_integer minuend("0");
    big_integer res("0");

    for (int i = first_value_digits_count - 1; i >= 0; --i)
    {
        big_integer subtrahend = tmp_zero;
        unsigned int curr_digit = get_digit(i);


        minuend <<= sizeof(int) << 3;
        minuend += big_integer(std::vector<int>{*reinterpret_cast<int*>(&curr_digit), 0});

        res <<= (sizeof(int) << 3);

        if (minuend < other)
        {
            continue;
        } // 15 string

        for (int j = 31; j >= 0; --j)
        {
            big_integer tmp = tmp_one << j;

            if (subtrahend + other * tmp <= minuend)
            {
                subtrahend += other * tmp;
                res += tmp;
            }
        }
        minuend -= subtrahend;

    }
    return *this = res;

}

big_integer big_integer::operator/(
        big_integer const &other) const
{
    return big_integer(*this) /= other;
}

big_integer &big_integer::operator%=(
        big_integer const &other)
{
    big_integer tmp_zero("0");
    big_integer tmp_one("1");
    if (other == tmp_zero)
    {
        throw std::logic_error("Division by zero error!");
    }
    if (*this == tmp_zero)
    {
        return *this;
    }
    if (other == tmp_one)
    {
        return *this = tmp_zero;
    }

    if (sign() == -1)
    {
        change_sign();
        *this %= other;
        return change_sign();
    }

    if (other.sign() == -1)
    {
        *this %= -other;
        return change_sign();
    }

    if (*this < other)
    {
        return *this;
    }


    auto const first_value_digits_count = get_digits_count();

    big_integer minuend("0");
    big_integer res("0");

    for (int i = first_value_digits_count - 1; i >= 0; --i)
    {
        big_integer subtrahend = tmp_zero;
        unsigned int curr_digit = get_digit(i);


        minuend <<= sizeof(int) << 3;
        minuend += big_integer(std::vector<int>{*reinterpret_cast<int*>(&curr_digit), 0});

        res <<= (sizeof(int) << 3);

        if (minuend < other)
        {
            continue;
        } // 15 string

        for (int j = 31; j >= 0; --j)
        {
            if (i == 0 && j == 4)
            {
                int l = 4;
            }

            big_integer tmp = tmp_one << j;

            if (subtrahend + other * tmp <= minuend)
            {
                subtrahend += other * tmp;
                res += tmp;
            }
        }
        minuend -= subtrahend;

    }
    return *this = *this - other * res;
}

big_integer big_integer::operator%(
        big_integer const &other) const
{
    return big_integer(*this) %= other;
}

bool big_integer::operator==(
        big_integer const &other) const
{
    if (this->_other_digits == nullptr ^ other._other_digits == nullptr)
    {
        return false;
    }
    if (this->_other_digits == nullptr && _other_digits == nullptr)
    {
        return this->_oldest_digit == other._oldest_digit;
    }
    if (this->_oldest_digit != other._oldest_digit || this->_other_digits[0] != other._other_digits[0])
    {
        return false;
    }
    for (int i = 1; i < _other_digits[0]; ++i)
    {
        if (this->_other_digits[i] != other._other_digits[i])
        {
            return false;
        }
    }
    return true;
}

bool big_integer::operator!=(
        big_integer const &other) const
{
    return !(*this == other);
}

bool big_integer::operator<(
        big_integer const &other) const
{

    if (this->sign() == -1 && other.sign() == -1)
    {
        return -*this > -other;
    }
    if (this->sign() == -1)
    {
        return true;
    }
    else if (other.sign() == -1)
    {
        return false;
    }


    if (get_digits_count() < other.get_digits_count())
    {
        return true;
    }

    if (get_digits_count() > other.get_digits_count())
    {
        return false;
    }

    auto digits_count = get_digits_count();

    for (int i = digits_count - 1; i >= 0; --i)
    {
        unsigned int first_value_digit = get_digit(i);
        unsigned int second_value_digit = other.get_digit(i);

        if (first_value_digit < second_value_digit)
        {
            return true;
        }
        else if (first_value_digit != second_value_digit)
        {
            return false;
        }
    }

    return false;
}

bool big_integer::operator<=(
        big_integer const &other) const
{
    return !(*this > other);
}

bool big_integer::operator>(
        big_integer const &other) const
{

    int changed = 1;
    if (this->sign() == -1 && other.sign() == -1)
    {
        return -*this < -other;
    }
    if (this->sign() == -1)
    {
        return false;
    }

    if (get_digits_count() > other.get_digits_count())
    {
        return true;
    }

    if (get_digits_count() < other.get_digits_count())
    {
        return false;
    }

    auto digits_count = get_digits_count();

    for (int i = digits_count - 1; i >= 0; --i)
    {
        unsigned int first_value_digit = get_digit(i);
        unsigned int second_value_digit = other.get_digit(i);

        if (first_value_digit > second_value_digit)
        {
            return true;
        }
        else if (first_value_digit != second_value_digit)
        {
            return false;
        }
    }

    return false;
}

bool big_integer::operator>=(
        big_integer const &other) const
{
    return !(*this < other);
}

big_integer big_integer::operator~() const
{
    std::vector<int> result;
    result.reserve(get_digits_count() - 1);
    for (int i = 0; i < get_digits_count(); ++i)
        {
            result.push_back(~ static_cast<int>(get_digit(i)));
        }
    return big_integer(result);
}

big_integer &big_integer::operator&=(
        big_integer const &other)
{
    std::vector<int> result;

    unsigned first_value_digits_cnt = get_digits_count();
    unsigned other_value_digit_cnt = other.get_digits_count();

    for (int i = 0, j = 0; i != first_value_digits_cnt || j != other_value_digit_cnt; ++i, ++j)
    {
        result.push_back(get_digit(i) & other.get_digit(j));
    }
    clear();
    initialize_from(result, get_significant_digits_count(result));
    return *this;
}

big_integer big_integer::operator&(
        big_integer const &other) const
{
    return big_integer(*this) &= other;
}

big_integer &big_integer::operator|=(
        big_integer const &other)
{
    std::vector<int> result;

    unsigned first_value_digits_cnt = get_digits_count();
    unsigned other_value_digit_cnt = other.get_digits_count();

    for (int i = 0, j = 0; i != first_value_digits_cnt || j != other_value_digit_cnt; ++i, ++j)
    {
        result.push_back(get_digit(i) | other.get_digit(j));
    }
    clear();
    initialize_from(result, get_significant_digits_count(result));
    return *this;
}

big_integer big_integer::operator|(
        big_integer const &other) const
{
    return big_integer(*this) |= other;
}

big_integer &big_integer::operator^=(
        big_integer const &other)
{
    std::vector<int> result;

    unsigned first_value_digits_cnt = get_digits_count();
    unsigned other_value_digit_cnt = other.get_digits_count();

    for (int i = 0, j = 0; i != first_value_digits_cnt || j != other_value_digit_cnt; ++i, ++j)
    {
        result.push_back(get_digit(i) ^ other.get_digit(j));
    }
    clear();
    initialize_from(result, get_significant_digits_count(result));
    return *this;
}

big_integer big_integer::operator^(
        big_integer const &other) const
{
    return big_integer(*this) ^= other;
}

big_integer big_integer::operator<<(
        size_t shift_value) const
{
    return big_integer(*this) <<= shift_value;
}


big_integer &big_integer::operator<<=(
        size_t shift_value)
{
    if (is_equal_to_zero() || shift_value == 0)
    {
        return *this;
    }

    if (sign() == -1)
    {
        change_sign();
        *this <<= shift_value;
        return change_sign();
    }

    auto bit_count = (sizeof(int) * 8);
    auto big_shift = shift_value / bit_count;
    shift_value %= bit_count;

    auto digits_count = get_digits_count();
    std::vector<int> result_digits(digits_count + big_shift);

    for (int i = 0; i < big_shift; ++i)
    {
        result_digits[i] = 0;
    }

    unsigned int remain = 0;

    for (int i = 0; i < digits_count; ++i)
    {
        unsigned int value_digit = get_digit(i);

        *reinterpret_cast<unsigned int *>(&result_digits[i + big_shift]) = (value_digit << shift_value) | remain;
        remain = bit_count - shift_value == 32 ?
                 0 :
                 value_digit >> (bit_count - shift_value);
    }

    if (remain != 0)
    {
        result_digits.push_back(static_cast<int>(remain));
    }

    if (result_digits.back() & (1 << ((sizeof(int) << 3) - 1)))
    {
        result_digits.push_back(0);
    }

    auto result_digits_count = result_digits.size();

    clear();
    initialize_from(result_digits, result_digits_count);

    return *this;
}


big_integer &big_integer::operator>>=(
        size_t shift)
{
    if (is_equal_to_zero() || shift == 0)
    {
        return *this;
    }

    auto bit_count = (sizeof(int) << 3);
    auto big_shift = shift / bit_count;
    shift %= bit_count;

    auto digits_count = get_digits_count();
    if (digits_count <= big_shift)
    {
        clear();
        return *this += big_integer("0");
    }

    std::vector<int> result_digits(digits_count - big_shift);

    unsigned int remain = 0;

    for (int i = static_cast<int>(big_shift); i < digits_count; ++i)
    {
        unsigned int value_digit = get_digit(i);

        *reinterpret_cast<unsigned int *>(&result_digits[i - big_shift]) = (value_digit >> shift) | remain;

        remain = bit_count - shift == bit_count ?
                 0 :
                 value_digit << (bit_count - shift);
    }

    while (result_digits.front() != result_digits.back() &&
           result_digits.back() == 0)
    {
        result_digits.pop_back();
    }

    auto result_digits_count = result_digits.size();

    clear();
    initialize_from(result_digits, result_digits_count);

    return *this;
}

big_integer big_integer::operator>>(
        size_t shift_value) const
{
    return big_integer(*this) >>= shift_value;
}

std:: string remove_zeros(std::string str)
{
    int i = 0;
    if (str.length() != 1)
    {
        while (str[i] == '0')
        {
            i++;
        }
        str.erase(0, i);
    }
    return str;
}

std::string big_integer::big_int_to_string() const
{
    std::string string;
    string.reserve(11 * get_digits_count());

    big_integer number = *this;
    int sign = this->sign();

    if (sign == -1)
    {
        number.change_sign();
    }

    size_t big_modulus_zeros_cnt = 9;
    int parts = 1;

    for (int i = 0; i < big_modulus_zeros_cnt; ++i)
    {
        parts *= 10;
    }

    big_integer curr("1000000000");

    while (!number.is_equal_to_zero())
    {
        big_integer quotient = number / curr;
        big_integer rem = number % curr;
        unsigned int tmp = rem.get_digit(0);
        for (size_t i = 0; i < big_modulus_zeros_cnt && (tmp || !quotient.is_equal_to_zero()); ++i)
        {
            string.push_back('0' + tmp % 10);
            tmp /= 10;
        }
        number = quotient;
    }

    if (is_equal_to_zero())
    {
        string.push_back('0');
    }

    if (sign == -1)
    {
        string.push_back('-');
    }

    std::reverse(string.begin(), string.end());
    return string;
}

std::ostream &operator<<(
        std::ostream &stream,
        big_integer const &value)
{
    return stream << value.big_int_to_string();
}

std::istream &operator>>(
        std::istream &stream,
        big_integer &value)
{
    std::string string_value;

    stream >> string_value;

    value.clear();
    value.initialize_from(string_value, 10);

    return stream;
}

int big_integer::get_significant_digits_count() const noexcept
{
    int res = get_digits_count();
    if (res == 0 && get_digit(0) == 0)
    {
        return res;
    }
    for (int i = get_digits_count() - 1; i >= 0; --i)
    {
        if (get_digit(i) == 0)
        {
            --res;
        }
        else
        {
            break;
        }
    }
    return res;
}

int big_integer::get_significant_digits_count(const std::vector<int> &digits, bool positive_flag) const noexcept
{
    int res = digits.size();
    int flag = 0;
    if (res == 1 && digits[0] == 0)
    {
        return res;
    }
    for (int i = digits.size() - 1; i >= 0 ; --i)
    {
        if (digits[i] == 0)
        {
            flag = 1;
            --res;
        }
        else
        {
            break;
        }
    }
    if (flag)
    {
        ++res;
    }

    if (digits[res - 1] == 0)
    {
        if (res > 1 && (*reinterpret_cast<unsigned int const*>(&digits[res - 2]) >> ((sizeof(unsigned int) << 3) - 1)) == 0)
        {
            --res;
        }
    }
    else
    {
        if (positive_flag && ((*reinterpret_cast<unsigned int const*>(&digits[res - 1]) >> ((sizeof(unsigned int) << 3) - 1)) == 1))
        {
            ++res;
        }
    }
    return res;
}

int big_integer::get_significant_digits_count(const int* digits, size_t digits_count) const noexcept
{
    if (digits_count == 1 && *digits == 0)
    {
        return digits_count;
    }
    for (int i = digits_count - 1; i >= 0 ; --i)
    {
        if (digits[i] == 0)
        {
            --digits_count;
        }
        else
        {
            break;
        }
    }
    return digits_count;
}

big_integer &big_integer::multiply(
        big_integer &first_multiplier,
        big_integer const &second_multiplier,
        class allocator *allocator,
        big_integer::multiplication_rule multiplication_rule)
{
    switch (multiplication_rule)
    {
        case multiplication_rule::Karatsuba:
            return Karatsuba_multiplication().multiply(first_multiplier, second_multiplier);
        case multiplication_rule::trivial:
            return trivial_multiplication().multiply(first_multiplier, second_multiplier);
        case multiplication_rule::SchonhageStrassen:
            return Schonhage_Strassen_multiplication().multiply(first_multiplier, second_multiplier);
    }
}

big_integer big_integer::multiply(
        big_integer const &first_multiplier,
        big_integer const &second_multiplier,
        class allocator *allocator,
        big_integer::multiplication_rule multiplication_rule)
{
    big_integer copy = first_multiplier;
    switch (multiplication_rule)
    {
        case multiplication_rule::Karatsuba:
            return Karatsuba_multiplication().multiply(copy, second_multiplier);
        case multiplication_rule::trivial:
            return trivial_multiplication().multiply(copy, second_multiplier);
        case multiplication_rule::SchonhageStrassen:
            return Schonhage_Strassen_multiplication().multiply(copy, second_multiplier);
    }
}

big_integer &big_integer::divide(
        big_integer &dividend,
        big_integer const &divisor,
        class allocator *allocator,
        big_integer::division_rule division_rule,
        big_integer::multiplication_rule multiplication_rule)
{
    switch (division_rule)
    {
        case division_rule::trivial:
            return trivial_division().divide(dividend, divisor, multiplication_rule);
        case division_rule::BurnikelZiegler:
            return Burnikel_Ziegler_division().divide(dividend, divisor, multiplication_rule);
        case division_rule::Newton:
            return Newton_division().divide(dividend, divisor, multiplication_rule);
    }
}

big_integer big_integer::divide(
        big_integer const &dividend,
        big_integer const &divisor,
        class allocator *allocator,
        big_integer::division_rule division_rule,
        big_integer::multiplication_rule multiplication_rule)
{
    big_integer copy = dividend;
    switch (division_rule)
    {
        case division_rule::trivial:
            return trivial_division().divide(copy, divisor, multiplication_rule);
        case division_rule::BurnikelZiegler:
            return Burnikel_Ziegler_division().divide(copy, divisor, multiplication_rule);
        case division_rule::Newton:
            return Newton_division().divide(copy, divisor, multiplication_rule);
    }
}

big_integer &big_integer::modulo(
        big_integer &dividend,
        big_integer const &divisor,
        class allocator *allocator,
        big_integer::division_rule division_rule,
        big_integer::multiplication_rule multiplication_rule)
{
    switch (division_rule)
    {
        case division_rule::trivial:
            return trivial_division().modulo(dividend, divisor, multiplication_rule);
        case division_rule::BurnikelZiegler:
            return Burnikel_Ziegler_division().modulo(dividend, divisor, multiplication_rule);
        case division_rule::Newton:
            return Newton_division().modulo(dividend, divisor, multiplication_rule);
    }
}

big_integer big_integer::modulo(
        big_integer const &dividend,
        big_integer const &divisor,
        class allocator *allocator,
        big_integer::division_rule division_rule,
        big_integer::multiplication_rule multiplication_rule)
{
    big_integer copy = dividend;
    switch (division_rule)
    {
        case division_rule::trivial:
            return trivial_division().modulo(copy, divisor, multiplication_rule);
        case division_rule::BurnikelZiegler:
            return Burnikel_Ziegler_division().modulo(copy, divisor, multiplication_rule);
        case division_rule::Newton:
            return Newton_division().modulo(copy, divisor, multiplication_rule);
    }
}
