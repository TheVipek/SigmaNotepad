//
// Created by thevi on 7/17/2024.
//

#ifndef NUMERICLABEL_H
#define NUMERICLABEL_H
#include "IBackground.h"
#include "IEditField.h"
#include "IText.h"
#include "SigmaRenderableObject.h"

class NumericLabel : public SigmaRenderableObject, public IText<int>, public IBackground, public IEditField {
public:
    NumericLabel(SDL_Rect &rect, Window *_owner)
        : SigmaRenderableObject(rect, _owner)
    {
        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
    }
    ~NumericLabel() {

    }

    void setText(const int text) override {
        this->text = text;
    }
    int getText() override {
        return text;
    }

    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
};

#endif //NUMERICLABEL_H
