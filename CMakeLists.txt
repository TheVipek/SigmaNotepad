CMAKE_MINIMUM_REQUIRED(VERSION 3.2...3.28)

project(SigmaNotepad
        VERSION 0.1
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(SDL2_PATH ${CMAKE_SOURCE_DIR}/libs/SDL2)
set(SDL2_LIBRARY ${CMAKE_SOURCE_DIR}/libs/SDL2/lib/libSDL2.a)

set(SDL2_TTF_LIBRARY ${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/lib/libSDL2_ttf.a)
set(SDL2_TTF_PATH ${CMAKE_SOURCE_DIR}/libs/SDL2_ttf)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(SigmaNotepad)


target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")



target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} -lsetupapi -limm32 -lversion -lwinmm)
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARY} -lRpcrt4)


add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/assets
        COMMENT "Copying resources..."
)

add_dependencies(${PROJECT_NAME} copy_resources)


target_sources(${PROJECT_NAME}
    PUBLIC
        include/Renderer/SigmaObject.h
        include/Renderer/SigmaRenderableObject.h
        include/Renderer/Button.h
        include/Renderer/TextLabel.h
        include/Renderer/TextHorizontalAligment.h
        include/Renderer/TextVerticalAligment.h
        include/Renderer/Font.h
        include/Renderer/Panel.h

        include/Managers/IWindowRenderingManager.h
        include/Managers/WindowRenderingManager.h

        src/Renderer/SigmaObject.cpp
        src/Renderer/SigmaRenderableObject.cpp
        src/Renderer/Button.cpp
        src/Renderer/TextLabel.cpp
        src/Renderer/Font.cpp
        src/Renderer/Panel.cpp

        src/Managers/WindowRenderingManager.cpp

        main.cpp
)




