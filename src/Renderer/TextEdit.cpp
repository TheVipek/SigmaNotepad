//
// Created by thevi on 5/6/2024.
//

#include "Renderer/TextEdit.h"

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
                //const Uint8 *state = SDL_GetKeyboardState(NULL);

                if (keycode == SDLK_BACKSPACE && !text.empty()) {
                    text.pop_back();
                } else if (keycode == SDLK_TAB) {
                    text += "\t";
                } else if (keycode == SDLK_RETURN) {
                    text += "\n";
                } else if (keycode == SDLK_SPACE) {
                    text += " ";
                }
                break;
            }
            case SDL_TEXTINPUT: {
                // Append the text from input
                text += e.text.text;
                break;
            }
        }
        // if(e.type == SDL_KEYDOWN) {
        //     SDL_KeyboardEvent* keyEvent = (SDL_KeyboardEvent*)&e;
        //     SDL_Keycode keyCode = keyEvent->keysym.sym;
        //     SDL_GetModState();
        //     printf("keycode; %d \n", keyCode);
        //     if(keyCode == 8) {
        //         text.pop_back();
        //     }
        //     else if(keyCode == 9) {
        //         text = text + "\t";
        //     }
        //     else if(keyCode == 13) {
        //         text = text + "\n";
        //     }
        //     else if(keyCode == 32) {
        //         text = text + " ";
        //     }
        //     else if(keyCode >= 0x21 && keyCode <= 0x7A) {
        //         const char* keyName = SDL_GetKeyName(keyCode);
        //         if(keyName == "Space") {
        //             text = text + " ";
        //         }
        //         else if(keyName == "Return") {
        //             text = text + "\n";
        //         }
        //         else {
        //
        //             text = text + keyName;
        //         }
        //         printf("writing; '%d' \n", keyName);
        //     }


        // }
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
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    //SDL_Log("Text rendered at: %d, %d, %d, %d", textRect.x, textRect.y, textRect.w, textRect.h);
}