#ifndef SIMPLEMLP_UPLOADFILEEXCEPTION_H
#define SIMPLEMLP_UPLOADFILEEXCEPTION_H


class UploadFileException: public std::exception{
public:
    explicit UploadFileException(const char* message)
            : msg_(message) {}

    explicit UploadFileException(std::string& message)
    : msg_(message) {}

    UploadFileException() {}

    virtual ~UploadFileException() noexcept {}

    virtual const char* what() const noexcept {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};


#endif //SIMPLEMLP_UPLOADFILEEXCEPTION_H
