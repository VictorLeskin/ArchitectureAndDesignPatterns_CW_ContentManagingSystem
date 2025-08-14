///************************* OUTS HOMEWORK ****************************************
#ifndef CEXCEPTION_HPP
#define CEXCEPTION_HPP

#include <stdexcept>
#include <string>

// base class of exception used in task. Just keep a text of a event.
class cException : public std::exception
{
public:
    cException(const char* sz) : szWhat(sz) {}
    cException(const std::string &str) : szWhat(str) {}

    const char* what() const noexcept { return szWhat.c_str(); }
    const std::string &What() const noexcept { return szWhat; }

protected:
  std::string szWhat;
};


#endif //#ifndef CEXCEPTION_HPP
