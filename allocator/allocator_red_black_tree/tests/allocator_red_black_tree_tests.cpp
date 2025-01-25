#include <gtest/gtest.h>
#include <logger.h>
#include <logger_builder.h>
#include <client_logger_builder.h>
#include <list>

#include "../include/allocator_red_black_tree.h"

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

TEST(positive_tests, test1) {
    //TODO: logger
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
                                           {
                                                   {"allocator_sorted_list_tests_logs_negative_test_2.txt",
                                                    logger::severity::debug}
                                           });

    allocator *alloc = new allocator_red_black_tree(3000, nullptr, logger, allocator_with_fit_mode::fit_mode::first_fit);



    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 21));
    alloc->deallocate(first_block);
    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 31));
    auto third_block = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 11));
    auto a = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 4));
    auto b = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 2));
    auto c = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 6));
    auto d = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 8));
    auto e = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 1));
    auto f = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 22));
    auto g = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 15));
    auto h = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 15));
    auto i = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 11));
    auto j = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 5));
    auto k = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 9));
    auto l = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 23));
    auto m = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 5));


    alloc->deallocate(third_block);
    alloc->deallocate(a);
    alloc->deallocate(c);
    alloc->deallocate(e);
    alloc->deallocate(g);
    alloc->deallocate(i);
    alloc->deallocate(k);
    alloc->deallocate(m);

//    auto fifth = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 423));

    auto block9 = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 4));

    auto block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 6)); //HERE
    alloc->deallocate(second_block);
//    auto block10 = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 100));

    alloc->deallocate(block9);
//    auto block5 = reinterpret_cast<int*>(alloc->allocate(sizeof(int), 250));
    alloc->deallocate(block);
//    alloc->deallocate(block5);
//    alloc->deallocate(block10);

    delete alloc;
}

int main(
        int argc,
        char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}