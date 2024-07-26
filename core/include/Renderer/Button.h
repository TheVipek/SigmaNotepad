//
// Created by thevi on 4/30/2024.
//



#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <SDL_rect.h>
#include <string>
#include <tr1/functional>

#include "IInteractableColors.h"
#include "SigmaObject.h"
#include "SigmaRenderableObject.h"
#include "TextLabel.h"

class Button : public SigmaRenderableObject, IInteractableColors  {
public:
    Button(SDL_Rect& rect, Window* _owner, const std::string& text)
        : SigmaRenderableObject(rect, _owner) {

        TLabel = std::make_shared<TextLabel>(this->baseRect, _owner);
        _owner->removeEventObject(TLabel.get());
        _owner->removeRenderableObject(TLabel.get());

        TLabel->setText(text);
    }

    std::shared_ptr<TextLabel>  TLabel;
    void handleEvent(const SDL_Event &e) override;
    void render(SDL_Renderer* renderer) override;
    void setRect(const SDL_Rect& rect) override;
    void setAnchor(Anchor anchor) override;
    void setOffset(const Offset &offset) override;
    void registerOnClick(std::function<void()> callback);

protected:

    bool                        isHovered = false;
    bool                        isClicked = false;



    std::vector<std::function<void()>> onClick;
    void notifyOnClick();
    virtual void click();
};



#endif //BUTTON_H
