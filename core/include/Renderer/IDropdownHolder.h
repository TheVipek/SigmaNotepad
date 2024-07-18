//
// Created by thevi on 7/17/2024.
//

#ifndef IDROPDOWNHOLDER_H
#define IDROPDOWNHOLDER_H
#include "DropdownItem.h"

class IDropdownHolder {
public:
    IDropdownHolder() {

    };
    ~IDropdownHolder() {

    };
    virtual void addElement(std::shared_ptr<DropdownItem> item) = 0;
    virtual void removeElement(std::shared_ptr<DropdownItem> item) = 0;
    virtual void removeElement(int index) = 0;
protected:
    std::vector<std::shared_ptr<DropdownItem>> items;
};
#endif //IDROPDOWNHOLDER_H
