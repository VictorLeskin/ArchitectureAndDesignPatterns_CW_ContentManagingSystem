///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cPageController.hpp"
#include "cIoC.hpp"

// gTest grouping class
class test_cPageController : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cPageController : public cPageController
  {
  public:
    // add here members for free access.
    using cPageController::cPageController; // delegate constructors
  };

};
 
TEST_F(test_cPageController, test_ctor )
{
  cIoC t0;
  cComponentRegistry registry("", t0);
  cAuthServer auth("",1);
  Test_cPageController t(registry,auth);
}

