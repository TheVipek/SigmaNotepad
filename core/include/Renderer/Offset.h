//
// Created by thevi on 5/6/2024.
//

#ifndef OFFSET_H
#define OFFSET_H
struct Offset {
    Offset(int l, int t, int r, int b) : Left(l), Top(t), Right(r), Bottom(b) {};
    int Left;
    int Top;
    int Right;
    int Bottom;
};
#endif //OFFSET_H
