//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"
#include "regex"
#include "StringHelpers.h"

void TextEdit::insertText(const char *val, const int &count) {
    text.insert(cursor.getPos(), val);
    cursor.updatePosition(cursor.getPos() + count);
    printf("inserting text, currentIndex; %d \n", cursor.getPos());
}

void TextEdit::removeText(const int &count) {
    if(cursor.getPos() > 0) {
        cursor.updatePosition(cursor.getPos() - count);
        text.erase(cursor.getPos(), count);
    }
}

void TextEdit::removeSelectionText(const int &startPos, const int &count) {
    std::cout << "startPos;" << startPos << "\n";
    std::cout << "deletion count;" << count << "\n";
    std::cout << "textCount; " << text.size() << "\n";
    if(startPos >= 0 && count <= text.size() - startPos) {
        cursor.updatePosition(startPos);
        text.erase(startPos, count);
    }
}

std::string TextEdit::getSelectionText(const int &startPos, const int &count) {
    std::cout << "startPos;" << startPos << "\n";
    std::cout << "get count;" << count << "\n";
    std::cout << "textCount; " << text.size() << "\n";
    if(startPos >= 0 && count <= text.size() - startPos) {
        return text.substr(startPos, count).c_str();
    }
    return "";

}

bool TextEdit::copyToClipboard() {
    printf("INSIDE COPY CLIPBOARD \n");
    auto _orderedSelection = selection.getOrderedSelection();
    std::string selectedText = getSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);

    if(selectedText.length() == 0) {
        return false;
    }
    printf("after length check \n");

    if(SDL_SetClipboardText(selectedText.c_str()) != 0) {
        printf("Unable to set clipboard text: %s", SDL_GetError());
        return false;
    }
    return true;
}

bool TextEdit::pasteFromClipboard() {
    std::string text = SDL_GetClipboardText();
    if(text.length() == 0) {
        return false;
    }

    insertText(text.c_str(), text.length());
    return true;
}


void TextEdit::handleNormalEvent(const SDL_Event &e) {

    switch (e.type) {
        case SDL_TEXTINPUT: {
            if(selection.IsSelecting) {
                auto _orderedSelection = selection .getOrderedSelection();
                selection.IsSelecting = false;
                removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
            }
            insertText(e.text.text, 1);
            break;
        }
        case SDL_KEYDOWN: {
            int keycode = e.key.keysym.sym;
            //handle normal events
            if (keycode == SDLK_BACKSPACE) {
                //printf("BACKSPACE \n");
                if (!text.empty()) {
                    if(selection.IsSelecting) {
                        auto _orderedSelection = selection .getOrderedSelection();
                        selection.IsSelecting = false;
                        removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
                    }
                    else {
                        removeText(1);
                    }
                }
            } else if (keycode == SDLK_TAB) {
                if(selection.IsSelecting) {
                    auto _orderedSelection = selection .getOrderedSelection();
                    selection.IsSelecting = false;
                    removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
                }
                insertText("   ", 3);
            } else if (keycode == SDLK_RETURN) {
                if(selection.IsSelecting) {
                    auto _orderedSelection = selection .getOrderedSelection();
                    selection.IsSelecting = false;
                    removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
                }
                insertText("\n", 1);
            } else if (keycode == SDLK_LEFT) {
                if(cursor.getPos() > 0) {
                    cursor.updatePosition(cursor.getPos() - 1);
                }
                //printf("moving left, currentIndex; %d \n", cursor.Position);
            } else if (keycode == SDLK_RIGHT) {
                if(cursor.getPos() < text.size()) {
                    cursor.updatePosition(cursor.getPos() + 1);
                }
                //printf("moving right, currentIndex; %d \n", cursor.Position);
            } else if (keycode == SDLK_UP) {
                if (cursor.getPos() == 0) {
                    std::cout << "First line of document" << std::endl;
                    return;
                }

                size_t currentLineStart = findLineStart(cursor.getPos(), text.c_str(), '\n');
                if (currentLineStart == 0) {
                    cursor.updatePosition(0);
                    std::cout << "First line of document" << std::endl;
                } else {
                    size_t previousLineEnd = currentLineStart - 1;
                    size_t previousLineStart = findLineStart(previousLineEnd, text.c_str(), '\n');
                    size_t distanceFromLineStart = cursor.getPos() - currentLineStart;
                    cursor.updatePosition( previousLineStart + std::min(distanceFromLineStart, previousLineEnd - previousLineStart));
                }
            }
            else if (keycode == SDLK_DOWN) {
                if(cursor.getPos() == text.size()) {
                    std::cout << "End line of document" << std::endl;
                    return;
                }

                size_t currentLineEnd  = findLineEnd(cursor.getPos(), text.c_str(), '\n');
                if (currentLineEnd  == text.size()) {
                    cursor.updatePosition(text.size());
                }
                else {
                    size_t nextLineStart = currentLineEnd + 1;
                    size_t nextLineEnd = findLineEnd(nextLineStart, text.c_str(), '\n');
                    size_t distanceFromLineStart = cursor.getPos() - findLineStart(cursor.getPos(), text.c_str(), '\n');

                    cursor.updatePosition(nextLineStart + std::min(distanceFromLineStart, nextLineEnd - nextLineStart));
                }



            }
        }
    }
}

