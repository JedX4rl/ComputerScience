//
// Created by Никита Третьяков on 02.06.2024.
//
#include "../include/continued_fraction.h"

int main()
{
    fraction a(big_integer("13"), big_integer("71"));
//    std::vector<big_integer> h =  continued_fraction::to_continued_fraction_representation(a);
//    auto n = continued_fraction::from_continued_fraction_representation(h);
//    std::cout << n << std::endl;
    auto g = continued_fraction::to_Calkin_Wilf_tree_path(a);
    auto b = continued_fraction::from_Calkin_Wilf_tree_path(g);
    std::cout << b << std::endl;
    std::cout << g.size();

    return 0;
}