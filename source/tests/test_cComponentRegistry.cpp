///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cComponentRegistry.hpp"
#include "cIoC.hpp"

// gTest grouping class
class test_cComponentRegistry : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cComponentRegistry : public cComponentRegistry
  {
  public:
    // add here members for free access.
    using cComponentRegistry::cComponentRegistry; // delegate constructors
  };

};
 
TEST_F(test_cComponentRegistry, test_ctor )
{
  cIoC t0;
  Test_cComponentRegistry t("",t0);
}

