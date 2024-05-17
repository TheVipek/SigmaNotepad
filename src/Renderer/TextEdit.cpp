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
                if (cursor.Position.Line == 0)
                    return false;

                std::string beforeCursor(text[cursor.Position.Column].begin(),text[cursor.Position.Column].begin() + cursor.Position.Line);
                std::reverse(beforeCursor.begin(), beforeCursor.end());
                std::regex pattern(R"((\s+|\W+|\w+))");
                std::smatch match;

                if(std::regex_search(beforeCursor, match, pattern)) {
                    if(cursor.Selection.IsSelecting) {
                        //cursor.Selection.SelectionEnd = cursor.Position.Line;
                    }
                    cursor.Position.Line -= match.length();
                }
                return true;
            }
            case SDLK_RIGHT: {
                if(cursor.Position.Line >= text[cursor.Position.Column].size()) {
                    return false;
                }
                std::string beforeCursor(text[cursor.Position.Column].begin() + cursor.Position.Line,text[cursor.Position.Column].end());;
                std::regex pattern(R"((\s+|\W+|\w+))");
                std::smatch match;

                if(std::regex_search(beforeCursor, match, pattern)) {
                    cursor.Position.Line += match.length();
                }
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
                text[cursor.Position.Column].insert(cursor.Position.Line,e.text.text);
                cursor.Position.Line++;
                break;
            }
            case SDL_KEYDOWN: {
                int keycode = e.key.keysym.sym;
                if(SDL_GetModState() & KMOD_SHIFT) {
                    if(!cursor.Selection.IsSelecting) {
                        cursor.Selection.IsSelecting = true;
                        //cursor.Selection.SelectionStart = cursor.
                    }
                }
                handleCTRLEvent(e);

                if(SDL_GetModState() & KMOD_CTRL || SDL_GetModState() & KMOD_SHIFT)
                    return;

                auto& currentTextLine = text[cursor.Position.Column];
                if (keycode == SDLK_BACKSPACE) {
                    printf("BACKSPACE \n");
                    if(currentTextLine.empty()) {
                        if(cursor.Position.Column == 0) {
                            break;
                        }

                        cursor.Position.Column--;
                        cursor.Position.Line = text[cursor.Position.Column].size();
                    }
                    else {
                        cursor.Position.Line--;
                        currentTextLine.erase(cursor.Position.Line, 1);
                    }
                }
                else if (keycode == SDLK_TAB) {
                    currentTextLine.insert(cursor.Position.Line,"   ");
                    cursor.Position.Line+=3;
                }
                else if (keycode == SDLK_RETURN) {
                    //currentTextLine.insert(cursor.Line,"\n");  // no need for it?

                    if(text.size() - 1 == cursor.Position.Column) { // last index
                        //printf("LAST textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                        if(cursor.Position.Line < currentTextLine.size()) {
                            //printf("smaller \n");
                            rope<char> newLineText = currentTextLine.substr(cursor.Position.Line, currentTextLine.size() - cursor.Position.Line);
                            text.push_back(newLineText);

                            rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Position.Line);
                            text[cursor.Position.Column] = modifiedCurrentLine;
                        }
                        else {
                            text.emplace_back();
                        }
                    }
                    else if(text.size() - 1 > cursor.Position.Column) { // between index
                        //printf("BETWEEN textSize %d;cursor.Column %d  \n", text.size(), cursor.Column);
                        if(cursor.Position.Line < currentTextLine.size()) {
                            //printf("smaller \n");
                            rope<char> newLineText = currentTextLine.substr(cursor.Position.Line, currentTextLine.size() - cursor.Position.Line);
                            text.insert(text.begin() + cursor.Position.Column + 1,newLineText);

                            rope<char> modifiedCurrentLine = currentTextLine.substr(0, cursor.Position.Line);
                            text[cursor.Position.Column] = modifiedCurrentLine;
                        }
                        else {
                            //printf("insert between \n");
                            text.insert(text.begin() + cursor.Position.Column + 1, rope<char>(""));
                        }
                    }
                    cursor.Position.Column++;
                    cursor.Position.Line = text[cursor.Position.Column].size();
                }
                else if (keycode == SDLK_LEFT) {
                    if(cursor.Position.Column == 0 && cursor.Position.Line == 0) {
                        printf("Beginning of document \n");
                        break;
                    }

                    if(cursor.Position.Line == 0) {
                        //printf("Detected newline character");
                        cursor.Position.Column--;
                        cursor.Position.Line = text[cursor.Position.Column].size();
                    }
                    else {
                        cursor.Position.Line--;
                    }
                }
                else if(keycode == SDLK_RIGHT) {
                    if(cursor.Position.Column == text.size() - 1 && cursor.Position.Line >= currentTextLine.size()) {
                        printf("End of document \n");
                        break;
                    }

                    if(cursor.Position.Line > currentTextLine.size() - 1) {
                        cursor.Position.Column++;
                        cursor.Position.Line = 0;
                    }
                    else {
                        cursor.Position.Line++;
                    }
                }
                else if(keycode == SDLK_UP) {
                    if(cursor.Position.Column == 0) {
                        printf("First column of document \n");
                        break;
                    }
                    cursor.Position.Column--;
                    if(text[cursor.Position.Column].size() < cursor.Position.Line) {
                        cursor.Position.Line = text[cursor.Position.Column].size();
                    }
                }
                else if(keycode == SDLK_DOWN) {
                    if(cursor.Position.Column == text.size() - 1) {
                        if(cursor.Position.Line < currentTextLine.size()) {
                            cursor.Position.Line = currentTextLine.size();
                        }
                        printf("Last column of document \n");
                        break;
                    }
                    cursor.Position.Column++;
                    if(text[cursor.Position.Column].size() < cursor.Position.Line) {
                        cursor.Position.Line = text[cursor.Position.Column].size();
                    }
                }
                
            }
        }
        printf("Line; %d \n", cursor.Position.Line);
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

    int cursorPosX = currentRect.x + (letterWidth * cursor.Position.Line);
    int cursorPosY = currentRect.y + (cursor.Position.Column * spaceBetweenLine);

    SDL_RenderDrawLine(renderer, cursorPosX, cursorPosY, cursorPosX, cursorPosY + spaceBetweenLine);
}
