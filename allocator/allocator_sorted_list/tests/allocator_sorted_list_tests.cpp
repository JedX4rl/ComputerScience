//#include <gtest/gtest.h>
//#include <logger.h>
//#include <logger_builder.h>
//#include <client_logger_builder.h>
//#include <list>
//
//#include "../include/allocator_sorted_list.h"
//
//logger *create_logger(
//    std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
//    bool use_console_stream = true,
//    logger::severity console_stream_severity = logger::severity::debug)
//{
//    logger_builder *builder = new client_logger_builder();
//
//    if (use_console_stream)
//    {
//        builder->add_console_stream(console_stream_severity);
//    }
//
//    for (auto &output_file_stream_setup: output_file_streams_setup)
//    {
//        builder->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
//    }
//
//    logger *built_logger = builder->build();
//
//    delete builder;
//
//    return built_logger;
//}
//
//TEST(allocatorSortedListPositiveTests, test1)
//{
//    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
//    {
//            {
//                    "allocator_sorted_list_tests_logs_false_positive_test_2.txt",
//                        logger::severity::information
//            },
//            {
//                    "", logger::severity::debug
//            },
//            {
//                    "", logger::severity::error
//            }
//    });
//
//    allocator *alloc = new allocator_sorted_list(3000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 250));
//
//    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(int), 250));
//    alloc->deallocate(first_block);
//
//    first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 245));
//
//    alloc->deallocate(second_block);
//    alloc->deallocate(first_block);
//
//    //TODO: Проверка
//
//    delete alloc;
//}
//
//TEST(allocatorSortedListPositiveTests, test2)
//{
//
//    //TODO: logger
//
//    allocator *alloc = new allocator_sorted_list(3000, nullptr, nullptr,
//        allocator_with_fit_mode::fit_mode::the_worst_fit);
//
//    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 250));
//
//    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(alloc);
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::first_fit);
//    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(char), 500));
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
//    auto third_block = reinterpret_cast<double *>(alloc->allocate(sizeof(double *), 100));
//
//    alloc->deallocate(first_block);
//    alloc->deallocate(second_block);
//    alloc->deallocate(third_block);
//
//    //TODO: проверка
//
//    delete alloc;
//}
//
//TEST(allocatorSortedListPositiveTests, test3)
//{
//    //TODO: logger
//    allocator *allocator = new allocator_sorted_list(5000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
//
//    int iterations_count = 100;
//
//    std::list<void *> allocated_blocks;
//    srand((unsigned)time(nullptr));
//
//    for (auto i = 0; i < iterations_count; i++)
//    {
//        switch (rand() % 2)
//        {
//            case 0:
//            case 1:
//                try
//                {
//                    allocated_blocks.push_front(allocator->allocate(sizeof(void *), rand() % 251 + 50));
//                    std::cout << "allocation succeeded" << std::endl;
//                }
//                catch (std::bad_alloc const &ex)
//                {
//                    std::cout << ex.what() << std::endl;
//                }
//                break;
//            case 2:
//                if (allocated_blocks.empty())
//                {
//                    std::cout << "No blocks to deallocate" << std::endl;
//
//                    break;
//                }
//
//                auto it = allocated_blocks.begin();
//                std::advance(it, rand() % allocated_blocks.size());
//                allocator->deallocate(*it);
//                allocated_blocks.erase(it);
//                std::cout << "deallocation succeeded" << std::endl;
//                break;
//        }
//    }
//
//    while (!allocated_blocks.empty())
//    {
//        auto it = allocated_blocks.begin();
//        std::advance(it, rand() % allocated_blocks.size());
//        allocator->deallocate(*it);
//        allocated_blocks.erase(it);
//        std::cout << "deallocation succeeded" << std::endl;
//    }
//
//    //TODO: проверка
//
//    delete allocator;
//    // delete logger;
//
//
//}
//
//TEST(allocatorSortedListPositiveTests, test4)
//{
//    //TODO: logger
//
//    allocator *alloc = new allocator_sorted_list(1000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto first_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char), 250));
//    auto second_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(char), 150));
//    auto third_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char *), 300));
//
//    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(alloc);
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
//    auto four_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char *), 50));
//
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
//    auto five_block = reinterpret_cast<unsigned char *>(alloc->allocate(sizeof(unsigned char *), 50));
//
//    alloc->deallocate(first_block);
//    alloc->deallocate(second_block);
//    alloc->deallocate(third_block);
//    alloc->deallocate(four_block);
//    alloc->deallocate(five_block);
//
//    //TODO: проверка
//
//    delete alloc;
//}
//
//TEST(allocatorSortedListPositiveTests, test5)
//{
//    allocator *alloc = new allocator_sorted_list(3000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 250));
//    auto second_block = reinterpret_cast<char *>(alloc->allocate(sizeof(char), 500));
//    auto third_block = reinterpret_cast<double *>(alloc->allocate(sizeof(double *), 250));
//    alloc->deallocate(first_block);
//    first_block = reinterpret_cast<int *>(alloc->allocate(sizeof(int), 245));
//
//    //TODO: logger
//    allocator *allocator = new allocator_sorted_list(5000, nullptr, nullptr, allocator_with_fit_mode::fit_mode::first_fit);
//    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(alloc);
//    int iterations_count = 100;
//
//    std::list<void *> allocated_blocks;
//    srand((unsigned)time(nullptr));
//
//    for (auto i = 0; i < iterations_count; i++)
//    {
//        switch (rand() % 2)
//        {
//            case 0:
//            case 1:
//                try
//                {
//                    switch (rand() % 2)
//                    {
//                        case 0:
//                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::first_fit);
//                        case 1:
//                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
//                        case 2:
//                            the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
//                    }
//
//                    allocated_blocks.push_front(allocator->allocate(sizeof(void *), rand() % 251 + 50));
//                    std::cout << "allocation succeeded" << std::endl;
//                }
//                catch (std::bad_alloc const &ex)
//                {
//                    std::cout << ex.what() << std::endl;
//                }
//                break;
//            case 2:
//                if (allocated_blocks.empty())
//                {
//                    std::cout << "No blocks to deallocate" << std::endl;
//
//                    break;
//                }
//
//                auto it = allocated_blocks.begin();
//                std::advance(it, rand() % allocated_blocks.size());
//                allocator->deallocate(*it);
//                allocated_blocks.erase(it);
//                std::cout << "deallocation succeeded" << std::endl;
//                break;
//        }
//    }
//
//    while (!allocated_blocks.empty())
//    {
//        auto it = allocated_blocks.begin();
//        std::advance(it, rand() % allocated_blocks.size());
//        allocator->deallocate(*it);
//        allocated_blocks.erase(it);
//        std::cout << "deallocation succeeded" << std::endl;
//    }
//
//    //TODO: проверка
//
//    delete allocator;
//    // delete logger;
//
//    delete alloc;
//}
//
//
////TODO: Тесты на особенность аллокатора?
//
//TEST(allocatorSortedListNegativeTests, test1)
//{
//    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
//        {
//            {
//                "allocator_sorted_list_tests_logs_negative_test_1.txt",
//                logger::severity::information
//            }
//        });
//    allocator *alloc = new allocator_sorted_list(3000, nullptr, logger, allocator_with_fit_mode::fit_mode::first_fit);
//
//    ASSERT_THROW(alloc->allocate(sizeof(char), 3100), std::bad_alloc);
//
//    delete alloc;
//    delete logger;
//}
//
//int main(
//    int argc,
//    char **argv)
//{
//    testing::InitGoogleTest(&argc, argv);
//
//    return RUN_ALL_TESTS();
//}

