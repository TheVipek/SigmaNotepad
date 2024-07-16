project(SigmaNotepadAPP)

add_library(${PROJECT_NAME} STATIC
        src/MyMainWindow.cpp
        src/FontSettingsWindow.cpp
        include/MyMainWindow.h
        include/FontSettingsWindow.h
)

find_package(unofficial-nativefiledialog CONFIG REQUIRED)
target_include_directories(SigmaNotepadAPP PUBLIC "src")
target_include_directories(SigmaNotepadAPP PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::nativefiledialog::nfd)
target_link_libraries(${PROJECT_NAME} PRIVATE
        SigmaNotepadLib)
