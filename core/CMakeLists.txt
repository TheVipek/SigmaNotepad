project(SigmaNotepadCore)

find_package(SDL2 CONFIG REQUIRED)

find_package(SDL2_ttf CONFIG REQUIRED)

add_library(SigmaNotepadLib STATIC
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
        include/Renderer/ScrollLayout.h
        include/IEventHandler.h
        include/Renderer/IRenderHandler.h
        include/Window/Window.h
        include/IRenderFrame.h
        include/Renderer/Dropdown.h
        include/Renderer/DropdownItem.h
        include/Renderer/NumericEdit.h
        include/Renderer/IEditField.h
        include/Renderer/ExtendableDropdownItem.h
        include/Renderer/IDropdownHolder.h
        include/Renderer/ScrollLayoutText.h
        include/Renderer/IInteractableColors.h

        src/Renderer/SigmaObject.cpp
        src/Renderer/SigmaRenderableObject.cpp
        src/Renderer/Button.cpp
        src/Renderer/TextLabel.cpp
        src/Renderer/Font.cpp
        src/Renderer/Panel.cpp
        src/Renderer/TextEdit.cpp
        src/Managers/WindowRenderingManager.cpp
        src/Renderer/Dropdown.cpp
        src/Renderer/DropdownItem.cpp
        src/Window/Window.cpp
        src/Renderer/ExtendableDropdownItem.cpp

        tfd/tinyfiledialogs.h
        tfd/tinyfiledialogs.cpp
)

target_include_directories(SigmaNotepadLib PUBLIC "src")
target_include_directories(SigmaNotepadLib PUBLIC "include")
target_include_directories(SigmaNotepadLib PUBLIC "tfd")

target_link_libraries(SigmaNotepadLib
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)