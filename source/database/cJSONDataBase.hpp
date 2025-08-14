///************************* OUTS HOMEWORK ****************************************
#ifndef CJSONDATABASE_HPP
#define CJSONDATABASE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <mutex>

#include "cException.hpp"

using json = nlohmann::json;

namespace cms 
{
  // Структуры данных
  struct User 
  {
    int id;
    std::string username;
    std::string password_hash;
    std::string role;
    std::string email;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, id, username, password_hash, role, email)
  };

  struct Component 
  {
    std::string type;
    json parameters;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Component, type, parameters)
  };

  struct Page 
  {
    int id;
    std::string title;
    std::vector<Component> components;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Page, id, title, components)
  };

  class cDataBaseException : public cException
  {
  public:
    using cException::cException;
  };

  class cJSONDataBase
  {
  public:
    explicit cJSONDataBase(const std::string& file_path);

    // User operations
    std::vector<User> getUsers();
    std::optional<User> getUserById(int id);
    std::optional<User> getUserByUsername(const std::string& username);

    bool addUser(const User& user);
    bool updateUser(const User& user);
    bool deleteUser(int id);

    // Page operations
    std::vector<Page> getPages();
    std::optional<Page> getPageById(int id);

    bool addPage(const Page& page);
    bool updatePage(const Page& page);
    bool deletePage(int id);

    // Transaction support
    void beginTransaction();
    void commit();
    void rollback();

  protected:
    void loadFromFile();
    void saveToFile();

  protected:
    std::string file_path_;
    json data_;
    bool in_transaction_ = false;
    json transaction_data_;
    std::mutex mutex_;
  };

} // namespace cms

#endif //#ifndef CJSONDATABASE_HPP
