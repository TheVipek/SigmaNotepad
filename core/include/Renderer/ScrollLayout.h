//
// Created by thevi on 6/4/2024.
//

#ifndef SCROLLLAYOUT_H
#define SCROLLLAYOUT_H

#include "SigmaRenderableObject.h"


class ScrollLayout : SigmaRenderableObject {
public:
    ScrollLayout(SDL_Rect &rect, const std::shared_ptr<IWindowRenderingManager> &targetWindow)
        : SigmaRenderableObject(rect, targetWindow) {
    }

    void render(SDL_Renderer *renderer) override;
    void handleEvent(const SDL_Event &e) override;
    virtual void assign(SigmaRenderableObject* targetObject);

    ~ScrollLayout() {
        assignedObject = nullptr;
    }

protected:
    SigmaRenderableObject*  assignedObject;
    bool                    vertical = true;
    bool                    horizontal = true;
};


#endif //SCROLLLAYOUT_H
