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
  {
      const char* szExampleJsonBase = R"({ "users": [], "pages": [] } )";
      std::ofstream strm("database.tmp1.json");
      strm << szExampleJsonBase << std::endl;
  }
  cms::cJSONDataBase db("database.tmp1.json");
  cIoC t0;
  cComponentRegistry registry("", t0);
  cAuthServer auth("",1);
  Test_cPageController t(db,auth,registry);
}

