project(SigmaNotepadAPP)

add_library(${PROJECT_NAME} STATIC
        src/MyMainWindow.cpp
        include/MyMainWindow.h
)
target_include_directories(SigmaNotepadAPP PUBLIC "src")
target_include_directories(SigmaNotepadAPP PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PRIVATE
        SigmaNotepadLib)