bool TextEdit::handleCTRLEvent(const SDL_Event &e) {
    if (e.key.keysym.mod & KMOD_CTRL) {
        switch(e.type) {
            case SDL_KEYDOWN: {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: {
                        // Skip multiple characters to left
                        if (cursor.getPos() == 0) {
                            return false;
                        }

                        std::string beforeCursor(text.begin(),
                                                 text.begin() + cursor.getPos());
                        std::reverse(beforeCursor.begin(), beforeCursor.end());
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            if (selection.IsSelecting) {
                                //cursor.Selection.SelectionEnd = cursor.Position.Line;
                            }
                            cursor.updatePosition(cursor.getPos() - match.length());
                            return true;
                        }
                        return false;
                    }
                    case SDLK_RIGHT: {
                        if (cursor.getPos() == text.size()) {
                            //printf("right false \n");
                            return false;
                        }
                        std::string beforeCursor(text.begin() + cursor.getPos(),
                                                 text.end());;
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            cursor.updatePosition(cursor.getPos() + match.length());
                            return true;
                        }
                        // Skip multiple characters to right
                        return false;
                    }
                    case SDLK_x: {
                        if(selection.IsSelecting) {
                            if(copyToClipboard() == true) {
                                std::cout << "Cut command\n";
                                selection.IsSelecting = false;
                                auto _orderedSelection = selection .getOrderedSelection();
                                removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
                                return true;
                            }
                        }
                        return false;
                    }
                    case SDLK_c: {
                        if(selection.IsSelecting) {
                            if(copyToClipboard() == true) {
                                std::cout << "Copy command\n";
                                return true;
                            }
                        }
                        return false;
                    }
                    case SDLK_v: {
                        if(selection.IsSelecting) {
                            selection.IsSelecting = false;
                            auto _orderedSelection = selection .getOrderedSelection();
                            removeSelectionText(_orderedSelection.first, _orderedSelection.second - _orderedSelection.first);
                        }
                        if(pasteFromClipboard() == true) {
                            std::cout << "Paste command\n";
                            return true;
                        }
                        return false;
                    }
                }
                default: {
                    //printf("No Ctrl Implementation");
                    return false;
                }
            }
        }
    }
    return false;
}

void TextEdit::handleSHIFTEvent(const SDL_Event &e) {
    switch(e.type) {
        case SDL_KEYDOWN: {
            if (e.key.keysym.mod & KMOD_SHIFT) {
                if (selection.IsSelecting == false) {
                    printf("SELECTED \n");
                    selection.IsSelecting = true;
                    selection.updateSelectionStart(cursor.getPos());
                }
            }
        }
        case SDL_KEYUP: {
            if(!(e.key.keysym.mod & KMOD_SHIFT)) {
                switch(e.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                    case SDLK_UP:
                    case SDLK_DOWN: {
                        if (selection.IsSelecting == true) {
                            printf("NOT SELECTED \n");
                            selection.IsSelecting = false;
                            selection.updateSelectionStart(cursor.getPos());
                            selection.updateSelectionEnd(cursor.getPos());
                        }
                    }
                }
            }
        }
    }
}

