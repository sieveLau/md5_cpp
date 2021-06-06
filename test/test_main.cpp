#include <gtest/gtest.h>
#include "../md5.hpp"
#include "../external/base64/base64.hpp"
#include "../external/util/util.hpp"

TEST(MD5, Hex_Equal)
{
    std::string str("Hello");
    auto md5d = sieve::hash::md5(str);
    // generate by bash: $ printf '%s' "Hello" | md5sum
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"), sieve::util::to_hex(md5d));
}

TEST(MD5, Base64encode_Equal)
{
    std::string str("Hello");
    auto md5 = sieve::hash::md5(str);
    auto b64str = sieve::base64::b64encode(md5);
    /*
     * generate by python:

from hashlib import md5
from base64 import b64encode
md5 = md5()
md5.update(b'Hello')
b64encode(md5.digest())

     */
    EXPECT_EQ(b64str, std::string("ixqZU8RhEpaoJ6v4xHgE1w=="));
}

TEST(MD5, RawArrayTemplateWithoutTerminator_Equal)
{
    unsigned char origin[] = "Hello";
    auto md5 = sieve::hash::md5(origin);
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"), sieve::util::to_hex(md5));
}

TEST(MD5, RawArrayTemplateWithTerminator_Equal)
{
    unsigned char origin[] = "Hello";
    auto md5 = sieve::hash::md5(origin, true);
    /*
     * generate by python:

from hashlib import md5
from base64 import b64encode
md5 = md5()
md5.update(b'Hello\0')
b64encode(md5.hexdigest())

     */
    EXPECT_EQ(std::string("9392c196504ae11ac127a595326ddf96"), sieve::util::to_hex(md5));
}

TEST(MD5, RawArray_Equal)
{
    unsigned char *origin = new unsigned char[]{"Hello"};
    const size_t full_size = 6;
    auto md5 = sieve::hash::md5(origin, 5);
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"), sieve::util::to_hex(md5));
}

TEST(MD5Class, digest_Equal)
{
    std::string str("Hello");
    auto md5 = sieve::hash::md5(str);
    sieve::hash::MD5 md5c;
    md5c.update(str);
    auto classmd5 = md5c.digest();
    EXPECT_TRUE(0==std::memcmp(md5.data(),classmd5.data(),md5.size()));
}

TEST(MD5Class, hexdigest_Equal)
{
    std::string str("Hello");
    sieve::hash::MD5 md5c;
    md5c.update(str);
    auto classmd5 = md5c.hexdigest();
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"), classmd5);
}

TEST(MD5Class, copy_Equal)
{
    std::string str("Hello");
    sieve::hash::MD5 md5c;
    md5c.update(str);
    sieve::hash::MD5 md5c_copy(md5c);
    auto copyed_md5_hex = md5c_copy.hexdigest();
    EXPECT_EQ(std::string("8b1a9953c4611296a827abf8c47804d7"), copyed_md5_hex);
}
