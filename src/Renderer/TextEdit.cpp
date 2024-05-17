//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"
#include "math.h"
#include "regex"

bool TextEdit::handleCTRLEvent(const SDL_Event &e) {
    if (SDL_GetModState() & KMOD_CTRL) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: {
                // Skip multiple characters to left
                if (cursor.Line == 0)
                    return false;

                std::string beforeCursor(text[cursor.Column].begin(),text[cursor.Column].begin() + cursor.Line);
                std::reverse(beforeCursor.begin(), beforeCursor.end());
                std::regex pattern(R"((\s+|\W+|\w+))");
                std::smatch match;

                if(std::regex_search(beforeCursor, match, pattern)) {
                    cursor.Line -= match.length();
                    beforeCursor = match.suffix().str();
                }
                return true;
            }
            case SDLK_RIGHT: {
                // Skip multiple characters to right
                return true;
            }
            case SDLK_x: {
                // CTRL + X
                std::cout << "Cut command\n";
                return true;
            }
            case SDLK_c: {
                // CTRL + C
                std::cout << "Copy command\n";
                return true;
            }
            case SDLK_v: {
                // CTRL + V
                std::cout << "Paste command\n";
                return true;
            }
            default: {
                return false;
            }
        }
    }
    return false;
}


void TextEdit::handleEvent(const SDL_Event &e) {
    if(!enabled) // no need to process events
        return;

    SigmaRenderableObject::handleEvent(e);

    //Set Active
    if(e.type == SDL_MOUSEBUTTONDOWN) {
        const int mousePosX = e.button.x;
        const int mousePosY = e.button.y;

        const bool withinX = mousePosX > currentRect.x && mousePosX < currentRect.x + currentRect.w;
        const bool withinY = mousePosY > currentRect.y && mousePosY < currentRect.y + currentRect.h;

        if(!withinX || !withinY) {
            printf("not active \n");
            isActive = false;
        }
        else {
            printf( "active \n");
            isActive = true;
        }
    }

    //Writing
    if(isActive) {
        switch (e.type) {
            case SDL_TEXTINPUT: {
                text[cursor.Column].insert(cursor.Line,e.text.text);
                cursor.Line++;
                break;
            }
            case SDL_KEYDOWN: {
                int keycode = e.key.keysym.sym;
                auto currentTextLine = text[cursor.Column];

                if (handleCTRLEvent(e)) {
                    return;
                }

                if (keycode == SDLK_BACKSPACE) {
                    if(currentTextLine.empty()) {
                        if(cursor.Column == 0) {
                            break;
                        }

                        cursor.Column--;
                        cursor.Line = text[cursor.Column].size();
                    }
                    else {
                        cursor.Line--;
                        currentTextLine.erase(cursor.Line, 1);
                    }
                }
                else if (keycode == SDLK_TAB) {
                    currentTextLine.insert(cursor.Line,"   ");
                    cursor.Line+=3;
                }
                else if (keycode == SDLK_RETURN) {
                    //currentTextLine.insert(cursor.Line,"\n");  // no need for it?

                    if(text.size() - 1 == cursor.Column) { // last index
                        //printf("LAST textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                        if(cursor.Line < currentTextLine.size()) {
                            //printf("smaller \n");
                            rope<char> newLineText = currentTextLine.substr(cursor.Line, currentTextLine.size() - cursor.Line);
                            text.push_back(newLineText);

                            rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Line);
                            text[cursor.Column] = modifiedCurrentLine;
                        }
                        else {
                            text.emplace_back();
                        }
                    }
                    else if(text.size() - 1 > cursor.Column) { // between index
                        //printf("BETWEEN textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                        if(cursor.Line < currentTextLine.size()) {
                            //printf("smaller \n");
                            rope<char> newLineText = currentTextLine.substr(cursor.Line, currentTextLine.size() - cursor.Line);
                            text.insert(text.begin() + cursor.Column + 1,newLineText);

                            rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Line);
                            text[cursor.Column] = modifiedCurrentLine;
                        }
                        else {
                            //printf("insert between \n");
                            text.insert(text.begin() + cursor.Column + 1, rope<char>(""));
                        }
                    }
                    cursor.Column++;
                    cursor.Line = text[cursor.Column].size();
                }
                else if (keycode == SDLK_LEFT) {
                    if(cursor.Column == 0 && cursor.Line == 0) {
                        printf("Beginning of document \n");
                        break;
                    }

                    if(cursor.Line == 0) {
                        //printf("Detected newline character");
                        cursor.Column--;
                        cursor.Line = text[cursor.Column].size();
                    }
                    else {
                        cursor.Line--;
                    }
                }
                else if(keycode == SDLK_RIGHT) {
                    if(cursor.Column == text.size() - 1 && cursor.Line >= currentTextLine.size()) {
                        printf("End of document \n");
                        break;
                    }

                    if(cursor.Line > currentTextLine.size() - 1) {
                        cursor.Column++;
                        cursor.Line = 0;
                    }
                    else {
                        cursor.Line++;
                    }
                }
                else if(keycode == SDLK_UP) {
                    if(cursor.Column == 0) {
                        printf("First column of document \n");
                        break;
                    }
                    cursor.Column--;
                    if(text[cursor.Column].size() < cursor.Line) {
                        cursor.Line = text[cursor.Column].size();
                    }
                }
                else if(keycode == SDLK_DOWN) {
                    if(cursor.Column == text.size() - 1) {
                        if(cursor.Line < currentTextLine.size()) {
                            cursor.Line = currentTextLine.size();
                        }
                        printf("Last column of document \n");
                        break;
                    }
                    cursor.Column++;
                    if(text[cursor.Column].size() < cursor.Line) {
                        cursor.Line = text[cursor.Column].size();
                    }
                }
                
            }
        }
        printf("Line; %d \n", cursor.Line);
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

    // Render each line of text
    for (size_t i = 0; i < text.size(); ++i) {
        const auto& lineRope = text[i];
        std::string line(lineRope.c_str(), lineRope.size());
        if (line.empty())
            line = " "; // to render even empty lines correctly

        SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font->get(), line.c_str(), textColor, 0);
        if (surface == nullptr) {
            SDL_Log("Unable to create text surface: %s", SDL_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
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

    // Render cursor
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int cursorPosX = currentRect.x + (letterWidth * cursor.Line);
    int cursorPosY = currentRect.y + (cursor.Column * spaceBetweenLine);

    SDL_RenderDrawLine(renderer, cursorPosX, cursorPosY, cursorPosX, cursorPosY + spaceBetweenLine);
}