void TextEdit::onCursorUpdated(const Cursor& cursor) {
    if(selection.IsSelecting == true) {
        //printf("updating end selection \n");
        selection.updateSelectionEnd(cursor.getPos());
    }
    else {
        //printf("updating start+end selection \n");
        selection.updateSelectionStart(cursor.getPos());
        selection.updateSelectionEnd(cursor.getPos());
    }
}

int TextEdit::convertMousePositionToCharacterPosition(const int x, const int y) {
    if(text.size() == 0) {
        return 0;
    }

    auto splitted = split(text.c_str(), "\n");
    int spaceBetweenLine = getSpaceBetweenLine();
    int targetY = std::floor((y - baseRect.y) / spaceBetweenLine) ;
    if(targetY >= splitted.size()) {
        return text.size(); // last index
    }

    int charIndex = 0;
    for (int i = 0; i < targetY; ++i) {
        charIndex += splitted[i].size() + 1; // +1 for the newline character
    }

    int targetX = x / letterWidth;

    if(targetX >= splitted[targetY].size()) {
        return charIndex + splitted[targetY].size();
    }
    return charIndex + targetX;
}

bool TextEdit::handleMouse(const SDL_Event &e) {
    switch(e.type) {
        case SDL_MOUSEBUTTONDOWN: {
            printf("MOUSE DOWN");
            auto pos = convertMousePositionToCharacterPosition(e.button.x,e.button.y);

            selection.IsSelecting = false;
            cursor.updatePosition(pos);
            selection.IsSelecting = true;

            selection.IsMousePressed = true;
            return true;
        }
        case SDL_MOUSEBUTTONUP: {
            selection.IsMousePressed = false;
            return false;
        }
        case SDL_MOUSEMOTION: {
            if(selection.IsMousePressed == true) {
                printf("MOTION CALLED \n");
                auto pos = convertMousePositionToCharacterPosition(e.button.x,e.button.y);
                cursor.updatePosition(pos);
            }
            return true;
        }
    }
    return false;
}

void TextEdit::handleSelection(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines) {

    size_t startPos = selection.SelectionStart;
    size_t endPos = selection.SelectionEnd;
    if(startPos == endPos)
        return;

    SDL_SetRenderDrawColor(renderer, 52, 45, 113, 255);

    if (startPos > endPos) {
        std::swap(startPos, endPos);
    }

    size_t currentPos = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        size_t lineStart = currentPos;
        size_t lineEnd = lineStart + line.size();

        if (endPos <= lineStart) {
            // Selection ends before the current line starts
            break;
        }

        if (startPos >= lineEnd) {
            // Selection starts after the current line ends
            currentPos += line.size() + 1; // +1 for the newline character
            continue;
        }

        int xPosition = currentRect.x;
        int yPosition = currentRect.y + (i * spaceBetweenLine);
        int xSize;
        int ySize = spaceBetweenLine;

        if (startPos <= lineStart && endPos >= lineEnd) {
            // Entire line is selected
            xSize = letterWidth * line.size();
        } else if (startPos > lineStart && endPos < lineEnd) {
            // Selection is within this single line
            xPosition += letterWidth * (startPos - lineStart);
            xSize = letterWidth * (endPos - startPos);
        } else if (startPos <= lineStart && endPos < lineEnd) {
            // Selection starts before this line and ends within this line
            xSize = letterWidth * (endPos - lineStart);
        } else if (startPos > lineStart && endPos >= lineEnd) {
            // Selection starts within this line and ends after this line
            xPosition += letterWidth * (startPos - lineStart);
            xSize = letterWidth * (lineEnd - startPos);
        }

        SDL_Rect rect = { xPosition, yPosition, xSize, ySize };
        SDL_RenderFillRect(renderer, &rect);

        currentPos += line.size() + 1; // +1 for the newline character
    }
}