//#include <gtest/gtest.h>
//#include <allocator.h>
//#include <allocator_sorted_list.h>
//#include <client_logger_builder.h>
//#include <logger.h>
//#include <logger_builder.h>
//
//logger *create_logger(
//    std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup,
//    bool use_console_stream = true,
//    logger::severity console_stream_severity = logger::severity::debug)
//{
//    logger_builder *logger_builder_instance = new client_logger_builder;
//
//    if (use_console_stream)
//    {
//        logger_builder_instance->add_console_stream(console_stream_severity);
//    }
//
//    for (auto &output_file_stream_setup: output_file_streams_setup)
//    {
//        logger_builder_instance->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
//    }
//
//    logger *logger_instance = logger_builder_instance->build();
//
//    delete logger_builder_instance;
//
//    return logger_instance;
//}
//
//TEST(positiveTests, test1)
//{
//    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
//        {
//            {
//                "allocator_sorted_list_tests_logs_positive_test_plain_usage.txt",
//                logger::severity::information
//            },
//            {
//                    "", logger::severity::trace
//            },
//            {
//                    "", logger::severity::debug
//            },
//            {
//                    "", logger::severity::information
//            },
//            {
//                    "", logger::severity::error
//            }
//        });
//    allocator *subject = new allocator_sorted_list(sizeof(int) * 40, nullptr, logger, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto const *first_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
//    auto const *second_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
//    auto const *third_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
//
//    ASSERT_EQ(first_block + 10, second_block);
//    ASSERT_EQ(second_block + 10, third_block);
//
//    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(second_block)));
//
//    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(subject);
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
//    auto const *fourth_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 1));
//    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
//    auto const *fifth_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 1));
//
//    ASSERT_EQ(first_block + 10, fifth_block);
//    ASSERT_EQ(third_block + 10, fourth_block);
//
//    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(first_block)));
//    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(third_block)));
//    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(fourth_block)));
//    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(fifth_block)));
//
//    delete subject;
//    delete logger;
//}
//
//TEST(positiveTests, test2)
//{
//    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
//        {
//            {
//                "allocator_sorted_list_tests_logs_false_positive_test_1.txt",
//                logger::severity::information
//            },
//            {
//                    "", logger::severity::trace
//            },
//            {
//                    "", logger::severity::debug
//            },
//            {
//                    "", logger::severity::information
//            },
//            {
//                    "", logger::severity::error
//            }
//        });
//    allocator *allocator_instance = new allocator_sorted_list(sizeof(unsigned char) * 3000, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);
//
//    char *first_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 1000));
//    char *second_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 0));
//    allocator_instance->deallocate(first_block);
//    first_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 999));
//    auto actual_blocks_state = dynamic_cast<allocator_test_utils *>(allocator_instance)->get_blocks_info();
//    std::vector<allocator_test_utils::block_info> expected_blocks_state
//        {
//            { .block_size = 1000 + sizeof(allocator::block_size_t) + sizeof(allocator::block_pointer_t) * 2, .is_block_occupied = true },
//            { .block_size = 1000 + sizeof(allocator::block_size_t) + sizeof(allocator::block_pointer_t) * 2, .is_block_occupied = true },
//            { .block_size = 3000 - (1000 + sizeof(allocator::block_size_t) + sizeof(allocator::block_pointer_t)) * 2, .is_block_occupied = false }
//        };
//
//    ASSERT_EQ(actual_blocks_state.size(), expected_blocks_state.size());
//    for (int i = 0; i < actual_blocks_state.size(); i++)
//    {
//        ASSERT_EQ(actual_blocks_state[i], expected_blocks_state[i]);
//    }
//
//    allocator_instance->deallocate(first_block);
//    allocator_instance->deallocate(second_block);
//
//    delete allocator_instance;
//    delete logger_instance;
//}
//
//TEST(falsePositiveTests, test1)
//{
//    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
//        {
//            {
//                "allocator_sorted_list_tests_logs_false_positive_test_2.txt",
//                logger::severity::information
//            },
//            {
//                    "", logger::severity::trace
//            },
//            {
//                    "", logger::severity::debug
//            },
//            {
//                    "", logger::severity::information
//            },
//            {
//                    "", logger::severity::error
//            }
//        });
//    allocator *allocator_instance = new allocator_sorted_list(3000, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);
//
//    ASSERT_THROW(static_cast<void>(allocator_instance->allocate(sizeof(char), 3000)), std::bad_alloc);
//
//    delete allocator_instance;
//    delete logger_instance;
//}
//
//TEST(falsePositiveTests, test2)
//{
//    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
//    {
//        {
//                "allocator_sorted_list_tests_logs_false_positive_test_3.txt",
//                    logger::severity::information
//        },
//        {
//                "", logger::severity::debug
//        },
//        {
//                "", logger::severity::information
//        },
//        {
//                "", logger::severity::error
//        }
//    });
//    allocator *allocator_parent = new allocator_sorted_list(250, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto *allocator_child = reinterpret_cast<allocator_sorted_list *>(allocator_parent->allocate(sizeof(allocator_sorted_list), 1));
//    allocator::construct(allocator_child, 50, allocator_parent, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);
//
//    auto *block = reinterpret_cast<char *>(allocator_child->allocate(sizeof(char), 10));
//
//    ASSERT_THROW(allocator_parent->deallocate(block), std::logic_error);
//
//    allocator_child->deallocate(block);
//    allocator::destruct(allocator_child);
//    allocator_parent->deallocate(allocator_child);
//
//    delete allocator_parent;
//    delete logger_instance;
//}
//
//int main(
//    int argc,
//    char *argv[])
//{
//    testing::InitGoogleTest(&argc, argv);
//
//    return RUN_ALL_TESTS();
//}

