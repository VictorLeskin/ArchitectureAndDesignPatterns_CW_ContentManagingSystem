///************************* OUTS HOMEWORK ****************************************
#ifndef CIMAGECOMPONENT_HPP
#define CIMAGECOMPONENT_HPP

#include "iComponent.hpp"

class cImageComponent : public iComponent {
public:
  void initialize(const nlohmann::json& params) override;
  std::string render() const override;
  std::string getType() const override { return "image"; }

  static nlohmann::json getParametersSchema();

private:
  std::string src;
  std::string altText;
  int width;
  int height;
};
#endif //#ifndef CIMAGECOMPONENT_HPP
