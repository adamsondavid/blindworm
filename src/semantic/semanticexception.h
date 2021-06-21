#ifndef BLINDWORM_COMPILER_SEMANTICEXCEPTION_H
#define BLINDWORM_COMPILER_SEMANTICEXCEPTION_H

#include <exception>

class SemanticException : public std::exception {
private:
    const std::string msg;
public:
    SemanticException(std::string msg): msg(msg) { }
    const char* what () const throw () {
        return this->msg.c_str();
    }
};

#endif //BLINDWORM_COMPILER_SEMANTICEXCEPTION_H
