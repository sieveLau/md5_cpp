#include "md5.hpp"

std::array<unsigned char, 16> sieve::hash::md5(const unsigned char *bytes, const size_t bytes_to_cal)
{
    std::array<unsigned char, MD5_DIGEST_LENGTH> result;
    MD5(bytes, bytes_to_cal, result.data());
    return result;
}

std::array<unsigned char, 16> sieve::hash::md5(const std::string &str)
{
    std::array<unsigned char, MD5_DIGEST_LENGTH> result;
    MD5(reinterpret_cast<const unsigned char *>(str.c_str()), str.size(), result.data());
    return result;
}
