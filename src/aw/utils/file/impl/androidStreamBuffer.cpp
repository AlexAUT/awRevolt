#include <aw/utils/impl/androidStreamBuffer.hpp>

#include <iostream>

#include <android/log.h>

namespace aw
{
AndroidStreamBuffer::AndroidStreamBuffer()
{
  setp(buffer, buffer + BUFFER_SIZE - 1);
}

int AndroidStreamBuffer::overflow(int c)
{
  if (c == traits_type::eof())
  {
    *this->pptr() = traits_type::to_char_type(c);
    this->sbumpc();
  }
  return this->sync() ? traits_type::eof() : traits_type::not_eof(c);
}

int AndroidStreamBuffer::sync()
{
  int rc = 0;
  if (this->pbase() != this->pptr())
  {
    __android_log_print(ANDROID_LOG_INFO, "aw", "%s", std::string(this->pbase(), this->pptr() - this->pbase()).c_str());
    rc = 0;
    this->setp(buffer, buffer + BUFFER_SIZE - 1);
  }
  return rc;
}
} // namespace aw
