#include <aw/utils/math/matrix.hpp>

#include <iomanip>

namespace aw
{

std::ostream& operator<<(std::ostream& stream, const Mat2& matrix)
{
  stream << "Mat2(";
  for (int i = 0; i < 2; i++)
  {
    stream << "\n\t[";
    for (int j = 0; j < 2; j++)
    {
      stream << std::setw(11) << matrix[j][i];
      if (j != 1)
        stream << " ,";
    }
    stream << "]";
  }
  stream << "\n)";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Mat3& matrix)
{
  stream << "Mat3(";
  for (int i = 0; i < 3; i++)
  {
    stream << "\n\t[";
    for (int j = 0; j < 3; j++)
    {
      stream << std::setw(11) << matrix[j][i];
      if (j != 2)
        stream << " ,";
    }
    stream << "]";
  }
  stream << "\n)";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Mat4& matrix)
{
  stream << "Mat4(";
  for (int i = 0; i < 4; i++)
  {
    stream << "\n\t[";
    for (int j = 0; j < 4; j++)
    {
      stream << std::setw(11) << matrix[j][i];
      if (j != 3)
        stream << " ,";
    }
    stream << "]";
  }
  stream << "\n)";
  return stream;
}
} // namespace aw
