///************************* OUTS HOMEWORK ****************************************
#ifndef CPAGEID_HPP
#define CPAGEID_HPP

#include <string>

class cPageId
{
public:
  cPageId() = default;
  cPageId(std::string id) : id(id) {}

public:
  std::string id;
};

#endif //#ifndef CPAGEID_HPP
