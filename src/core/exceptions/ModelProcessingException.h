#ifndef SIMPLEMLP_MODELPROCESSINGEXCEPTION_H
#define SIMPLEMLP_MODELPROCESSINGEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

class ModelProcessingException : public std::exception {
public:
  explicit ModelProcessingException(const char *message) : msg_(message) {}

  explicit ModelProcessingException(std::string &message) : msg_(message) {}

  ModelProcessingException() {}

  virtual ~ModelProcessingException() noexcept {}

  virtual const char *what() const noexcept { return msg_.c_str(); }

protected:
  std::string msg_;
};

#endif // SIMPLEMLP_MODELPROCESSINGEXCEPTION_H