#include <gtest/gtest.h>
#include <allocator.h>
#include <allocator_sorted_list.h>
#include <client_logger_builder.h>
#include <logger.h>
#include <logger_builder.h>

logger *create_logger(
        std::vector<std::pair<std::string, logger::severity>> const &output_file_streams_setup)
{
    logger_builder *logger_builder_instance = new client_logger_builder;

    for (auto &output_file_stream_setup: output_file_streams_setup)
    {
        if (output_file_stream_setup.first.size())
        {
            logger_builder_instance->add_file_stream(output_file_stream_setup.first, output_file_stream_setup.second);
        }
        else
        {
            logger_builder_instance->add_console_stream(output_file_stream_setup.second);
        }
    }

    logger *logger_instance = logger_builder_instance->build();

    delete logger_builder_instance;

    return logger_instance;
}

const size_t block_meta_size = sizeof(size_t) + sizeof(void *); //occupied :  sizeof(block_size_t) + sizeof(allocator*);

TEST(positiveTests, test1)
{
    logger *logger = create_logger(std::vector<std::pair<std::string, logger::severity>>
                                           {
                                                   {
                                                           "allocator_sorted_list_tests_logs_positive_test_plain_usage.txt",
                                                               logger::severity::information
                                                   },
                                                   {
                                                           "", logger::severity::debug
                                                   },
                                                   {
                                                           "", logger::severity::information
                                                   }
                                           });
    allocator *subject = new allocator_sorted_list(sizeof(int) * 100, nullptr, logger, allocator_with_fit_mode::fit_mode::first_fit);

    auto const *first_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
    auto const *second_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
    auto const *third_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 10));
    size_t a = block_meta_size;

    ASSERT_EQ(first_block + 10 + block_meta_size / sizeof(int), second_block);
    ASSERT_EQ(second_block + 10 + block_meta_size / sizeof(int), third_block);

    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(second_block)));

    auto *the_same_subject = dynamic_cast<allocator_with_fit_mode *>(subject);
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_worst_fit);
    auto const *fourth_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 1));
    the_same_subject->set_fit_mode(allocator_with_fit_mode::fit_mode::the_best_fit);
    auto const *fifth_block = reinterpret_cast<int const *>(subject->allocate(sizeof(int), 1));


    ASSERT_EQ(first_block + 10 + block_meta_size / sizeof(int), fifth_block);
    ASSERT_EQ(third_block + 10 + block_meta_size / sizeof(int), fourth_block);

    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(first_block)));
    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(third_block)));
    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(fourth_block)));
    subject->deallocate(const_cast<void *>(reinterpret_cast<void const *>(fifth_block)));

    delete subject;
    delete logger;
}

