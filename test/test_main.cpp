#include <gtest/gtest.h>
#include "../md5.hpp"
#include "../external/base64/base64.hpp"
#include "../external/util/util.hpp"

TEST(TESTMD5,HEXEQUAL)
{
   std::string str("Hello");
    auto md5d = sieve::hash::md5(str);
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"),sieve::util::to_hex(md5d).c_str());
   // printf("%s\n", sieve::util::to_hex(md5d).c_str());
}