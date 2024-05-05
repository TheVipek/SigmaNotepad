//
// Created by thevi on 5/2/2024.
//

#include <SDL_events.h>
#include <Renderer/TextLabel.h>

void TextLabel::initFont(const std::string& fPath, const int fSize) {
    if(font != nullptr) {
        //Ignore, font has been initialized already
    }
    else {
        font = std::make_unique<Font>(fPath, fSize);
    }
}

void TextLabel::handleEvent(const SDL_Event &e) {
    }


void TextLabel::render(SDL_Renderer* renderer) {
    if(!visible)
        return;

    if(font->get() == nullptr)
        return;

    SDL_Surface* surface = TTF_RenderText_Solid(font->get(), text.c_str(), textColor);
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
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

}
