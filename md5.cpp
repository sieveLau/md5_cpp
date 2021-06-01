#include <cstdio>
#include <openssl/md5.h>
#include "../base64/base64.hpp"
#include <memory>
#include <vector>
#include <array>

int main(int argc,char** argv)
{
    unsigned char string[] = "a string";
    unsigned char dest[MD5_DIGEST_LENGTH];
    MD5(string,sizeof(string),dest);
    
    printf("%s\n",sieve::base64::b64encode(dest).c_str());
    return 0;
}
