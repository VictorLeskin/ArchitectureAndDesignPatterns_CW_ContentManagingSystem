cmake_minimum_required(VERSION 3.14)
project(ArchitectureAndDesignPatterns_CW_ContentManagingSystem)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем необходимые зависимости
# Указываем путь к OpenSSL
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_USE_STATIC_LIBS TRUE)

# Поиск OpenSSL
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    message(STATUS "OpenSSL found: ${OPENSSL_INCLUDE_DIR}")
    include_directories(${OPENSSL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "OpenSSL not found")
endif()

# Загрузка jwt-cpp
include(FetchContent)
FetchContent_Declare(
    jwt-cpp
    GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
    GIT_TAG        v0.7.0
)
FetchContent_MakeAvailable(jwt-cpp)

# Загрузка nlohmann_json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  ContentManagingSystem

  source/ArchitectureAndDesignPatterns_CW_ContentManagingSystem.hpp
  source/ArchitectureAndDesignPatterns_CW_ContentManagingSystem.cpp
  source/cException.hpp
  source/cException.cpp
  source/iCommand.hpp
  source/iCommand.cpp
  source/cIoC.hpp
  source/cIoC.cpp
  source/cUser.hpp
  source/cUser.cpp
  source/cAuthServer.hpp
  source/cAuthServer.cpp
  source/cListOfUsers.hpp
  source/cListOfUsers.cpp
  source/cRequestAccessToPage.hpp
  source/cRequestAccessToPage.cpp
  source/cPageId.hpp
  source/cPageId.cpp
  source/components/iComponent.hpp
  source/components/iComponent.cpp
  source/components/cTextComponent.hpp
  source/components/cTextComponent.cpp
  source/components/cHeaderComponent.hpp
  source/components/cHeaderComponent.cpp
  source/components/cImageComponent.hpp
  source/components/cImageComponent.cpp
  source/database/cJSONDataBase.hpp
  source/database/cJSONDataBase.cpp
  source/cComponentRegistry.hpp
  source/cComponentRegistry.cpp
#add source file here

  source/tests/test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem.cpp
  source/tests/test_cException.cpp
  source/tests/test_iCommand.cpp
  source/tests/test_cIoC.cpp
  source/tests/test_cUser.cpp
  source/tests/test_cAuthServer.cpp
  source/tests/test_cListOfUsers.cpp
  source/tests/test_cRequestAccessToPage.cpp
  source/tests/test_cPageId.cpp
  source/components/tests/test_iComponent.cpp
  source/components/tests/test_cTextComponent.cpp
  source/components/tests/test_cHeaderComponent.cpp
  source/components/tests/test_cImageComponent.cpp
  source/database/tests/test_cJSONDataBase.cpp
  source/tests/test_cComponentRegistry.cpp
#add test file here
)

target_include_directories(
   ContentManagingSystem PRIVATE 
   source
   source/components
   source/database
)

target_link_libraries(
  ContentManagingSystem
  GTest::gtest_main
  GTest::gmock_main
  jwt-cpp::jwt-cpp
  nlohmann_json::nlohmann_json
  #OpenSSL::SSL
  #OpenSSL::Crypto
  ${OPENSSL_SSL_LIBRARY}
  ${OPENSSL_CRYPTO_LIBRARY}
)

include(GoogleTest GoogleMock)
gtest_discover_tests(ContentManagingSystem)