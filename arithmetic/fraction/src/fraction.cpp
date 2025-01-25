#include "../include/fraction.h"
#include "not_implemented.h"

big_integer fraction::gcd(const big_integer &numerator, const big_integer &denominator)
{

    big_integer zero("0");
    big_integer one("1");
    big_integer tmp_numerator = numerator;
    big_integer tmp_denominator = denominator;

//    int sign = 1;
    big_integer negative_one("-1");
    if (tmp_numerator.sign() == -1)
    {
        tmp_numerator *= negative_one;
    }

    if (numerator == zero)
    {
        return denominator;
    }
    if (denominator == zero)
    {
        return numerator;
    }
    if (numerator == one)
    {
        return numerator;
    }
    if (numerator == denominator)
    {
        return numerator;
    }
    while (tmp_numerator != zero)
    {
        tmp_denominator %= tmp_numerator;
        big_integer tmp(std::move(tmp_numerator));
        tmp_numerator = std::move(tmp_denominator);
        tmp_denominator = std::move(tmp);
    }

//        if (tmp_numerator > tmp_denominator)
//        {
//            big_integer tmp = tmp_numerator;
//            tmp_numerator = tmp_denominator;
//            tmp_denominator = tmp;
//        }
//        tmp_denominator -= tmp_numerator;
//    }
//    if (sign == -1)
//    {
//        return tmp_numerator *= negative_one;
//    }
    return tmp_denominator;
}

void fraction::equalise_denominator(fraction& first, fraction& second)
{
    fraction tmp = first;

    first._numerator *= second._denominator;
    first._denominator *= second._denominator;

    second._numerator *= tmp._denominator;
    second._denominator *= tmp._denominator;
}

fraction::fraction(
    big_integer &&numerator,
    big_integer &&denominator):
        _numerator(std::forward<big_integer>(numerator)),
        _denominator(std::forward<big_integer>(denominator))
{
    big_integer zero("0");
    if (_denominator == zero)
    {
        throw std::logic_error("division by zero error");
    }
    if (_denominator < zero)
    {
        throw std::logic_error("denominator must be a positive number");
    }
    big_integer t_gcd = gcd(_numerator, _denominator);
    _numerator /= t_gcd;
    _denominator /= t_gcd;
}

fraction::fraction(
    fraction const &other):
        _numerator(other._numerator),
        _denominator(other._denominator)
{

}

fraction &fraction::operator=(
    fraction const &other)
{
    if (this != &other)
    {
        _numerator = other._numerator;
        _denominator = other._denominator;
    }
    return *this;
}

fraction::fraction(
    fraction &&other) noexcept:
        _numerator(std::move(other._numerator)),
        _denominator(std::move(other._denominator))
{

}

fraction &fraction::operator=(
    fraction &&other) noexcept
{
    if (this != &other)
    {
        _numerator = other._numerator;
        _denominator = other._denominator;
    }
    return *this;
}

fraction &fraction::operator+=(
    fraction const &other)
{
    fraction tmp = other;
    if (_denominator == other._denominator)
    {
        _numerator += other._numerator;
        big_integer t_gcd = gcd(_numerator, _denominator);
        _numerator /= t_gcd;
        _denominator /= t_gcd;
    }
    else
    {
        equalise_denominator(*this, tmp);
        _numerator += tmp._numerator;
        big_integer t_gcd = gcd(_numerator, _denominator);
        _numerator /= t_gcd;
        _denominator /= t_gcd;
    }
    return *this;
}

fraction fraction::operator+(
    fraction const &other) const
{
    return fraction(*this) += other;
}

fraction &fraction::operator-=(
    fraction const &other)
{
    fraction tmp = other;
    if (_denominator == other._denominator)
    {
        _numerator -= other._numerator;
        big_integer t_gcd = gcd(_numerator, _denominator);
        _numerator /= t_gcd;
        _denominator /= t_gcd;
    }
    else
    {
        equalise_denominator(*this, tmp);
        _numerator -= tmp._numerator;
        big_integer t_gcd = gcd(_numerator, _denominator);
        _numerator /= t_gcd;
        _denominator /= t_gcd;
    }
    return *this;
}

