#include <gtest/gtest.h>

#include <big_integer.h>
#include <client_logger.h>
#include <operation_not_supported.h>
#include "../../fraction/include/fraction.h"

logger *create_logger(
    std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
    bool use_console_stream = true,
    logger::severity console_stream_severity = logger::severity::debug)
{
    logger_builder *builder = new client_logger_builder();
    
    if (use_console_stream)
    {
        builder->add_console_stream(console_stream_severity);
    }
    
    for (auto &output_file_stream_setup: output_file_streams_setup)
    {
        builder->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
    }
    
    logger *built_logger = builder->build();
    
    delete builder;
    
    return built_logger;
}

TEST(positive_tests, test1)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("32850346459076457453464575686784654");
    big_integer bigint_2("423534596495087569087908753095322");
    big_integer result_of_sum = bigint_1 + bigint_2;
    result_of_sum.dump_value(std::cout << std::endl);

    std::stringstream ss;
    ss << result_of_sum;
    std::string result_string = ss.str();
    EXPECT_TRUE(result_string == "33273881055571545022552484439879976");

    delete logger;
}

TEST(positive_tests, test2)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("32850346459076457453464575686784654");
    big_integer bigint_2("0000042353459649508756908790875309532245366457546765745645647567575");

    big_integer result_of_sub = bigint_1 - bigint_2;

//    std::stringstream ss;
//    ss << result_of_sub;
//    std::string result_string = ss.str();

    big_integer res("-42353459649508756908790875276681898907381089312281069960782921");

//    EXPECT_TRUE(result_string == "-42353459649508756908790875276681898907381089312281069960782921");

    EXPECT_TRUE(res == result_of_sub);
    delete logger;
}

TEST(positive_tests, test3)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("32850346459076457453464575686784654");
    big_integer bigint_2("12342357553253");

    big_integer result_of_remainder = bigint_1 % bigint_2;

    std::stringstream ss;
    ss << result_of_remainder;
    std::string result_string = ss.str();

    EXPECT_TRUE(result_string == "3232571319826");

    delete logger;
}

TEST(positive_tests, test4)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("-54357893745346457544353");
    big_integer bigint_2("-54357893745346457544354");

    EXPECT_TRUE(bigint_1 > bigint_2);

    delete logger;
}

TEST(positive_tests, test5)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("423895435432");
    big_integer bigint_2("423895435432");

    EXPECT_TRUE(bigint_1 >= bigint_2);

    delete logger;
}

TEST(positive_tests, test6)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("-423895435432312432534645756753");
    big_integer bigint_2("0");

    EXPECT_TRUE(bigint_1 < bigint_2);

    delete logger;
}

TEST(positive_tests, test7)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("4238954354324222200000000");
    big_integer bigint_2("4238954354324222222222234");

    EXPECT_TRUE(bigint_1 <= bigint_2);

    delete logger;
}

TEST(positive_tests, test8)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("4238954354321");
    big_integer bigint_2("423895435432");

    EXPECT_TRUE(bigint_1 != bigint_2);

    delete logger;
}

TEST(positive_tests, test9)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
        {
            {
                "bigint_logs.txt",
                logger::severity::information
            },
        });

    big_integer bigint_1("-00000044234235347865897389456748953795739648996453238954354321");
    big_integer bigint_2("-00000044234235347865897389456748953795739648996453238954354321");

    EXPECT_TRUE(bigint_1 == bigint_2);

    delete logger;
}

//int main()
//{
//
//    //static_cast<int>((0x80000002)) //function for digits significant
//    std::vector<int> a = {1 << 30}; //c 5 " 1 4
//    std::vector<int> b = {1, 1}; //d 5 " 0 4
//    std::vector<int> q = {1 << 31}; //d 5 " 0 4
//    std::vector<int> e = {1 << 30};
//
//    //d 5 " 0 4
////    big_integer{q}.dump_value(std::cout);
////    big_integer res1 = big_integer{q} + big_integer{e};
////    res1.dump_value(std::cout << std::endl);
//
////    big_integer c(std::vector<int>{1, 7, 8, 9});
////    big_integer d(std::vector<int>{2, 3, 1});
////
////    big_integer c1(std::vector<int>{7, 8 , 9});
//    big_integer c("630031123123131231231231412451251251251251417246124712843124981274712749127481279847127412");
//    big_integer d("32");
//
//    std::string g = c.big_int_to_string();
//    std::cout << g << std::endl;
//
//    std::cout << c;
//
////    c %= d;
////    c.dump_value(std::cout);
//
//
////    (~t).dump_value(std::cout << std::endl);
//
////     big_integer h = c / d;
////
////     h.dump_value(std::cout << std::endl << std::endl);
//
//     int k = 1;
//
////    big_integer c("1");
////    for (int i = 0; i < 8; ++i)
////    {
////        c.dump_value(std::cout << std::endl);
////        c *= big_integer("2");
////
////    }
////    std::cout << "--------\n";
////    big_integer d("3");
////    for (int i = 0; i < 33; ++i)
////    {
////        if (i ==10)
////        {
////            int v = 1;
////        }
////        d.dump_value(std::cout << std::endl);
////        d <<= 3;
////    }
////    std::cout << std::endl;
////    (big_integer("1") << 32).dump_value(std::cout);
//
//
////    00000001 00000000 00000000 00000000
////    00000010 00000000 00000000 00000000  00000001 00000000 00000000 10000000
////    00000100 00000000 00000000 00000000  00000010 00000000 00000000 10000000
////    00001000 00000000 00000000 00000000  00000100 00000000 00000000 10000000
////    00010000 00000000 00000000 00000000  00001000 00000000 00000000 10000000
////    00100000 00000000 00000000 00000000  00010000 00000000 00000000 10000000
////    01000000 00000000 00000000 00000000  00100000 00000000 00000000 10000000
//
//
////    c.dump_value(std::cout);
////    big_integer c1("-0");
////    c1.dump_value(std::cout << std::endl);
////    (c << 1).dump_value(std::cout << std::endl);
////    (c << 2).dump_value(std::cout << std::endl);
////    (c << 3).dump_value(std::cout << std::endl);
////    (c << 4).dump_value(std::cout << std::endl);
//
////    big_integer d(e);
////    d.dump_value(std::cout << std::endl);
////    big_integer res = c * c1;
////    res.dump_value(std::cout << std::endl);
////    std::cout<<std::endl;
//}

int main(
    int argc,
    char **argv)
{

    big_integer a("63340828764059520458379290673212321580752174718721");
    big_integer b("5758158596535184995813207565491950149003704448861");
    std::cout << a/b << std::endl;

//    fraction a(big_integer("10"), big_integer("4"));
//    std::cout << a << std::endl;
//    testing::InitGoogleTest(&argc, argv);
//
//    return RUN_ALL_TESTS();
}
