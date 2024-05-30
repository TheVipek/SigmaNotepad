//
// Created by thevi on 5/6/2024.
//

#ifndef ITEXTALIGMENT_H
#define ITEXTALIGMENT_H

#include "TextHorizontalAligment.h"
#include "TextVerticalAligment.h"

class ITextAligment {
public:
    virtual ~ITextAligment() = default;
    virtual void setHorizontalAligment(const HorizontalAligment ha) { horizontal_aligment = ha; }
    virtual void setVerticalAligment(const VerticalAligment va) { vertical_aligment = va; }

protected:
    HorizontalAligment          horizontal_aligment = HorizontalAligment::Top;
    VerticalAligment            vertical_aligment = VerticalAligment::Left;
};

#endif //ITEXTALIGMENT_H