fraction fraction::operator-(
    fraction const &other) const
{
    return fraction(*this) -= other;
}

fraction &fraction::operator*=(
    fraction const &other)
{
    _numerator *= other._numerator;
    _denominator *= other._denominator;
    big_integer t_gcd = gcd(_numerator, _denominator);
    _numerator /= t_gcd;
    _denominator /= t_gcd;
    return *this;
}

fraction fraction::operator*(
    fraction const &other) const
{
    return fraction(*this) *= other;
}

fraction &fraction::operator/=(
    fraction const &other)
{
    _numerator *= other._denominator;
    _denominator *= other._numerator;
    big_integer t_gcd = gcd(_numerator, _denominator);
    _numerator /= t_gcd;
    _denominator /= t_gcd;
    return *this;
}

//fraction &fraction::operator%=(
//        fraction const &other)
//{
//    _numerator *= other._denominator;
//    _denominator *= other._numerator;
//    big_integer t_gcd = gcd(_numerator, _denominator);
//    _numerator /= t_gcd;
//    _denominator /= t_gcd;
//    return *this;
//}

fraction fraction::operator/(
    fraction const &other) const
{
    return fraction(*this) /= other;
}

//fraction fraction::operator%(
//        fraction const &other) const
//{
//    return fraction(*this) %= other;
//}

bool fraction::operator==(
    fraction const &other) const
{
    if (_denominator != other._denominator)
    {
        return false;
    }
    return _numerator == other._numerator;
}

bool fraction::operator!=(
    fraction const &other) const
{
    return !(*this == other);
}

bool fraction::operator>=(
    fraction const &other) const
{
    return !(*this < other);
}

bool fraction::operator>(
    fraction const &other) const
{
    if (_denominator == other._denominator)
    {
        return _numerator > other._numerator;
    }
    fraction tmp_first = *this;
    fraction tmp_second = other;
    equalise_denominator(tmp_first, tmp_second);
    return tmp_first._numerator > tmp_second._numerator;
}

bool fraction::operator<=(
    fraction const &other) const
{
    return !(*this > other);
}

bool fraction::operator<(
    fraction const &other) const
{
    if (_denominator == other._denominator)
    {
        return _numerator < other._numerator;
    }
    fraction tmp_first = *this;
    fraction tmp_second = other;
    equalise_denominator(tmp_first, tmp_second);
    return tmp_first._numerator < tmp_second._numerator;
}

std::ostream &operator<<(
    std::ostream &stream,
    fraction const &obj)
{
    return stream << obj._numerator << '/' << obj._denominator;
}

std::istream &operator>>(
    std::istream &stream,
    fraction &obj)
{
    std::string string;
    std::string numerator;
    std::string denominator;
    stream >> string;

    size_t found = string.find('/') != std::string::npos;
    numerator = string.substr(0, found);
    denominator = string.substr(found + 1, std::string::npos);
    obj._numerator = big_integer(numerator);
    obj._denominator = big_integer(denominator);
    return stream;
}

fraction fraction::sin(
    fraction const &epsilon) const
{
    fraction zero(big_integer("0"),big_integer("1"));

    if (epsilon <= zero)
    {
        throw std::logic_error("Eps must be > 0");
    }
    fraction one(big_integer("1"),big_integer("1"));
    fraction two(big_integer("2"),big_integer("1"));
    fraction negative_one(big_integer("-1"),big_integer("1"));

    fraction x = *this;
    fraction current = x;
    fraction next = current;
    fraction n = one;
    do
    {
        fraction tmp = two * n;
        current *=  (negative_one * x * x) / (tmp * (tmp + one));
        next += current;
        n._numerator += one._numerator;
    }
    while(abs(current) >= epsilon);
    return next;
}

