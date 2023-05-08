#include "libs21.h"

namespace s21 {
std::string to_lower(std::string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
}  // namespace s21