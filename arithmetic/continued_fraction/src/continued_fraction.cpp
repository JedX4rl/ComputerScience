#include "../include/continued_fraction.h"

#include <not_implemented.h>
#include <bitset>

std::vector<big_integer> continued_fraction::to_continued_fraction_representation(
    fraction const &value)
{
    fraction number = value;
    std::vector<big_integer> result;
    fraction one(big_integer("1"), big_integer("1"));
    big_integer zero("0");
    big_integer quotient = zero;
    big_integer remainder = zero;

    while (true)
    {
        quotient = number._numerator / number._denominator;
        remainder = number._numerator % number._denominator;
        if (remainder < zero)
        {
            quotient -= big_integer("1");
            remainder += number._denominator;
        }

        result.push_back(quotient);
        number._numerator = remainder;

        if (number._numerator == zero)
        {
            break;
        }

        number = one / number;
    }
    return result;
}

fraction continued_fraction::from_continued_fraction_representation(
    std::vector<big_integer> const &continued_fraction_representation)
{
    //TODO exception
    big_integer prev_prev_p("1");
    big_integer prev_prev_q("0");

    big_integer prev_p = continued_fraction_representation[0];
    big_integer prev_q("1");

    big_integer curr_p("0");
    big_integer curr_q("0");

    for (int i = 1; i < continued_fraction_representation.size(); ++i)
    {
        curr_p = prev_p * continued_fraction_representation[i] + prev_prev_p;
        curr_q = prev_q * continued_fraction_representation[i] + prev_prev_q;

        prev_prev_p = prev_p;
        prev_p = curr_p;
        prev_prev_q = prev_q;
        prev_q = curr_q;
    }

    return fraction(std::move(curr_p), std::move(curr_q));
}

std::vector<fraction> continued_fraction::to_convergents_series(
    fraction const &value)
{
    std::vector<big_integer> tmp = continued_fraction::to_continued_fraction_representation(value);
    return continued_fraction::to_convergents_series(tmp);

}

std::vector<fraction> continued_fraction::to_convergents_series(
    std::vector<big_integer> const &continued_fraction_representation)
{
    std::vector<fraction> result;

    big_integer prev_prev_p("1");
    big_integer prev_prev_q("0");

    big_integer prev_p = continued_fraction_representation[0];
    big_integer prev_q("1");

    big_integer tmp = continued_fraction_representation[0];

    result.emplace_back(std::move(tmp), big_integer("1"));

    big_integer curr_p("0");
    big_integer curr_q("0");

    for (int i = 1; i < continued_fraction_representation.size(); ++i)
    {
        curr_p = prev_p * continued_fraction_representation[i] + prev_prev_p;
        curr_q = prev_q * continued_fraction_representation[i] + prev_prev_q;

        prev_prev_p = prev_p;
        prev_p = curr_p;
        prev_prev_q = prev_q;
        prev_q = curr_q;
        result.emplace_back(std::move(curr_p), std::move(curr_q));
    }
    return result;
}

std::vector<bool> continued_fraction::to_Stern_Brokot_tree_path(
    fraction const &value)
{

    if (value._numerator.sign() <= 0)
    {
        throw std::logic_error("Must be greater than 0");
    }

    std::vector<bool> result; //0 - left 1 - right
    big_integer left_a("0");
    big_integer left_b("1");
    big_integer right_a("1");
    big_integer right_b("0");
    fraction current(big_integer("1"), big_integer("1"));
    while (true)
    {
        if (value > current)
        {
            left_a = current._numerator;
            left_b = current._denominator;
            current._numerator += right_a;
            current._denominator += right_b; //TODO set / get
            result.push_back(true);
        }
        else if (value < current)
        {
            right_a = current._numerator;
            right_b = current._denominator;
            current._numerator += left_a;
            current._denominator += left_b;
            result.push_back(false);
        }
        else
        {
            break;
        }
    }
    return result;
}

fraction continued_fraction::from_Stern_Brokot_tree_path(
    std::vector<bool> const &path)
{
    big_integer left_a("0");
    big_integer left_b("1");
    big_integer right_a("1");
    big_integer right_b("0");
    fraction result(big_integer("1"), big_integer("1"));
    for (auto item : path)
    {
        if (item == 0)
        {
            right_a = result._numerator;
            right_b = result._denominator;
            result._numerator += left_a;
            result._denominator += left_b;
        }
        else
        {
            left_a = result._numerator;
            left_b = result._denominator;
            result._numerator += right_a;
            result._denominator += right_b;
        }
    }
    return result;
}

std::vector<bool> continued_fraction::to_Calkin_Wilf_tree_path(
    fraction const &value)
{
    if (value._numerator.sign() <= 0)
    {
        throw std::logic_error("Must be greater than 0");
    }

    std::vector<bool> result; //0 - left 1 - right
    fraction current(big_integer("1"), big_integer("1"));
    fraction two(big_integer("2"), big_integer("1"));
    fraction one = current;
    size_t position = 1;
    size_t t;
    while (current != value)
    {
        fraction tmp(current._numerator / current._denominator, big_integer("1"));
        current = one / (two * tmp + one - current);
        ++position;
    }
    while(position)
    {
        t = position % 2;
        position /= 2;
        result.push_back(t);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

fraction continued_fraction::from_Calkin_Wilf_tree_path(
    std::vector<bool> const &path)
{
    fraction current(big_integer("1"), big_integer("1"));
    fraction two(big_integer("2"), big_integer("1"));
    fraction one = current;
    size_t position = 0;
    long long base = 1;
    for (long long i = path.size() - 1; i >= 0; --i)
    {
        if (path[i])
        {
            position += base;
        }
        base *= 2;
    }
    for (long long i = 0; i < position - 1; ++i)
    {
        fraction tmp(current._numerator / current._denominator, big_integer("1"));
        current = one / (two * tmp + one - current);
    }
    return current;
}