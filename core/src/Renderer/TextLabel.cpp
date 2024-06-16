//
// Created by thevi on 5/2/2024.
//

#include <SDL_events.h>
#include <Renderer/TextLabel.h>


void TextLabel::handleEvent(const SDL_Event &e) {
    if(!enabled)
        return;

    SigmaRenderableObject::handleEvent(e);
}


void TextLabel::render(SDL_Renderer* renderer) {
    if(!visible)
        return;

    SigmaRenderableObject::render(renderer);

    if(font->get() == nullptr || text.empty())
        return;
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font->get(), text.c_str(), textColor, 0);
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

    SDL_Rect dest = { currentRect.x, currentRect.y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

}
