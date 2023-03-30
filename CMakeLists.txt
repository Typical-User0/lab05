cmake_minimum_required(VERSION 3.4)
project(lab)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gtest" "gtest")

find_package(Threads)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/banking)

if(COVERAGE)
  add_executable(account_test tests/test_account.cpp)
  add_executable(transaction_test tests/test_transaction.cpp)

  target_compile_options(account_test PRIVATE --coverage)
  target_compile_options(transaction_test PRIVATE --coverage)

  target_include_directories(account_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)
  target_include_directories(transaction_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)

  target_link_libraries(transaction_test PRIVATE gtest ${CMAKE_THREAD_LIBS_INIT} gtest_main gmock_main banking --coverage)
  target_link_libraries(account_test PRIVATE gtest ${CMAKE_THREAD_LIBS_INIT} gtest_main gmock_main banking --coverage)
endif()
