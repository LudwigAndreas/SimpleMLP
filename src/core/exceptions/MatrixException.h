#ifndef SIMPLEMLP_MATRIXEXCEPTION_H
#define SIMPLEMLP_MATRIXEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

class MatrixException : public std::exception {
public:
  explicit MatrixException(const char *message) : msg_(message) {}

  explicit MatrixException(std::string &message) : msg_(message) {}

  MatrixException() {}

  virtual ~MatrixException() noexcept {}

  virtual const char *what() const noexcept { return msg_.c_str(); }

protected:
  std::string msg_;
};

class MatrixCalculationsException : public MatrixException {
public:
  explicit MatrixCalculationsException(const char *message) : msg_(message) {}

  explicit MatrixCalculationsException(std::string &message) : msg_(message) {}

  virtual ~MatrixCalculationsException() noexcept {}

  virtual const char *what() const noexcept { return msg_.c_str(); }

protected:
  std::string msg_;
};

#endif // SIMPLEMLP_MATRIXEXCEPTION_H
