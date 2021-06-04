enable_testing()
#find_package(GTest CONFIG REQUIRED)
add_executable(testmd5cpp test_main.cpp)
target_link_libraries(
  testmd5cpp
  PRIVATE
  gtest_main
  md5cpp
)
include(GoogleTest)
gtest_discover_tests(testmd5cpp)