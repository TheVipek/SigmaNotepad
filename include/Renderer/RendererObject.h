//
// Created by thevi on 4/30/2024.
//

#ifndef RENDEREROBJECT_H
#define RENDEREROBJECT_H

#include <SDL_events.h>
#include <SDL_rect.h>
#include <string>

class RendererObject {
    public:
        RendererObject(int x, int y, int w, int h, bool enabled, bool visible);
        int getX() const { return rect.x;}
        int getY() const { return rect.y;}
        int getWidth() const { return rect.w; }
        int getHeight() const { return rect.h; }

        void setEnabled(bool enabled) { this->enabled = enabled; }
        void setRect(SDL_Rect rect) { this->rect = rect; }
        void setVisibility(bool visible) { this->visible = visible; }


        virtual void handleEvent(SDL_Event& e) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
    protected:
        SDL_Rect rect;
        bool enabled;
        bool visible;

};



#endif //RENDEREROBJECT_H
