#pragma once
#include <array>
#include <openssl/evp.h>
#include "external/util/util.hpp"

namespace sieve {
namespace hash {
const int MD5_DIGEST_LENGTH = 16;
/**
 * \brief calculate the md5 of the parameter.
 * \param bytes content to calculate md5
 * \param include_string_terminator If true, treat '\0' as part of the input. Default false.
 * \return a unsigned char std::array containing the digest
 */
template<int N>
auto md5(const unsigned char (&bytes)[N], bool include_string_terminator = false)
{
    std::array<unsigned char, MD5_DIGEST_LENGTH> result;
    unsigned long bytes_to_cal = N;
    if (!include_string_terminator && bytes[N - 1] == (unsigned char) '\0') {
        --bytes_to_cal;
    }
    EVP_Digest(bytes, bytes_to_cal, result.data(),NULL, EVP_md5(),NULL);
    return result;
}


std::array<unsigned char, MD5_DIGEST_LENGTH> md5(const unsigned char *bytes, size_t bytes_to_cal);

std::array<unsigned char, MD5_DIGEST_LENGTH> md5(const std::string &str);

class MD5
{
    EVP_MD_CTX *buffer_;
    bool finish_;
    void dirty_reset() noexcept;
public:
    const static size_t digest_size = MD5_DIGEST_LENGTH;

    explicit MD5();

    friend void swap(MD5 &left, MD5 &right)
    {
        using std::swap;
        swap(left.buffer_, right.buffer_);
        swap(left.finish_, right.finish_);
    }

    MD5(const MD5 &);
    MD5(MD5 &&) noexcept;
    MD5 &operator=(MD5);

    void update(const std::string &);
    void update(const unsigned char *, size_t);

    template<size_t SIZE>
    void update(std::array<unsigned char, SIZE> bytes)
    {
        EVP_DigestUpdate(buffer_, bytes.data(), SIZE);
    }

    std::array<unsigned char, MD5_DIGEST_LENGTH> digest();
    std::string hexdigest();

    ~MD5();
};

}
}
