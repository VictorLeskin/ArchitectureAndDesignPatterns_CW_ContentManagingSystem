///************************* OUTS HOMEWORK ****************************************
#ifndef CCOMPONENTREGISTRY_HPP
#define CCOMPONENTREGISTRY_HPP

#include <memory>
#include <string>

#include "iComponent.hpp"

class cIoC;


class cComponentRegistry 
{
public:
    explicit cComponentRegistry(const std::string &scope, cIoC& container) : scope_(scope), container_(container) {}

    std::unique_ptr<iComponent> createComponent(const std::string& type);
    
protected:
    std::string scope_;
    cIoC& container_;
};

#endif //#ifndef CCOMPONENTREGISTRY_HPP
