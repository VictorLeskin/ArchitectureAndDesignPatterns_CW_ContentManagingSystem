cmake_minimum_required(VERSION 3.14)
project(ArchitectureAndDesignPatterns_CW_ContentManagingSystem)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
#add source file here

  source/tests/test_ArchitectureAndDesignPatterns_CW_ContentManagingSystem.cpp
  source/tests/test_cException.cpp
  source/tests/test_iCommand.cpp
  source/tests/test_cIoC.cpp
  source/tests/test_cUser.cpp
#add test file here
)

target_include_directories(
   ContentManagingSystem PRIVATE 
   source
)

target_link_libraries(
  ContentManagingSystem
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest GoogleMock)
gtest_discover_tests(ContentManagingSystem)