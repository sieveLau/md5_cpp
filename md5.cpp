#include "MD5.hpp"

namespace sieve {
namespace hash {
std::array<unsigned char, 16> hash::md5(const unsigned char *bytes,
                                        const size_t bytes_to_cal)
{
    std::array<unsigned char, MD5_DIGEST_LENGTH> result;
    EVP_Digest(bytes, bytes_to_cal, result.data(),NULL, EVP_md5(),NULL);
    // MD5(bytes, bytes_to_cal, result.data());
    return result;
}

std::array<unsigned char, 16> hash::md5(const std::string &str)
{
    return md5(reinterpret_cast<const unsigned char *>(str.c_str()), str.size());
}

void MD5::dirty_reset() noexcept
{
    buffer_ = nullptr;
    finish_ = true;
}

MD5::MD5()
    : buffer_(EVP_MD_CTX_new()), finish_(false)
{
    EVP_DigestInit_ex(buffer_, EVP_md5(), nullptr);
}

MD5::MD5(MD5 &&another) noexcept
    : MD5()
{
    swap(*this,another);
}

MD5 & MD5::operator=(MD5 another)
{
    swap(*this,another);
    return *this;
}

void MD5::update(const std::string &data)
{
    EVP_DigestUpdate(buffer_, data.c_str(), data.size());
}

void MD5::update(const unsigned char * bytes, const size_t bytes_to_cal)
{
    EVP_DigestUpdate(buffer_,bytes,bytes_to_cal);
}


std::array<unsigned char, MD5_DIGEST_LENGTH> MD5::digest()
{
    std::array<unsigned char, digest_size> result;
    EVP_MD_CTX *temp_copy=EVP_MD_CTX_new();
    EVP_MD_CTX_copy(temp_copy, buffer_);
    EVP_DigestFinal(temp_copy, result.data(), nullptr);
    return result;
}

std::string MD5::hexdigest()
{
    auto temp = digest();
    return util::to_hex(temp);
}

MD5::~MD5()
{
    EVP_MD_CTX_free(buffer_);
    finish_ = true;
}

MD5::MD5(const MD5 &another):buffer_(nullptr),finish_(another.finish_)
{
    buffer_=EVP_MD_CTX_new();
    EVP_MD_CTX_copy_ex(buffer_,another.buffer_);
}


}
}
