find_package(OpenSSL REQUIRED)

add_executable(main md5.cpp)

target_link_libraries(main base64 OpenSSL::Crypto)