TEST(positiveTests, test2)
{
    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                    {
                                                            {
                                                                    "allocator_sorted_list_tests_logs_false_positive_test_1.txt",
                                                                        logger::severity::information
                                                            },
                                                            {
                                                                    "", logger::severity::debug
                                                            },
                                                            {
                                                                    "", logger::severity::warning
                                                            }
                                                    });
    allocator *allocator_instance = new allocator_sorted_list(sizeof(unsigned char) * 300, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);

    char *first_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 100));
    char *second_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 100));
    allocator_instance->deallocate(first_block);
    first_block = reinterpret_cast<char *>(allocator_instance->allocate(sizeof(char), 99));
    auto actual_blocks_state = dynamic_cast<allocator_test_utils *>(allocator_instance)->get_blocks_info();
    std::vector<allocator_test_utils::block_info> expected_blocks_state
            {
                    { .block_size = 100 + block_meta_size, .is_block_occupied = true },
                    { .block_size = 100 + block_meta_size, .is_block_occupied = true },
                    { .block_size = 300 - (100 + block_meta_size) * 2, .is_block_occupied = false }
            };

    ASSERT_EQ(actual_blocks_state.size(), expected_blocks_state.size());
    for (int i = 0; i < actual_blocks_state.size(); i++)
    {
        ASSERT_EQ(actual_blocks_state[i], expected_blocks_state[i]);
    }

    allocator_instance->deallocate(first_block);
    allocator_instance->deallocate(second_block);

    delete allocator_instance;
    delete logger_instance;
}

