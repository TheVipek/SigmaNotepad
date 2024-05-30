project(SigmaNotepadTests)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        SigmaObjectFixture.h
        SigmaObjectFixture.cpp
        TextEditFixture.h
        TextEditFixture.cpp
        main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        SigmaNotepadLib)

enable_testing()