//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"
#include "regex"

void TextEdit::handleNormalEvent(const SDL_Event &e) {

    switch (e.type) {
        case SDL_TEXTINPUT: {
            insertText(e.text.text, 1);
            break;
        }
        case SDL_KEYDOWN: {
            int keycode = e.key.keysym.sym;
            //handle normal events
            auto &currentTextLine = text[cursor.Position.Column];
            if (keycode == SDLK_BACKSPACE) {
                //printf("BACKSPACE \n");
                if (currentTextLine.empty()) {
                    if (cursor.Position.Column == 0) {
                        break;
                    }

                    cursor.Position.Column--;
                    cursor.Position.Line = text[cursor.Position.Column].size();
                } else {
                    removeText(1);
                }
            } else if (keycode == SDLK_TAB) {
                insertText("   ", 3);
            } else if (keycode == SDLK_RETURN) {
                if (text.size() - 1 == cursor.Position.Column) {
                    // last index
                    //printf("LAST textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                    if (cursor.Position.Line < currentTextLine.size()) {
                        //printf("smaller \n");
                        rope<char> newLineText = currentTextLine.substr(
                            cursor.Position.Line, currentTextLine.size() - cursor.Position.Line);
                        text.push_back(newLineText);

                        rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Position.Line);
                        text[cursor.Position.Column] = modifiedCurrentLine;
                    } else {
                        text.emplace_back();
                    }
                } else if (text.size() - 1 > cursor.Position.Column) {
                    // between index
                    //printf("BETWEEN textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                    if (cursor.Position.Line < currentTextLine.size()) {
                        //printf("smaller \n");
                        rope<char> newLineText = currentTextLine.substr(
                            cursor.Position.Line, currentTextLine.size() - cursor.Position.Line);
                        text.insert(text.begin() + cursor.Position.Column + 1, newLineText);

                        rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Position.Line);
                        text[cursor.Position.Column] = modifiedCurrentLine;
                    } else {
                        //printf("insert between \n");
                        text.insert(text.begin() + cursor.Position.Column + 1, rope<char>(""));
                    }
                }
                cursor.Position.Column++;
                cursor.Position.Line = text[cursor.Position.Column].size();
            } else if (keycode == SDLK_LEFT) {
                if (cursor.Position.Column == 0 && cursor.Position.Line == 0) {
                    printf("Beginning of document \n");
                    break;
                }

                if (cursor.Position.Line == 0) {
                    //printf("Detected newline character");
                    cursor.Position.Column--;
                    cursor.Position.Line = text[cursor.Position.Column].size();
                } else {
                    cursor.Position.Line--;
                }
            } else if (keycode == SDLK_RIGHT) {
                if (cursor.Position.Column == text.size() - 1 && cursor.Position.Line >= currentTextLine.size()) {
                    printf("End of document \n");
                    break;
                }

                if (cursor.Position.Line > currentTextLine.size() - 1) {
                    cursor.Position.Column++;
                    cursor.Position.Line = 0;
                } else {
                    cursor.Position.Line++;
                }
            } else if (keycode == SDLK_UP) {
                if (cursor.Position.Column == 0) {
                    printf("First column of document \n");
                    break;
                }
                cursor.Position.Column--;
                if (text[cursor.Position.Column].size() < cursor.Position.Line) {
                    cursor.Position.Line = text[cursor.Position.Column].size();
                }
            } else if (keycode == SDLK_DOWN) {
                if (cursor.Position.Column == text.size() - 1) {
                    if (cursor.Position.Line < currentTextLine.size()) {
                        cursor.Position.Line = currentTextLine.size();
                    }
                    printf("Last column of document \n");
                    break;
                }
                cursor.Position.Column++;
                if (text[cursor.Position.Column].size() < cursor.Position.Line) {
                    cursor.Position.Line = text[cursor.Position.Column].size();
                }
            }
        }
    }
}

bool TextEdit::handleCTRLEvent(const SDL_Event &e) {
    if (SDL_GetModState() & KMOD_CTRL) {
        switch(e.type) {
            case SDL_KEYDOWN: {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: {
                        // Skip multiple characters to left
                        if (cursor.Position.Line == 0) {
                            return false;
                        }

                        std::string beforeCursor(text[cursor.Position.Column].begin(),
                                                 text[cursor.Position.Column].begin() + cursor.Position.Line);
                        std::reverse(beforeCursor.begin(), beforeCursor.end());
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            if (cursor.Selection.IsSelecting) {
                                //cursor.Selection.SelectionEnd = cursor.Position.Line;
                            }
                            cursor.Position.Line -= match.length();
                            return true;
                        }
                        return false;
                    }
                    case SDLK_RIGHT: {
                        if (cursor.Position.Line >= text[cursor.Position.Column].size()) {
                            //printf("right false \n");
                            return false;
                        }
                        std::string beforeCursor(text[cursor.Position.Column].begin() + cursor.Position.Line,
                                                 text[cursor.Position.Column].end());;
                        std::regex pattern(R"((\s+|\W+|\w+))");
                        std::smatch match;

                        if (std::regex_search(beforeCursor, match, pattern)) {
                            cursor.Position.Line += match.length();
                            return true;
                        }
                        // Skip multiple characters to right
                        return false;
                    }
                    case SDLK_x: {
                        std::cout << "Cut command\n";
                        return false;
                    }
                    case SDLK_c: {
                        std::cout << "Copy command\n";
                        return false;
                    }
                    case SDLK_v: {
                        std::cout << "Paste command\n";
                        return false;
                    }
                }

            }
        }
    }
    return false;
}

