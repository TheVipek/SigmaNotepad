//
// Created by thevi on 6/18/2024.
//

#ifndef IRENDERFRAME_H
#define IRENDERFRAME_H
class IRenderFrame {
public:
    virtual ~IRenderFrame() = default;
    virtual void renderFrame() = 0;
};
#endif //IRENDERFRAME_H