fraction fraction::cos(
    fraction const &epsilon) const
{
    fraction zero(big_integer("0"),big_integer("1"));

    if (epsilon <= zero)
    {
        throw std::logic_error("Eps must be > 0");
    }
    fraction one(big_integer("1"),big_integer("1"));
    fraction two(big_integer("2"),big_integer("1"));
    fraction negative_one(big_integer("-1"),big_integer("1"));

    fraction x = *this;
    fraction current = one;
    fraction next = current;
    fraction n = one;
    do
    {
        fraction tmp = two * n;
        current *=  (negative_one * x * x) / (tmp * (tmp - one));
        next += current;
        n._numerator += one._numerator;
    }
    while(abs(current) >= epsilon);
    return next;
}

fraction fraction::tg(
    fraction const &epsilon) const
{
    fraction number = *this;
    return number.sin(epsilon) / number.cos(epsilon);
}

fraction fraction::ctg(
    fraction const &epsilon) const
{
    fraction number = *this;
    return number.cos(epsilon) / number.sin(epsilon);
}

fraction fraction::sec(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction one(big_integer("1"), big_integer("1"));
    return one / number.cos(epsilon);
}

fraction fraction::cosec(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction one(big_integer("1"), big_integer("1"));
    return one / number.sin(epsilon);
}

fraction fraction::arcsin(
    fraction const &epsilon) const
{
    fraction zero(big_integer("0"),big_integer("1"));

    if (epsilon <= zero)
    {
        throw std::logic_error("Eps must be > 0");
    }
    fraction one(big_integer("1"),big_integer("1"));
    if (abs(*this) > one)
    {
        throw std::logic_error("Number must be <= |1|");
    }
    fraction two(big_integer("2"),big_integer("1"));

    fraction x = *this;
    fraction current = x;
    fraction next = current;
    fraction n = one;
    do
    {
        fraction tmp = two * n;
        current *=  (tmp - one).pow(2) * x * x / (tmp * (tmp + one));
        next += current;
        n._numerator += one._numerator;
    }
    while(abs(current) >= epsilon);
    return next;
}

fraction fraction::arccos(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction two(big_integer("2"), big_integer("1"));
    return pi(epsilon) / two - number.arcsin(epsilon);
}

fraction fraction::arctg(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction one(big_integer("1"), big_integer("1"));
    return (number/(one + number.pow(2)).root(2, epsilon)).arcsin(epsilon);
}

fraction fraction::arcctg(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction one(big_integer("1"), big_integer("1"));
    return (number/(one + number.pow(2)).root(2, epsilon)).arccos(epsilon);
}

fraction fraction::arcsec(
    fraction const &epsilon) const
{
    fraction one(big_integer("1"), big_integer("1"));
    fraction number = *this;
    if (abs(number) < one)
    {
        throw std::logic_error("|Number| must be > 1");
    }
//    if (number >= one)
//    {
//        return ((number.pow(2) - one).root(2, epsilon) / number).arcsin(epsilon);
//    }
//    else
//    {
//        return pi(epsilon) + ((number.pow(2) - one).root(2, epsilon) / number).arcsin(epsilon);
//    }
    return (one / number).arccos(epsilon);
}

fraction fraction::arccosec(
    fraction const &epsilon) const
{
    fraction one(big_integer("1"), big_integer("1"));
    fraction number = *this;
    if (abs(number) < one)
    {
        throw std::logic_error("|Number| must be > 1");
    }
    return (one / number).arcsin(epsilon);
}

fraction fraction::pow(
    size_t degree) const
{
    if (_numerator == big_integer("0") && degree == 0)
    {
        throw std::logic_error("0 powered zero");
    }
    if (degree == 0)
    {
        return *this / *this;
    }
    fraction value = *this;
    fraction tmp_res(big_integer("1"), big_integer("1"));
    while (degree > 0)
    {
        if (degree % 2 == 1)
        {
            tmp_res *= value;
        }
        value *= value;
        degree /= 2;
    }
    return tmp_res;
}

fraction fraction::abs(fraction number)
{
    if (number._numerator < big_integer("0"))
    {
        number._numerator *= big_integer("-1");
        return number;
    }
    return number;
}

