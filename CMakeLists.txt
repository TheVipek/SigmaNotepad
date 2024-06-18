#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
CMAKE_MINIMUM_REQUIRED(VERSION 3.2...3.28)

project(SigmaNotepad
        VERSION 0.1
        DESCRIPTION ""
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

add_subdirectory(tests)
add_subdirectory(core)
add_subdirectory(app)

add_executable(SigmaNotepad main.cpp)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/assets
        COMMENT "Copying resources..."
)
add_dependencies(${PROJECT_NAME} copy_resources)
target_link_libraries(SigmaNotepad
        PRIVATE
        SigmaNotepadLib
        SigmaNotepadAPP
)





