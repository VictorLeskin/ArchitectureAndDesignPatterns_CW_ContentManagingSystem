///************************* OUTS HOMEWORK ****************************************

#include "cJSONDataBase.hpp"

#include <filesystem>
#include <stdexcept>

namespace cms
{
  cJSONDataBase::cJSONDataBase(const std::string& file_path)
    : file_path_(file_path)
  {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!std::filesystem::exists(file_path_))
    {
      // Initialize empty database structure
      data_ =
      {
          {"users", json::array()},
          {"pages", json::array()}
      };
      saveToFile();
    }
    else
    {
      loadFromFile();
    }
  }

  void cJSONDataBase::loadFromFile()
  {
    std::ifstream file(file_path_);
    if (!file.is_open())
    {
      throw cDataBaseException("Failed to open database file");
    }

    try
    {
      file >> data_;
    }
    catch (const json::exception& e)
    {
      throw cDataBaseException(std::string("JSON parse error: ") + e.what());
    }
  }

  void cJSONDataBase::saveToFile()
  {
    std::ofstream file(file_path_);
    if (!file.is_open()) 
    {
      throw cDataBaseException("Failed to open database file for writing");
    }

    file << data_.dump(4);
  }

  // User operations
  std::vector<User> cJSONDataBase::getUsers()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try
    {
      return data_["users"].get<std::vector<User>>();
    }
    catch (const json::exception& e)
    {
      throw cDataBaseException(std::string("Failed to get users: ") + e.what());
    }
  }

  std::optional<User> cJSONDataBase::getUserById(int id)
  {
    auto users = getUsers();
    for (const auto& user : users) 
    {
      if (user.id == id) 
      {
        return user;
      }
    }
    return std::nullopt;
  }

  std::optional<User> cJSONDataBase::getUserByUsername(const std::string& username) 
  {
    auto users = getUsers();
    for (const auto& user : users) 
    {
      if (user.username == username) 
      {
        return user;
      }
    }
    return std::nullopt;
  }

  bool cJSONDataBase::addUser(const User& user) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto users = data_["users"].get<std::vector<User>>();

      // Check if user already exists
      for (const auto& u : users) 
      {
        if (u.id == user.id || u.username == user.username) 
        {
          return false;
        }
      }

      users.push_back(user);
      data_["users"] = users;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to add user: ") + e.what());
    }
  }

  // Page operations
  std::vector<Page> cJSONDataBase::getPages() 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      return data_["pages"].get<std::vector<Page>>();
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to get pages: ") + e.what());
    }
  }

  std::optional<Page> cJSONDataBase::getPageById(int id) 
  {
    auto pages = getPages();
    for (const auto& page : pages) 
    {
      if (page.id == id) 
      {
        return page;
      }
    }
    return std::nullopt;
  }

  bool cJSONDataBase::addPage(const Page& page) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto pages = data_["pages"].get<std::vector<Page>>();

      // Check if page already exists
      for (const auto& p : pages) 
      {
        if (p.id == page.id) 
        {
          return false;
        }
      }

      pages.push_back(page);
      data_["pages"] = pages;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to add page: ") + e.what());
    }
  }

  // Transaction support
  void cJSONDataBase::beginTransaction() 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (in_transaction_) 
    {
      throw cDataBaseException("Transaction already in progress");
    }
    transaction_data_ = data_;
    in_transaction_ = true;
  }

  void cJSONDataBase::commit() 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!in_transaction_) 
    {
      throw cDataBaseException("No transaction in progress");
    }
    saveToFile();
    in_transaction_ = false;
  }

  void cJSONDataBase::rollback() 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!in_transaction_) 
    {
      throw cDataBaseException("No transaction in progress");
    }
    data_ = transaction_data_;
    in_transaction_ = false;
  }

  bool cJSONDataBase::updateUser(const User& user) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto users = data_["users"].get<std::vector<User>>();
      bool found = false;

      for (auto& u : users) 
      {
        if (u.id == user.id) 
        {
          u = user;
          found = true;
          break;
        }
      }

      if (!found) 
      {
        return false;
      }

      data_["users"] = users;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to update user: ") + e.what());
    }
  }

  bool cJSONDataBase::deleteUser(int id) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto users = data_["users"].get<std::vector<User>>();
      bool found = false;

      users.erase(std::remove_if(users.begin(), users.end(),
        [id](const User& u) { return u.id == id; }),
        users.end());

      // Проверяем, был ли удален пользователь
      found = (users.size() != data_["users"].size());

      if (!found) 
      {
        return false;
      }

      data_["users"] = users;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to delete user: ") + e.what());
    }
  }

  bool cJSONDataBase::updatePage(const Page& page) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto pages = data_["pages"].get<std::vector<Page>>();
      bool found = false;

      for (auto& p : pages) 
      {
        if (p.id == page.id) 
        {
          p = page;
          found = true;
          break;
        }
      }

      if (!found) 
      {
        return false;
      }

      data_["pages"] = pages;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to update page: ") + e.what());
    }
  }

  bool cJSONDataBase::deletePage(int id) 
  {
    std::lock_guard<std::mutex> lock(mutex_);
    try 
    {
      auto pages = data_["pages"].get<std::vector<Page>>();
      bool found = false;

      pages.erase(std::remove_if(pages.begin(), pages.end(),
        [id](const Page& p) { return p.id == id; }),
        pages.end());

      // Проверяем, была ли удалена страница
      found = (pages.size() != data_["pages"].size());

      if (!found) 
      {
        return false;
      }

      data_["pages"] = pages;

      if (!in_transaction_) 
      {
        saveToFile();
      }
      return true;
    }
    catch (const json::exception& e) 
    {
      throw cDataBaseException(std::string("Failed to delete page: ") + e.what());
    }
  }

} // namespace cms


