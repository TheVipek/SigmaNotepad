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

void TextEdit::handleNormalEvent(const SDL_Event &e) {

    switch (e.type) {
        case SDL_TEXTINPUT: {
            insertText(e.text.text, 1);
            break;
        }
        case SDL_KEYDOWN: {
            int keycode = e.key.keysym.sym;
            //handle normal events
            if (keycode == SDLK_BACKSPACE) {
                //printf("BACKSPACE \n");
                if (!text.empty()) {
                    removeText(1);
                }
            } else if (keycode == SDLK_TAB) {
                insertText("   ", 3);
            } else if (keycode == SDLK_RETURN) {
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
                //     case SDLK_x: {
                //         std::cout << "Cut command\n";
                //         return false;
                //     }
                //     case SDLK_c: {
                //         std::cout << "Copy command\n";
                //         return false;
                //     }
                //     case SDLK_v: {
                //         std::cout << "Paste command\n";
                //         return false;
                //     }
                }

            }
        }
    }
    return false;
}

bool TextEdit::handleSHIFTEvent(const SDL_Event &e) {
    if (e.key.keysym.mod & KMOD_SHIFT) {
        printf("passed kmod shift");
        if (selection.IsSelecting == false) {
            selection.IsSelecting = true;
            selection.updateSelectionStart(cursor.getPos());
        }
        return handleSelection(e);
    }
    else {
        printf("shift not selected");
        if (selection.IsSelecting == true) {
            selection.IsSelecting = false;

            selection.updateSelectionStart(cursor.getPos());
            selection.updateSelectionEnd(cursor.getPos());
        }
    }

    return false;
}

void TextEdit::onCursorUpdated(const Cursor& cursor) {
    if(selection.IsSelecting == true) {
        selection.updateSelectionEnd(cursor.getPos());
    }
    else {
        selection.updateSelectionStart(cursor.getPos());
        selection.updateSelectionEnd(cursor.getPos());
    }
}


bool TextEdit::handleSelection(const SDL_Event& e) {
    if(selection.IsSelecting == true) {
        switch (e.type) {
            case SDL_TEXTINPUT: {
                break;
            }
            case SDL_KEYDOWN: {
                int keycode = e.key.keysym.sym;
                if (keycode == SDLK_BACKSPACE) {
                    int selectionStart = selection.SelectionStart >= selection.SelectionEnd ?  selection.SelectionEnd : selection.SelectionStart;
                    int selectionEnd = selection.SelectionEnd >= selection.SelectionStart ?  selection.SelectionEnd : selection.SelectionStart;
                    std::cout << "selectionStart;" << selectionStart << "\n";
                    std::cout << "selectionEnd;" << selectionEnd << "\n";
                    removeSelectionText(selectionStart, selectionEnd - selectionStart);

                    return true;
                }
                else if (keycode == SDLK_TAB) {

                }
                else if (keycode == SDLK_RETURN) {

                }
            }
        }
    }
    return false;
}

void TextEdit::handleSelection(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines) {
 if (selection.IsSelecting) {
        SDL_SetRenderDrawColor(renderer, 52, 45, 113, 255);
        size_t startPos = selection.SelectionStart;
        size_t endPos = selection.SelectionEnd;
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
        SDL_RenderCopy(renderer, texture, nullptr, &textRect);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        yOffset += spaceBetweenLine;
    }
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

        if(handleCTRLEvent(e)) {
            printf("HANDLING CTRL EVENTS SKIP \n");
            return;
        }
        if(handleSHIFTEvent(e)) {
            printf("HANDLING SHIFT EVENTS SKIP \n");
            return;
        }
        printf("HANDLING NORMAL EVENTS \n");
        handleNormalEvent(e);

        //printf("Line; %d \n", cursor.Position.Line);
    }
}

void TextEdit::render(SDL_Renderer *renderer) {
    if (!visible)
        return;

    SigmaRenderableObject::render(renderer);

    // Background rendering
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &currentRect);

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
