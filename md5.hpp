#pragma once
#include <array>
#include <string>
#include <openssl/md5.h>

namespace sieve {
namespace hash {

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
    MD5(bytes, bytes_to_cal, result.data());
    return result;
}

auto md5(const std::string& str)
{
    std::array<unsigned char, MD5_DIGEST_LENGTH> result;
    MD5(reinterpret_cast<const unsigned  char*>(str.c_str()),str.size(),result.data());
    return result;
}

}
}
