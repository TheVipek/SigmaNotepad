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
        if(e.type == SDL_KEYDOWN) {
            SDL_KeyboardEvent* keyEvent = (SDL_KeyboardEvent*)&e;
            SDL_Keycode keyCode = keyEvent->keysym.sym;
            const char* keyName = SDL_GetKeyName(keyCode);
            printf("writing; '%d'", keyName);
            text = text + keyName;
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
    SDL_Surface* surface = TTF_RenderText_Blended(font->get(), text.c_str(), textColor);
    printf("w; %d  h; %d", surface->w, surface->h);
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
    SDL_RenderCopy(renderer, texture, NULL, &currentRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);




    // // Set the background color and fill the rectangle
    // SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    // SDL_RenderFillRect(renderer, &baseRect);
    //
    // // Font rendering
    // if (font->get() == nullptr || strlen(text.c_str()) == 0)
    //     return;
    //
    // // Determine text size
    // int textWidth = 0, textHeight = 0;
    // TTF_SizeText(font->get(), text.c_str(), &textWidth, &textHeight);
    //
    // // Adjust text size if necessary (simple scaling example)
    // SDL_Rect textRect = baseRect;
    // if (textWidth > baseRect.w || textHeight > baseRect.h) {
    //     float scaleX = baseRect.w / (float)textWidth;
    //     float scaleY = baseRect.h / (float)textHeight;
    //     float scale = std::min(scaleX, scaleY);
    //     textWidth *= scale;
    //     textHeight *= scale;
    //     textRect.x += (baseRect.w - textWidth) / 2;  // Center the text horizontally
    //     textRect.y += (baseRect.h - textHeight) / 2; // Center the text vertically
    //     textRect.w = textWidth;
    //     textRect.h = textHeight;
    // }
    //
    // // Create surface and texture for the text
    // SDL_Surface* surface = TTF_RenderText_Blended(font->get(), text.c_str(), textColor);
    // if (surface == nullptr) {
    //     SDL_Log("Unable to create text surface: %s", SDL_GetError());
    //     return;
    // }
    //
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // if (texture == nullptr) {
    //     SDL_Log("Unable to create texture: %s", SDL_GetError());
    //     SDL_FreeSurface(surface);
    //     return;
    // }
    //
    // // Render the texture to the specified rectangle
    // SDL_RenderCopy(renderer, texture, NULL, &textRect);
    //
    // // Cleanup
    // SDL_DestroyTexture(texture);
    // SDL_FreeSurface(surface);
}