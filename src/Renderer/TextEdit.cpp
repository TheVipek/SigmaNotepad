//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"
#include "math.h"



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
            case SDL_KEYDOWN: {
                int keycode = e.key.keysym.sym;

                if (keycode == SDLK_BACKSPACE && !text.empty()) {
                    if(text[text.length() - 1] == '\n') {
                        currentColumn--;
                    }
                    else if(lines[currentColumn] > 0) {
                        lines[currentColumn]--;
                    }
                    text.pop_back();
                } else if (keycode == SDLK_TAB) {
                    text.append("   ");
                    lines[currentColumn]+=3;
                } else if (keycode == SDLK_RETURN) {
                    text.append('\n');
                    if(lines.size() <= currentColumn + 1) {
                        lines.push_back(0);
                    }
                    currentColumn++;
                }


                break;
            }
            case SDL_TEXTINPUT: {
                text.append(e.text.text);
                lines[currentColumn]++;
                break;
            }
        }
    }
}

void TextEdit::render(SDL_Renderer *renderer) {
    if(!visible)
        return;

    SigmaRenderableObject::render(renderer);

    //BG
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderFillRect(renderer, &currentRect);


    //FONT RENDER
    if(font->get() == nullptr || strlen(text.c_str()) == 0)
        return;

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font->get(), text.c_str(), textColor, 0);
    if (surface == nullptr) {
        SDL_Log("Unable to create text surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_Log("Unable to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect = {currentRect.x, currentRect.y,  surface->w , surface->h};


    int spaceBetweenLine = TTF_FontLineSkip(font->get());
    SDL_RenderCopy(renderer, texture, NULL, &textRect);


    int w,h;
    //TTF_SizeUTF8(font->get(), text.c_str(),&w, &h);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int cursorPosX = (currentRect.x + offset.Left) + (letterWidth * lines[currentColumn]);
    int cursorPosY = (currentRect.x + offset.Top) + (currentColumn * spaceBetweenLine);

    SDL_RenderDrawLine(renderer, cursorPosX, cursorPosY, cursorPosX, cursorPosY + spaceBetweenLine);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    //SDL_Log("Text rendered at: %d, %d, %d, %d", textRect.x, textRect.y, textRect.w, textRect.h);
}