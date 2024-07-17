//
// Created by thevi on 7/17/2024.
//

#ifndef IEDITFIELD_H
#define IEDITFIELD_H
#include <ext/functional>

class IEditField {
public:
    ~IEditField() {
        onTextLengthChangedCallbacks.clear();
    }
    void registerToOnTextLengthChanged(std::function<void(int)> callback) {
        onTextLengthChangedCallbacks.push_back(callback);
    }
    void unregisterToOnTextLengthChanged(std::function<void(int)> callback) {
        auto it = std::find_if(onTextLengthChangedCallbacks.begin(), onTextLengthChangedCallbacks.end(),
                                    [&callback](const std::function<void(int)>& elem) {
                                        return callback.target<void(int)>() == elem.target<void(int)>();
                                    });

        if (it != onTextLengthChangedCallbacks.end()) {
            onTextLengthChangedCallbacks.erase(it);
        }
    }
protected:
    std::vector<std::function<void(int length)>> onTextLengthChangedCallbacks;

    virtual void notifyOnTextLengthChanged(int length) {
        for(auto& callback : onTextLengthChangedCallbacks) {
            callback(length);
        }
    }
};


#endif //IEDITFIELD_H
