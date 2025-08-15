///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

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
        static cTextComponent* getTextComponent()
        {
            return new cTextComponent;
        }
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
}

TEST_F(test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem, test_simpleTestAndImage)
{
    const std::string scope("TestA");
    // Инициализация
    Test_cFactory f1;
    f1.Register(std::string("test"), Test_cFactory::getTextComponent);

    cIoC t0;
    cAuthServer auth("", 1);;
    cComponentRegistry registry(scope, t0);
    cPageController controller(registry, auth);

    const cFactory& f11 = f1;
    t0.Resolve<iCommand>("Register", scope, f11)->Execute();

    std::string sPageId("page_01");
    
    // Генерация страницы
    auto response = controller.renderPage(sPageId, "admin_token");

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

