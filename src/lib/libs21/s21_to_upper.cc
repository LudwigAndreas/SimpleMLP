
namespace s21 {
    std::string to_upper_case(std::string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
}