fraction fraction::root(
    size_t degree,
    fraction const &epsilon)
{

    if (degree == 0)
    {
        throw std::logic_error("Crazy");
    }
    if (degree == 1)
    {
        return *this;
    }

    big_integer zero("0");
    big_integer one("1");
    fraction fraction_one(big_integer("1"), big_integer("1"));
    fraction fraction_degree(big_integer(std::to_string(degree)), big_integer("1"));
    fraction tmp_fraction = *this;

    fraction negative_one(big_integer("-1"), big_integer("1"));

    int sign = 1;
    int l = 0;

    if (degree % 2 && tmp_fraction._numerator < zero)
    {
        throw std::logic_error("0__0");
    }
    if (!(degree % 2) && tmp_fraction._numerator < zero)
    {
        sign = -1;
        tmp_fraction *= negative_one;
    }

    fraction current = (fraction(big_integer("1"), big_integer("1")) + tmp_fraction)
                            / fraction(big_integer("2"), big_integer("1"));
    fraction next = current;

    fraction one_by_n(big_integer("1"), big_integer(std::to_string(degree)));

    fraction prev_degree = fraction_degree - fraction_one;

    do
    {
        current = next;
        next = one_by_n * (prev_degree * current + tmp_fraction / current.pow(degree - 1));

    }
    while (abs(next - current) >= epsilon);

    if (sign == -1)
    {
        return current *= negative_one;
    }
    return next;
}


fraction fraction::log2(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction ten(big_integer("2"), big_integer("1"));
    return number.ln(epsilon) / ten.ln(epsilon);
}

fraction fraction::ln(
    fraction const &epsilon) const
{

    big_integer zero("0");
    big_integer two("2");

    fraction one(big_integer("1"),big_integer("1"));
    fraction zero_fraction(big_integer("0"),big_integer("1"));
    if (*this <= zero_fraction)
    {
        throw std::logic_error("Number must be > 0");
    }
    if (epsilon <= zero_fraction)
    {
        throw std::logic_error("Eps must be > 0");
    }

    fraction number = *this;

    fraction current = one;
    fraction next = current;
    fraction x = (number - one) / (number + one);
    fraction sum = x;
    fraction iter = one;
    do
    {
        current *= x * x;
        iter._numerator += two;
        next = current / iter;
        sum += next;
    }
    while(abs(current - next) >= epsilon);

    sum *= fraction(big_integer("2"), big_integer("1"));
    return sum;
}

fraction fraction::lg(
    fraction const &epsilon) const
{
    fraction number = *this;
    fraction ten(big_integer("10"), big_integer("1"));
    return number.ln(epsilon) / ten.ln(epsilon);
}

fraction fraction::pi(const fraction &eps)
{

    double pi = M_PI;
    pi *= 100000000;
    int p_i = floor(pi);
    return fraction(big_integer(std::vector<int>{p_i}), big_integer(std::vector<int>{100000000}));
//    fraction zero(big_integer("0"),big_integer("1"));
//
//    if (eps <= zero)
//    {
//        throw std::logic_error("Eps must be > 0");
//    }
//    fraction one(big_integer("1"),big_integer("1"));
//    fraction two(big_integer("2"),big_integer("1"));
//    fraction four(big_integer("4"),big_integer("1"));
//
//
//    fraction n = one;
//    fraction prev = zero;
//    fraction current = four;
//    do
//    {
//        n._numerator += one._numerator;
//        prev = current;
//        fraction tmp = n * two - one;
//        tmp += tmp;
//        current *= four * n * (n - one) / (tmp);
//
//    }
//    while(abs(current - prev) >= eps);
//    return current;
}

fraction fraction::exp(const fraction &eps)
{

    fraction one(big_integer("1"),big_integer("1"));
    fraction zero(big_integer("0"),big_integer("1"));
    if (eps <= zero)
    {
        throw std::logic_error("Eps must be > 0");
    }

    fraction current = one;
    fraction next = current;
    big_integer i("1");
    fraction x = one;
    do
    {
        current = next;
        next += one / x;
        std::cout << "curr: " << current << std::endl;
        std::cout << "next: " << next << std::endl;
        i += one._numerator;
        x._numerator *= i;
    }
    while(abs(current - next) >= eps);


    return next;
}