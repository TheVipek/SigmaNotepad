//
// Created by thevi on 4/30/2024.
//

#ifndef TEXTLABEL_H
#define TEXTLABEL_H


#include <memory>
#include <utility>

#include "SigmaRenderableObject.h"
#include "TextHorizontalAligment.h"
#include "TextVerticalAligment.h"
#include "SDL_ttf.h"
#include "Font.h"


class TextLabel : public SigmaRenderableObject {

public:
    TextLabel(const SDL_Rect& rect, std::shared_ptr<IWindowRenderingManager> targetWindow, const bool enabled, const bool visible, const std::string& text)
        : SigmaRenderableObject(rect, enabled, visible, targetWindow), text(text) {

        initFont(DEFAULT_FONTP, DEFAULT_FONTS);
    }


    virtual void setText(const std::string& text) { this->text = text; }
    virtual std::string getText() { return text;}

    virtual void setHorizontalAligment(const HorizontalAligment ha) { horizontal_aligment = ha; }
    virtual void setVerticalAligment(const VerticalAligment va) { vertical_aligment = va; }

    virtual void initFont(const std::string& fPath, const int fSize);



    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
protected:

    SDL_Color                   textColor = { 0, 0, 0, 255 };

    std::unique_ptr<Font>       font;

    std::string                 text;
    HorizontalAligment          horizontal_aligment = HorizontalAligment::Top;
    VerticalAligment            vertical_aligment = VerticalAligment::Left;

    const std::string DEFAULT_FONTP = "assets/defaultFonts/OpenSans_Condensed-Medium.ttf";
    const int DEFAULT_FONTS = 12;
};

#endif //TEXTLABEL_H
