//
// Created by thevi on 5/3/2024.
//

#ifndef IWINDOWRENDERINGMANAGER_H
#define IWINDOWRENDERINGMANAGER_H


class SigmaRenderableObject;

class IWindowRenderingManager {
public:
    virtual void AddRenderableObject(SigmaRenderableObject* obj) = 0;
    virtual void RemoveRenderableObject(SigmaRenderableObject* obj) = 0;
    virtual ~IWindowRenderingManager() {}
};

#endif //IWINDOWRENDERINGMANAGER_H
