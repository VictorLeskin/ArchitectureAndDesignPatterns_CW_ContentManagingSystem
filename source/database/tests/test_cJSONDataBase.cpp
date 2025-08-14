///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cJSONDataBase.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

// gTest grouping class
class Test_cJSONDataBase : public ::testing::Test 
{
protected:
  const std::string test_db_path = "test_db.json";

  void SetUp() override 
  {
    // ������� �������� ��, ���� ��� ����������
    if (fs::exists(test_db_path)) 
    {
      fs::remove(test_db_path);
    }
  }

  void TearDown() override {
    // ������� �������� �� ����� ���������� ������
    if (fs::exists(test_db_path)) {
      fs::remove(test_db_path);
    }
  }

  void createTestDatabase() {
    nlohmann::json initial_data = {
        {"users", {
            {
                {"id", 1},
                {"username", "admin"},
                {"password_hash", "hash1"},
                {"role", "admin"},
                {"email", "admin@test.com"}
            },
            {
                {"id", 2},
                {"username", "editor"},
                {"password_hash", "hash2"},
                {"role", "editor"},
                {"email", "editor@test.com"}
            }
        }},
        {"pages", {
            {
                {"id", 1},
                {"title", "Home Page"},
                {"components", {
                    {
                        {"type", "header"},
                        {"parameters", {
                            {"text", "Welcome"},
                            {"level", 1}
                        }}
                    }
                }}
            }
        }}
    };

    std::ofstream file(test_db_path);
    file << initial_data.dump(4);
  }
};

TEST_F(Test_cJSONDataBase, test_CreatesNewDatabaseIfNotExists) 
{
  ASSERT_FALSE(fs::exists(test_db_path));

  cms::cJSONDataBase db(test_db_path);
  ASSERT_TRUE(fs::exists(test_db_path));

  // ��������� ��������� ����� ��
  std::ifstream file(test_db_path);
  nlohmann::json data;
  file >> data;

  EXPECT_TRUE(data.contains("users"));
  EXPECT_TRUE(data["users"].is_array());
  EXPECT_TRUE(data.contains("pages"));
  EXPECT_TRUE(data["pages"].is_array());
}

TEST_F(Test_cJSONDataBase, test_LoadsExistingDatabase) {
  createTestDatabase();

  cms::cJSONDataBase db(test_db_path);
  auto users = db.getUsers();
  auto pages = db.getPages();

  EXPECT_EQ(users.size(), 2);
  EXPECT_EQ(pages.size(), 1);
}

TEST_F(Test_cJSONDataBase, test_UserOperations) {
  createTestDatabase();
  cms::cJSONDataBase db(test_db_path);

  // �������� ��������� �������������
  auto users = db.getUsers();
  ASSERT_EQ(users.size(), 2);

  // �������� ������ ������������ �� ID
  auto user1 = db.getUserById(1);
  ASSERT_TRUE(user1.has_value());
  EXPECT_EQ(user1->username, "admin");

  // �������� ������ ������������ �� �����
  auto user2 = db.getUserByUsername("editor");
  ASSERT_TRUE(user2.has_value());
  EXPECT_EQ(user2->id, 2);

  // �������� ���������� ������������
  cms::User new_user{
      3,
      "new_user",
      "hash3",
      "reader",
      "new@test.com"
  };

  EXPECT_TRUE(db.addUser(new_user));
  EXPECT_EQ(db.getUsers().size(), 3);

  // �������� ������������ ������������
  EXPECT_FALSE(db.addUser(new_user));

  // �������� ���������� ������������
  new_user.email = "updated@test.com";
  EXPECT_TRUE(db.updateUser(new_user));
  auto updated_user = db.getUserById(3);
  ASSERT_TRUE(updated_user.has_value());
  EXPECT_EQ(updated_user->email, "updated@test.com");

  // �������� �������� ������������
  EXPECT_TRUE(db.deleteUser(3));
  EXPECT_EQ(db.getUsers().size(), 2);
}

TEST_F(Test_cJSONDataBase, test_PageOperations) {
  createTestDatabase();
  cms::cJSONDataBase db(test_db_path);

  // �������� ��������� �������
  auto pages = db.getPages();
  ASSERT_EQ(pages.size(), 1);

  // �������� ������ �������� �� ID
  auto page1 = db.getPageById(1);
  ASSERT_TRUE(page1.has_value());
  EXPECT_EQ(page1->title, "Home Page");

  // �������� ���������� ��������
  cms::Page new_page{
      2,
      "New Page",
      {
          {
              "text",
              {
                  {"content", "Sample text"}
              }
          }
      }
  };

  EXPECT_TRUE(db.addPage(new_page));
  EXPECT_EQ(db.getPages().size(), 2);

  // �������� ������������ ��������
  EXPECT_FALSE(db.addPage(new_page));

  // �������� ���������� ��������
  new_page.title = "Updated Page";
  EXPECT_TRUE(db.updatePage(new_page));
  auto updated_page = db.getPageById(2);
  ASSERT_TRUE(updated_page.has_value());
  EXPECT_EQ(updated_page->title, "Updated Page");

  // �������� �������� ��������
  EXPECT_TRUE(db.deletePage(2));
  EXPECT_EQ(db.getPages().size(), 1);
}

TEST_F(Test_cJSONDataBase, test_Transactions) {
  createTestDatabase();
  cms::cJSONDataBase db(test_db_path);

  // �������� ����������
  db.beginTransaction();

  // ��������� ������������ � ����������
  cms::User new_user{
      3,
      "temp_user",
      "hash3",
      "reader",
      "temp@test.com"
  };
  EXPECT_TRUE(db.addUser(new_user));

  // ���������, ��� ��������� �� ��������� �� ����
  {
    cms::cJSONDataBase db2(test_db_path);
    EXPECT_EQ(db2.getUsers().size(), 2);
  }

  // ���������� ����������
  db.rollback();

  // ���������, ��� ��������� ����������
  EXPECT_EQ(db.getUsers().size(), 2);

  // ����� ���������� � ��������
  db.beginTransaction();
  EXPECT_TRUE(db.addUser(new_user));
  db.commit();

  // ���������, ��� ��������� ���������
  EXPECT_EQ(db.getUsers().size(), 3);
  {
    cms::cJSONDataBase db2(test_db_path);
    EXPECT_EQ(db2.getUsers().size(), 3);
  }
}

TEST_F(Test_cJSONDataBase, test_ErrorHandling) {
  // �������� ������ � �������������� ������
  EXPECT_NO_THROW(cms::cJSONDataBase db("nonexistent.json"));

  // �������� ������ � ������������ JSON
  {
    std::ofstream bad_file("bad_db.json");
    bad_file << "{ invalid json }";
    bad_file.close();

    EXPECT_THROW(cms::cJSONDataBase db("bad_db.json"), cms::cDataBaseException);
    fs::remove("bad_db.json");
  }

  // �������� ��������� ������������ ID
  createTestDatabase();
  cms::cJSONDataBase db(test_db_path);

  cms::User duplicate_id_user{
      1,  // ������������ ID
      "new_user",
      "hash",
      "role",
      "email@test.com"
  };

  EXPECT_FALSE(db.addUser(duplicate_id_user));
}

