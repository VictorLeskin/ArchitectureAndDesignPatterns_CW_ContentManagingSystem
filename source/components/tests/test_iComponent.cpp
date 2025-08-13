///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "iComponent.hpp"

// gTest grouping class
class test_iComponent : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_iComponent : public iComponent
  {
  public:
    // add here members for free access.
    using iComponent::iComponent; // delegate constructors

    void initialize(const nlohmann::json& params) override {}
    std::string render() const override { return ""; }
    std::string getType() const override { return ""; }
  };

};
 
TEST_F(test_iComponent, test_ctor )
{
  Test_iComponent t;
}

