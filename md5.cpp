#include <cstdio>
#include <openssl/md5.h>
#include "../base64/base64.hpp"
#include <memory>
#include <vector>
#include <array>
// #include <iomanip>
// #include <iostream>
// #include <sstream>
//
// int main(int argc,char** argv)
// {
//     unsigned char string[] = "Hello";
//     unsigned char dest[MD5_DIGEST_LENGTH];
//     MD5(string,sizeof(string)-1,dest);
//     
//     std::ostringstream sout;
// sout<<std::hex<<std::setfill('0');
// for(long long c: dest)
// {
//     sout<<std::setw(2)<<(long long)c;
// }
//     std::cout<<sout.str()<<std::endl;
//     return 0;
// }

#include "md5.hpp"
