cmake_minimum_required(VERSION 3.16)

if(TARGET md5cpp)
  return()
endif(TARGET md5cpp)


project(md5cpp)

set(CXX_STANDARD 17)

add_subdirectory(external/base64)
add_subdirectory(external/util)

find_package(OpenSSL REQUIRED)

add_library(md5cpp STATIC md5.cpp md5.hpp)

target_link_libraries(md5cpp base64 util OpenSSL::Crypto)

# add googletest https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)