#include "libs21.h"

namespace s21 {
std::string to_upper(std::string str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}
} // namespace s21