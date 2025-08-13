///************************* OUTS HOMEWORK ****************************************
#ifndef CAUTHSERVER_HPP
#define CAUTHSERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>
#include "cListOfUsers.hpp"
#include "cRequestAccessToPage.hpp"

struct PageInfo {
  std::string page_id;
  std::vector<std::string> participants;
  std::time_t creation_time;
};

struct AuthConfig {
  std::string secret_key;
  int token_expiration_sec;
};

class cAuthServer {
public:
  cAuthServer(const std::string& secret, int token_expiry)
    : secret_key(secret), token_expiry_seconds(token_expiry) {}

  std::string createPage(const cListOfUsers& participantsList);
  bool checkPlayer(const std::string& pageId, const std::string& playerName);

  std::string issueToken(const cRequestAccessToPage& req);
  

  std::string createPage(const std::vector<std::string>& players);
  std::string issueToken(const std::string& user_id, const std::string& page_id);
  bool validateToken(const std::string& token, const std::string& page_id);

private:
  int counter = 0;

  std::string secret_key;
  int token_expiry_seconds;
  std::map<std::string, std::vector<std::string>> users;

  std::string generateSimpleId();
};

#endif //#ifndef CAUTHSERVER_HPP