void TextEdit::handleCursorBlinking(SDL_Renderer *renderer, const int spaceBetweenLine, const std::vector<std::string> lines) {
    cursor.updateTicks(SDL_GetTicks());

    if (cursor.IsBlinking) {
        int cursorPosX, cursorPosY;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        size_t currentPos = 0;
        size_t cursorLine = 0;
        size_t cursorColumn = 0;

        for (auto const line : lines) {
            size_t lineStart = currentPos;
            size_t lineEnd = lineStart + line.size();

            if (cursor.getPos() >= lineStart && cursor.getPos() <= lineEnd) {

                cursorColumn = cursor.getPos() - lineStart;
                break;
            }

            currentPos += line.size() + 1; // +1 for the newline character
            cursorLine++;
        }

        cursorPosX = currentRect.x + (letterWidth * cursorColumn);
        cursorPosY = currentRect.y + (cursorLine * spaceBetweenLine);

        SDL_RenderDrawLine(renderer, cursorPosX, cursorPosY, cursorPosX, cursorPosY + spaceBetweenLine);
    }
}

void TextEdit::handleRenderingText(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines) {
    int yOffset = 0;
    for (auto line : lines) {
        if (line.empty())
            line = " "; // to render even empty lines correctly

        SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(font->get(), line.c_str(), textColor, 0);
        if (surface == nullptr) {
            SDL_Log("Unable to create text surface: %s", SDL_GetError());
            continue;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            SDL_Log("Unable to create texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }
        SDL_Rect textRect = {currentRect.x, currentRect.y + yOffset, surface->w, surface->h};
        if(surface->w > contentSize.w) {
            contentSize.w = surface->w;
        }

        SDL_RenderCopy(renderer, texture, nullptr, &textRect);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        yOffset += spaceBetweenLine;
    }
    contentSize.h = spaceBetweenLine * lines.size();
}

void TextEdit::handleEvent(const SDL_Event &e) {
    if (!enabled) // no need to process events
        return;

    SigmaRenderableObject::handleEvent(e);

    //Set Active
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        const int mousePosX = e.button.x;
        const int mousePosY = e.button.y;

        const bool withinX = mousePosX > currentRect.x && mousePosX < currentRect.x + currentRect.w;
        const bool withinY = mousePosY > currentRect.y && mousePosY < currentRect.y + currentRect.h;

        if (!withinX || !withinY) {
            printf("not active \n");
            setActive(false);
        } else {
            printf("active \n");
            setActive(true);
        }
    }

    //Writing
    if (isActive) {
        handleMouse(e);

        if(selection.IsMousePressed == true) {
            return;
        }

        handleSHIFTEvent(e);

        if(handleCTRLEvent(e)) {
            //printf("HANDLING CTRL EVENTS SKIP \n");
        }
        else {
            //printf("HANDLING NORMAL EVENTS \n");
            handleNormalEvent(e);
        }


        //printf("Line; %d \n", cursor.Position.Line);
    }
}

void TextEdit::render(SDL_Renderer *renderer) {
    if (!visible)
        return;

    SigmaRenderableObject::render(renderer);

    // Background rendering
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rect = currentRect;

    if(contentSize.w > currentRect.w) {
        rect.w = contentSize.w;
    }
    if(contentSize.h > currentRect.h) {
        rect.h = contentSize.h;
    }

    SDL_RenderFillRect(renderer, &rect);

    // Font rendering
    if (font->get() == nullptr || text.empty())
        return;

    // Get font line height and calculate space between lines
    int spaceBetweenLine = getSpaceBetweenLine();

    std::vector<std::string> splittedText = split(text.c_str(), "\n");

    // Render cursor
    //It is being rendered first, so we can se blinking cursor on top of it
    handleSelection(renderer, spaceBetweenLine, splittedText);
    //And now blinking
    handleCursorBlinking(renderer, spaceBetweenLine, splittedText);

    // Render each line of text
    handleRenderingText(renderer,spaceBetweenLine, splittedText);

}

