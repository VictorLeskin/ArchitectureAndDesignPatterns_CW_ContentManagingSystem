///************************* OUTS HOMEWORK ****************************************
#ifndef CTEXTCOMPONENT_HPP
#define CTEXTCOMPONENT_HPP

#include "iComponent.hpp"

class cTextComponent : public iComponent 
{
public:
  void initialize(const nlohmann::json& params) override;
  std::string render() const override;
  std::string getType() const override { return "text"; }

  static nlohmann::json getParametersSchema();

protected:
  std::string content;
  std::string color;
  int fontSize;
};
#endif //#ifndef CTEXTCOMPONENT_HPP
