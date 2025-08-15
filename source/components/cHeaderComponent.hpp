///************************* OUTS HOMEWORK ****************************************
#ifndef CHEADERCOMPONENT_HPP
#define CHEADERCOMPONENT_HPP

#include "iComponent.hpp"

class cHeaderComponent : public iComponent {
public:
  void initialize(const nlohmann::json& params) override;
  std::string render() const override;
  
  std::string getType() const override { return "header"; }

  static nlohmann::json getParametersSchema();

private:
  std::string text;
  int level;
  std::string alignment;
};

#endif //#ifndef CHEADERCOMPONENT_HPP
