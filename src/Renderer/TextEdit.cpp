//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"
#include "regex"
#include "StringHelpers.h"

void TextEdit::insertText(const char *val, const int &count) {
    text.insert(cursor.Position, val);
    cursor.Position += count;
}

void TextEdit::removeText(const int &count) {
    if(cursor.Position > 0) {
        cursor.Position -= count;
        text.erase(cursor.Position, count);
    }
}
void TextEdit::removeSelectionText(const int &startPos, const int &count) {
    std::cout << "startPos;" << startPos << "\n";
    std::cout << "deletion count;" << count << "\n";
    std::cout << "textCount; " << text.size() << "\n";
    if(startPos >= 0 && count <= text.size() - startPos) {
        cursor.Position = startPos;
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
                if(cursor.Position > 0) {
                    cursor.Position--;
                }
            } else if (keycode == SDLK_RIGHT) {
                if(cursor.Position < text.size()) {
                    cursor.Position++;
                }
            } else if (keycode == SDLK_UP) {
                if (cursor.Position == 0) {
                    std::cout << "First line of document" << std::endl;
                    return;
                }

                size_t currentLineStart = findLineStart(cursor.Position, text.c_str(), '\n');
                if (currentLineStart == 0) {
                    cursor.Position = 0;
                    std::cout << "First line of document" << std::endl;
                } else {
                    size_t previousLineEnd = currentLineStart - 1;
                    size_t previousLineStart = findLineStart(previousLineEnd, text.c_str(), '\n');
                    size_t distanceFromLineStart = cursor.Position - currentLineStart;
                    cursor.Position = previousLineStart + std::min(distanceFromLineStart, previousLineEnd - previousLineStart);
                }
            }
            else if (keycode == SDLK_DOWN) {
                size_t currentLineEnd  = findLineEnd(cursor.Position, text.c_str(), '\n');
                if (currentLineEnd  == text.size()) {
                    std::cout << "End line of document" << std::endl;
                    return;
                }

                size_t nextLineStart = currentLineEnd + 1;
                size_t nextLineEnd = findLineEnd(nextLineStart, text.c_str(), '\n');
                size_t distanceFromLineStart = cursor.Position - findLineStart(cursor.Position, text.c_str(), '\n');
                cursor.Position = nextLineStart + std::min(distanceFromLineStart, nextLineEnd - nextLineStart);
            }
        }
    }
}

bool TextEdit::handleCTRLEvent(const SDL_Event &e, bool isCtrlPressed) {
    if (isCtrlPressed) {
        switch(e.type) {
            case SDL_KEYDOWN: {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: {
                        // Skip multiple characters to left
                        if (cursor.Position == 0) {
                            return false;
                        }

                        std::string beforeCursor(text.begin(),
                                                 text.begin() + cursor.Position);
                        std::reverse(beforeCursor.begin(), beforeCursor.end());
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            if (cursor.Selection.IsSelecting) {
                                //cursor.Selection.SelectionEnd = cursor.Position.Line;
                            }
                            cursor.Position -= match.length();
                            return true;
                        }
                        return false;
                    }
                    case SDLK_RIGHT: {
                        if (cursor.Position == text.size()) {
                            //printf("right false \n");
                            return false;
                        }
                        std::string beforeCursor(text.begin() + cursor.Position,
                                                 text.end());;
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            cursor.Position += match.length();
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

bool TextEdit::handleSHIFTEvent(const SDL_Event &e, bool isShiftPressed) {
    if (isShiftPressed) {
        if (cursor.Selection.IsSelecting == false) {

            cursor.Selection.IsSelecting = true;
            cursor.Selection.SelectionStart = cursor.Position;

            cursor.Selection.SelectionEnd = cursor.Position;

            printf("SelectionStart; %d \n", cursor.Selection.SelectionStart);
        } else if (cursor.Selection.IsSelecting == true) {
            cursor.Selection.SelectionEnd = cursor.Position;

            printf("update SelectionEnd to; %d \n", cursor.Selection.SelectionEnd);
        }

        return handleSelection(e);
    }
    else {
        printf("shift not selected");
        if (cursor.Selection.IsSelecting == true) {
            cursor.Selection.IsSelecting = false;
        }
    }

    return false;
}

bool TextEdit::handleSelection(const SDL_Event& e) {
    if(cursor.Selection.IsSelecting == true) {
        switch (e.type) {
            case SDL_TEXTINPUT: {
                break;
            }
            case SDL_KEYDOWN: {
                int keycode = e.key.keysym.sym;
                if (keycode == SDLK_BACKSPACE) {
                    int selectionStart = cursor.Selection.SelectionStart >= cursor.Selection.SelectionEnd ?  cursor.Selection.SelectionEnd : cursor.Selection.SelectionStart;
                    int selectionEnd = cursor.Selection.SelectionEnd >= cursor.Selection.SelectionStart ?  cursor.Selection.SelectionEnd : cursor.Selection.SelectionStart;
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

void TextEdit::handleCursorSelection(SDL_Renderer* renderer, const int spaceBetweenLine, const std::vector<std::string> lines) {
 if (cursor.Selection.IsSelecting) {
        SDL_SetRenderDrawColor(renderer, 52, 45, 113, 255);
        size_t startPos = cursor.Selection.SelectionStart;
        size_t endPos = cursor.Selection.SelectionEnd;
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
    Uint32 ticks = SDL_GetTicks();
    if (ticks - cursor.LastTimeBlink > cursor.BLINK_INTERVAL) {
        cursor.LastTimeBlink = ticks;
        cursor.IsBlinking = !cursor.IsBlinking;
    }

    if (cursor.IsBlinking) {
        int cursorPosX, cursorPosY;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        size_t currentPos = 0;
        size_t cursorLine = 0;
        size_t cursorColumn = 0;

        for (auto const line : lines) {
            size_t lineStart = currentPos;
            size_t lineEnd = lineStart + line.size();

            if (cursor.Position >= lineStart && cursor.Position <= lineEnd) {

                cursorColumn = cursor.Position - lineStart;
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
            isActive = false;
        } else {
            printf("active \n");
            isActive = true;
        }
    }

    //Writing
    if (isActive) {

        if(handleCTRLEvent(e, SDL_GetModState() & KMOD_CTRL)) {
            printf("HANDLING CTRL EVENTS SKIP \n");
            return;
        }
        if(handleSHIFTEvent(e, SDL_GetModState() & KMOD_SHIFT)) {
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
    handleCursorSelection(renderer, spaceBetweenLine, splittedText);
    //And now blinking
    handleCursorBlinking(renderer, spaceBetweenLine, splittedText);

    // Render each line of text
    handleRenderingText(renderer,spaceBetweenLine, splittedText);

}

