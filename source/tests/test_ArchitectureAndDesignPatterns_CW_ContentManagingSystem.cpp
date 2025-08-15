///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cJSONDataBase.hpp"
#include "cAuthServer.hpp"
#include "cComponentRegistry.hpp"
#include "cPageController.hpp"
#include "cIoC.hpp"

#include "cHeaderComponent.hpp"
#include "cTextComponent.hpp"
#include "cImageComponent.hpp"

#include "ArchitectureAndDesignPatterns_CW_ContentManagingSystem.hpp"

#include <fstream>

// gTest grouping class
class test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem : public ::testing::Test
{
public:
    // additional class to access to member of tested class
    class Test_cFactory : public cFactory
    {
    public:
        // add here members for free access.
        using cFactory::cFactory; // delegate constructors
        using cFactory::factoryMethods;

        static Test_cFactory* Clone(const Test_cFactory&) { return nullptr; }

        static cHeaderComponent* getHeaderComponent() { return new cHeaderComponent; }
        static cTextComponent* getTextComponent() { return new cTextComponent; }
        static cImageComponent* getImageComponent() { return new cImageComponent; }
    };

  // additional class to access to member of tested class
  class Test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem : public ArchitectureAndDesignPatterns_CW_ContentManagingSystem
  {
  public:
    // add here members for free access.
    using ArchitectureAndDesignPatterns_CW_ContentManagingSystem::ArchitectureAndDesignPatterns_CW_ContentManagingSystem; // delegate constructors
  };
};

TEST_F(test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem, test_ctor )
{
  Test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem t;
  t;
}

extern const char* szExampleJsonBase;

TEST_F(test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem, test_simpleTestAndImage_A )
{
    {
        // open tmp file and write test JSON to it

        std::ofstream strm("database.tmp.json");
        strm << szExampleJsonBase << std::endl;
    }

    cms::cJSONDataBase db("database.tmp.json");

    {
        std::vector<cms::User> t1 = db.getUsers();
        std::vector<cms::Page> p1 = db.getPages();

        EXPECT_TRUE(0 != t1.size());
        EXPECT_TRUE(0 != p1.size());
    }

    std::vector<cms::Page> p1 = db.getPages();

    cAuthServer authServer("", 1);

    cUser organizer("Organizer");
    cUser participant1("Participant #1");
    cUser participant2("Participant #2");

    cListOfUsers participantsList = { organizer, participant1, participant2 };

    cPageId pageId = authServer.createPage(p1[0].id, participantsList);

    cRequestAccessToPage reqAccessToPageOrganizer(organizer, pageId);
    cRequestAccessToPage reqAccessToPageParticipant1(participant1, pageId);
    cRequestAccessToPage reqAccessToPageParticipant2(participant2, pageId);

    EXPECT_TRUE(authServer.getAccessToPage(reqAccessToPageOrganizer) );
    EXPECT_TRUE(authServer.getAccessToPage(reqAccessToPageParticipant1));
    EXPECT_TRUE(authServer.getAccessToPage(reqAccessToPageParticipant2));

    const std::string scope("TestA");
    // Инициализация
    Test_cFactory f1;
    cIoC t0;
    f1.Register(std::string("header"), Test_cFactory::getHeaderComponent);
    f1.Register(std::string("text"), Test_cFactory::getTextComponent);
    f1.Register(std::string("image"), Test_cFactory::getImageComponent);
    t0.Resolve<iCommand>("Register", scope, (const cFactory&)f1)->Execute();

    cComponentRegistry registry(scope, t0);
    cPageController controller(db, authServer, registry);

    // Генерация страницы для пользователя organizer
    auto response = controller.renderPage(reqAccessToPageOrganizer);

    EXPECT_FALSE(response.access_denied);
    if (response.access_denied)
    {
        std::cerr << "Access denied!" << std::endl;
    }
    else
    {
        // Сохраняем в HTML файл
        std::ofstream out("output.html");
        out << "<!DOCTYPE html>\n"
            << "<html>\n"
            << "<head>\n"
            << "  <title>CMS Generated Page</title>\n"
            << "  <style>\n"
            << "    body { font-family: Arial, sans-serif; }\n"
            << "    .cms-image { border: 1px solid #ddd; margin: 10px 0; }\n"
            << "  </style>\n"
            << "</head>\n"
            << "<body>\n"
            << response.html << "\n"
            << "</body>\n"
            << "</html>";

        out.close();

        std::cout << "Page generated successfully: output.html" << std::endl;
    }
}


TEST_F(test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem, test_simpleTestAndImage)
{
    {
        std::ofstream strm("database.tmp.json");
        strm << szExampleJsonBase << std::endl;
    }
    cms::cJSONDataBase db("database.tmp.json");

    const std::string scope("TestA");
    // Инициализация
    Test_cFactory f1;
    f1.Register(std::string("header"), Test_cFactory::getHeaderComponent);
    f1.Register(std::string("text"), Test_cFactory::getTextComponent);
    f1.Register(std::string("image"), Test_cFactory::getImageComponent);
    

    cIoC t0;
    cAuthServer auth("", 1);;
    cComponentRegistry registry(scope, t0);
    cPageController controller(db, auth, registry);

    const cFactory& f11 = f1;
    t0.Resolve<iCommand>("Register", scope, f11)->Execute();

    std::string sPageId("page_01");
    cUser user;
    cPageId pageId;
    cRequestAccessToPage req(user, pageId);
    
    // Генерация страницы
    auto response = controller.renderPage(req);

    EXPECT_TRUE(response.access_denied);
    if (response.access_denied) 
    {
        std::cerr << "Access denied!" << std::endl;

    }
    else
    {
        // Сохраняем в HTML файл
        std::ofstream out("output.html");
        out << "<!DOCTYPE html>\n"
            << "<html>\n"
            << "<head>\n"
            << "  <title>CMS Generated Page</title>\n"
            << "  <style>\n"
            << "    body { font-family: Arial, sans-serif; }\n"
            << "    .cms-image { border: 1px solid #ddd; margin: 10px 0; }\n"
            << "  </style>\n"
            << "</head>\n"
            << "<body>\n"
            << response.html << "\n"
            << "</body>\n"
            << "</html>";

        out.close();

        std::cout << "Page generated successfully: output.html" << std::endl;
    }
    
}



const char* szExampleJsonBase
= R"({
  "users": [
    {
      "username": "admin",
      "password_hash": "$2a$10$N9qo8uLOickgx2ZMRZoMy.MrYV7Z1vL3H9CQ7sB6J3q7zQ9JQ1qW2",
      "role": "admin",
      "email": "admin@example.com"
    }
  ],
  "pages": [
    {
      "id": "1",
      "title": "Test Page",
      "components": [
        {
          "type": "text",
          "parameters": {
            "content": "Hello, world! Look at this",
            "color": "#00ff00",
            "font-size": "24",
            "style": "color: blue; font-size: 24px;"
          }
        },
        {
          "type": "image",
          "parameters": {
            "src": "https://otus.ru/_next/static/images/img/logo2022_without_text-ad6a01e8608432b9967c441a0f4760b4.svg",
            "alt": "Sample Image",
            "width": 400,
            "class": "responsive-img"
          }
        }
      ],
      "permissions": {
        "read": ["admin", "editor"],
        "write": ["admin"]
      }
    }
  ]
}
)";