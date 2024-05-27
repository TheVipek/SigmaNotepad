#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
CMAKE_MINIMUM_REQUIRED(VERSION 3.2...3.28)

project(SigmaNotepad
        VERSION 0.1
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(SigmaNotepad)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/assets
        COMMENT "Copying resources..."
)

add_dependencies(${PROJECT_NAME} copy_resources)

find_package(GTest CONFIG REQUIRED)

target_sources(${PROJECT_NAME}
    PUBLIC
        include/StringHelpers.h
        include/Renderer/SigmaObject.h
        include/Renderer/SigmaRenderableObject.h
        include/Renderer/Button.h
        include/Renderer/TextLabel.h
        include/Renderer/TextHorizontalAligment.h
        include/Renderer/TextVerticalAligment.h
        include/Renderer/Font.h
        include/Renderer/Panel.h
        include/Renderer/Offset.h
        include/Renderer/TextEdit.h
        include/Managers/IWindowRenderingManager.h
        include/Managers/WindowRenderingManager.h
        include/Renderer/ITextAligment.h
        include/Renderer/IText.h
        include/Renderer/IBackground.h
        src/Renderer/SigmaObject.cpp
        src/Renderer/SigmaRenderableObject.cpp
        src/Renderer/Button.cpp
        src/Renderer/TextLabel.cpp
        src/Renderer/Font.cpp
        src/Renderer/Panel.cpp
        src/Renderer/TextEdit.cpp
        src/Managers/WindowRenderingManager.cpp

        main.cpp

        tests/SigmaObjectFixture.h
        tests/SigmaObjectFixture.cpp
        tests/TextEditFixture.h
        tests/TextEditFixture.cpp
        tests/main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
enable_testing()
add_test(TESTS SigmaObjectFixture COMMAND SigmaNotepad)