TEST(falsePositiveTests, test1)
{
    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                    {
                                                            {
                                                                    "allocator_sorted_list_tests_logs_false_positive_test_2.txt",
                                                                        logger::severity::information
                                                            },
                                                            {
                                                                    "", logger::severity::debug
                                                            },
                                                            {
                                                                    "", logger::severity::error
                                                            }
                                                    });
    allocator *allocator_instance = new allocator_sorted_list(3000, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);

    ASSERT_THROW(static_cast<void>(allocator_instance->allocate(sizeof(char), 3000)), std::bad_alloc);

    delete allocator_instance;
    delete logger_instance;
}

TEST(falsePositiveTests, test2)
{
    logger *logger_instance = create_logger(std::vector<std::pair<std::string, logger::severity>>
                                                    {
                                                            {
                                                                    "allocator_sorted_list_tests_logs_false_positive_test_3.txt",
                                                                        logger::severity::information
                                                            },
                                                            {
                                                                    "", logger::severity::debug
                                                            },
                                                            {
                                                                    "", logger::severity::information
                                                            },
                                                            {
                                                                    "", logger::severity::error
                                                            }
                                                    });
    allocator *allocator_parent = new allocator_sorted_list(250, nullptr, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);

    auto *allocator_child = reinterpret_cast<allocator_sorted_list *>(allocator_parent->allocate(sizeof(allocator_sorted_list), 1));
    allocator::construct(allocator_child, 50, allocator_parent, logger_instance, allocator_with_fit_mode::fit_mode::first_fit);

    auto *block = reinterpret_cast<char *>(allocator_child->allocate(sizeof(char), 10));

    ASSERT_THROW(allocator_parent->deallocate(block), std::logic_error);

    allocator_child->deallocate(block);
    allocator::destruct(allocator_child);
    allocator_parent->deallocate(allocator_child);

    delete allocator_parent;
    delete logger_instance;
}

#include <sys/mman.h>
#include <forward_list>

int main(
        int argc,
        char *argv[])
{
//    testing::InitGoogleTest(&argc, argv);
//
//    return RUN_ALL_TESTS();

    std::forward_list<int> data = {6, 2, 3, 4, 5};
    auto pos = data.begin();
    data.pop_front();
    for (int elem : data) {
        std::cout << elem << " ";
    }
    std::cout << "\\n";
}