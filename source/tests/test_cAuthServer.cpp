///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cAuthServer.hpp"

// gTest grouping class
class test_cAuthServer : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cAuthServer : public cAuthServer
  {
  public:
    // add here members for free access.
    using cAuthServer::cAuthServer; // delegate constructors
  };

};
 
TEST_F(test_cAuthServer, test_ctor )
{
  // 1. Инициализация сервиса
  Test_cAuthServer auth("simple_secret_key", 3600);

  // 2. Создаем игру
  std::vector<std::string> users = { "user1", "user2" };
  std::string page_id = auth.createPage(users);
  EXPECT_EQ( page_id, "page_1" );

  // 3. Получаем токен для user1
  try {
    std::string token = auth.issueToken("user1", page_id);

    // 4. Проверяем токен
    EXPECT_TRUE(auth.validateToken(token, page_id)) << "Token is valid!" << std::endl;
  }
  catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  std::string token = auth.issueToken("user1", page_id);
  std::cout << "Token for user1: " << token << std::endl;

  // 4. Проверяем токен
  EXPECT_FALSE(auth.validateToken(token, "page_id99999"));
}

