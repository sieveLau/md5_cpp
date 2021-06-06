#pragma once
#include "external/util/util.hpp"
#include <array>
#include <openssl/evp.h>

namespace sieve {
namespace hash {
const int MD5_DIGEST_LENGTH = 16;

/// calculate the md5sum of a byte array
/// array size auto deduce
template <int N>
auto md5(const unsigned char (&bytes)[N],
         bool include_string_terminator = false) {
  std::array<unsigned char, MD5_DIGEST_LENGTH> result;
  unsigned long bytes_to_cal = N;
  if (!include_string_terminator && bytes[N - 1] == (unsigned char)'\0') {
    --bytes_to_cal;
  }
  EVP_Digest(bytes, bytes_to_cal, result.data(), NULL, EVP_md5(), NULL);
  return result;
}

// calculate the md5sum of byte array.
// 2nd param indicates the number of bytes to read
std::array<unsigned char, MD5_DIGEST_LENGTH> md5(const unsigned char *bytes,
                                                 size_t bytes_to_cal);

// calculate the md5sum of std::string.
std::array<unsigned char, MD5_DIGEST_LENGTH> md5(const std::string &str);

class MD5 {
  EVP_MD_CTX *buffer_;
  bool finish_;
  void dirty_reset() noexcept;

public:
  const static size_t digest_size = MD5_DIGEST_LENGTH;

  explicit MD5();

  friend void swap(MD5 &left, MD5 &right) {
    using std::swap;
    swap(left.buffer_, right.buffer_);
    swap(left.finish_, right.finish_);
  }

  MD5(const MD5 &);
  MD5(MD5 &&) noexcept;
  MD5 &operator=(MD5);

  void update(const std::string &);
  void update(const unsigned char *, size_t);

  template <size_t SIZE> void update(std::array<unsigned char, SIZE> bytes) {
    EVP_DigestUpdate(buffer_, bytes.data(), SIZE);
  }

  std::array<unsigned char, MD5_DIGEST_LENGTH> digest();
  std::string hexdigest();

  ~MD5();
};

} // namespace hash
} // namespace sieve