bool TextEdit::handleSHIFTEvent(const SDL_Event &e) {
    if (SDL_GetModState() & KMOD_SHIFT) {
        if (cursor.Selection.IsSelecting == false) {

            cursor.Selection.IsSelecting = true;
            cursor.Selection.SelectionStart.Column = cursor.Position.Column;
            cursor.Selection.SelectionStart.Line = cursor.Position.Line;

            cursor.Selection.SelectionEnd.Column = cursor.Position.Column;
            cursor.Selection.SelectionEnd.Line = cursor.Position.Line;

            printf("SelectionStart; Column:%d Line:%d \n", cursor.Selection.SelectionStart.Column,
                  cursor.Selection.SelectionStart.Line);
        } else if (cursor.Selection.IsSelecting == true) {
            cursor.Selection.SelectionEnd.Column = cursor.Position.Column;
            cursor.Selection.SelectionEnd.Line = cursor.Position.Line;

            printf("update SelectionEnd to; Column:%d Line:%d \n", cursor.Position.Column, cursor.Position.Line);
        }

        handleSelection(e);
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

void TextEdit::insertText(const char *val, const int &count) {
    text[cursor.Position.Column].insert(cursor.Position.Line, val);
    cursor.Position.Line += count;
}

void TextEdit::removeText(const int &count) {
    cursor.Position.Line -= count;
    text[cursor.Position.Column].erase(cursor.Position.Line, count);
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
    int spaceBetweenLine = TTF_FontLineSkip(font->get());
    int yOffset = 0;

    // Render cursor

    //It is being rendered first, so we can se blinking cursor on top of it
    if (cursor.Selection.IsSelecting) {
        // need to draw it line by line like font i think
        SDL_SetRenderDrawColor(renderer, 52, 45, 113, 255);
        Position startPos = cursor.Selection.SelectionStart;
        Position endPos = cursor.Selection.SelectionEnd;

        int xPosition, xSize, yPosition, ySize;
        if (startPos.Column == endPos.Column) {
            // one liner
            xPosition = currentRect.x + (letterWidth * startPos.Line);
            xSize = letterWidth * (endPos.Line - startPos.Line);
            yPosition = currentRect.y + (startPos.Column * spaceBetweenLine);
            ySize = spaceBetweenLine;

            SDL_Rect rect = {
                xPosition,
                yPosition,
                xSize,
                ySize
            };
            SDL_RenderFillRect(renderer, &rect);
        } else if (startPos.Column < endPos.Column) {
            // from left to right
            for (int i = startPos.Column; i <= endPos.Column; i++) {
                if (i == endPos.Column) {
                    // last line
                    xPosition = currentRect.x;
                    xSize = letterWidth * endPos.Line;
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                } else if (i == startPos.Column) {
                    // first line
                    xPosition = currentRect.x + (letterWidth * startPos.Line);
                    xSize = letterWidth * (text[i].size() - startPos.Line);
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                } else {
                    // any other line
                    xPosition = currentRect.x;
                    xSize = letterWidth * text[i].size();
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        } else if (startPos.Column > endPos.Column) {
            // ** INCOMPLETED ** // from right to left

            for (int i = startPos.Column; i >= endPos.Column; i--) {
                if (i == endPos.Column) {
                    // first line
                    xPosition = currentRect.x + (letterWidth * endPos.Line);
                    xSize = letterWidth * (text[i].size() - endPos.Line);
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                } else if (i == startPos.Column) {
                    // last line
                    xPosition = currentRect.x + (letterWidth * startPos.Line);
                    xSize = text[i].size() == startPos.Line ? -startPos.Line : startPos.Line - text[i].size();
                    xSize *= letterWidth;
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                } else {
                    xPosition = currentRect.x;
                    xSize = letterWidth * text[i].size();
                    yPosition = currentRect.y + (i * spaceBetweenLine);
                    ySize = spaceBetweenLine;

                    SDL_Rect rect = {
                        xPosition,
                        yPosition,
                        xSize,
                        ySize
                    };
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }


    Uint32 ticks = SDL_GetTicks();
    if (ticks - cursor.LastTimeBlink > cursor.BLINK_INTERVAL) {
        cursor.LastTimeBlink = ticks;
        cursor.IsBlinking = !cursor.IsBlinking;
    }
    if (cursor.IsBlinking) {
        int cursorPosX, cursorPosY;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        cursorPosX = currentRect.x + (letterWidth * cursor.Position.Line);
        cursorPosY = currentRect.y + (cursor.Position.Column * spaceBetweenLine);
        SDL_RenderDrawLine(renderer, cursorPosX, cursorPosY, cursorPosX, cursorPosY + spaceBetweenLine);
    }


    // Render each line of text
    for (size_t i = 0; i < text.size(); ++i) {
        const auto &lineRope = text[i];
        std::string line(lineRope.c_str(), lineRope.size());
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
