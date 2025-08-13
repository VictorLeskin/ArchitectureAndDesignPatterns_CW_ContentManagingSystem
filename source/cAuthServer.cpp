///************************* OUTS HOMEWORK ****************************************

#include "cAuthServer.hpp"

#include <random>
#include <algorithm>

std::string cAuthServer::createPage(const cListOfUsers& participantsList)
{
  std::vector<std::string> players;
  return createPage(participantsList.Users());
}

std::string cAuthServer::createPage(const std::vector<std::string>& players) {
  std::string id = generateSimpleId();
  users[id] = players;
  return id;
}

bool cAuthServer::checkPlayer(const std::string& pageId, const std::string& playerName)
{
  if (users.find(pageId) == users.end())
    return false;
  const std::vector<std::string>& players = users[pageId];
  return std::find(  players.begin(), players.end(), playerName) != players.end();
}

std::string cAuthServer::issueToken(const std::string& user_id, const std::string& page_id) {
  if (users.find(page_id) == users.end()) {
    throw std::runtime_error("Page not found");
  }

  auto& players = users[page_id];
  if (std::find(players.begin(), players.end(), user_id) == players.end()) {
    throw std::runtime_error("User not in page");
  }

  return jwt::create()
    .set_payload_claim("user_id", jwt::claim(user_id))
    .set_payload_claim("page_id", jwt::claim(page_id))
    .sign(jwt::algorithm::hs256{ secret_key });
}

std::string cAuthServer::issueToken(const cRequestAccessToPage& req)
{
  return issueToken(req.user.Name(), req.pageId.id);
}

bool cAuthServer::validateToken(const std::string& token, const std::string& page_id) {
  try {
    auto decoded = jwt::decode(token);
    jwt::verify()
      .allow_algorithm(jwt::algorithm::hs256{ secret_key })
      .verify(decoded);

    return decoded.get_payload_claim("page_id").as_string() == page_id;
  }
  catch (...) {
    return false;
  }
}

std::string cAuthServer::generateSimpleId() {
  return "page_" + std::to_string(++counter);
}