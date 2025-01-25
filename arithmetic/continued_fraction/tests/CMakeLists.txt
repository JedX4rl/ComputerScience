cmake_minimum_required(VERSION 3.21)
project(cont_fraction)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

# For Windows users: prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(
        googletest)

add_executable(
        cont_fraction
        continued_fraction_test.cpp)
target_link_libraries(
        cont_fraction
        PUBLIC
        mp_os_cmmn)
target_link_libraries(
        cont_fraction
        PUBLIC
        mp_os_lggr_clnt_lggr)
target_link_libraries(
        cont_fraction
        PUBLIC
        mp_os_arthmtc_cntnd_frctn)
set_target_properties(
        cont_fraction PROPERTIES
        LANGUAGES CXX
        LINKER_LANGUAGE CXX
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VERSION 1.0
        DESCRIPTION "bigint implementation library tests")