//
// Created by thevi on 7/22/2024.
//

#ifndef SCROLLLAYOUTTEXT_H
#define SCROLLLAYOUTTEXT_H
#include "ScrollLayout.h"
#include "TextEdit.h"

class ScrollLayoutText : ScrollLayout<TextEdit> {
public:
    ScrollLayoutText(float _barSize, SDL_Rect &rect, Window* owner)
      : ScrollLayout<TextEdit>(_barSize,rect, owner) {
        //static_assert(std::is_base_of<TextEdit, ScrollLayout<T>>::value, "T must derive from TextEdit");
    }

    void render(SDL_Renderer *renderer) {
        ScrollLayout::render(renderer);
    }
    void handleEvent(const SDL_Event &e) {
        ScrollLayout::handleEvent(e);
    }
    void assign(TextEdit *targetObject) {
        if(targetObject != nullptr)
            ScrollLayout::assign(targetObject);
    }

protected:
    bool adjustPosition;

};

#endif //SCROLLLAYOUTTEXT_H
