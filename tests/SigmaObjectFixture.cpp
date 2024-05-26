//
// Created by thevi on 5/26/2024.
//

#include "SigmaObjectFixture.h"


TEST_F(SigmaObjectFixture, AnchorTopLeftTest) {
    obj->setAnchor(Anchor::TopLeft);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(), defaultRect.x);
    EXPECT_EQ(obj->getY(), defaultRect.y);
}

TEST_F(SigmaObjectFixture, AnchorTopTest) {
    obj->setAnchor(Anchor::Top);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(), defaultRect.x + (defaultScreenWidth/2) - defaultRect.w);
    EXPECT_EQ(obj->getY(), defaultRect.y);
}

TEST_F(SigmaObjectFixture, AnchorTopRightTest) {
    obj->setAnchor(Anchor::TopRight);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(), defaultScreenWidth - defaultRect.w);
    EXPECT_EQ(obj->getY(), defaultRect.y);
}

TEST_F(SigmaObjectFixture, AnchorBottomLeft) {
    obj->setAnchor(Anchor::BottomLeft);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(), defaultRect.y + defaultScreenHeight - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorBottom) {
    obj->setAnchor(Anchor::Bottom);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x + (defaultScreenWidth / 2) - defaultRect.w);
    EXPECT_EQ(obj->getY(), defaultRect.y + defaultScreenHeight - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorBottomRight) {
    obj->setAnchor(Anchor::BottomRight);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultScreenWidth - defaultRect.w);
    EXPECT_EQ(obj->getY(), defaultRect.y + defaultScreenHeight - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorLeft) {
    obj->setAnchor(Anchor::Left);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  (defaultScreenHeight / 2) - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorRight) {
    obj->setAnchor(Anchor::Right);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(), defaultScreenWidth - defaultRect.w);
    EXPECT_EQ(obj->getY(), (defaultScreenHeight / 2) - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorCenter) {
    obj->setAnchor(Anchor::Center);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  (defaultScreenWidth / 2) - defaultRect.w);
    EXPECT_EQ(obj->getY(), (defaultScreenHeight / 2) - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorFullScreen) {
    obj->setAnchor(Anchor::FullScreen);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultScreenWidth - defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultScreenHeight - defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorFullWidthTop) {
    obj->setAnchor(Anchor::FullWidthTop);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultScreenWidth);
    EXPECT_EQ(obj->getHeight(), defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorFullWidthCenter) {
    obj->setAnchor(Anchor::FullWidthCenter);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  0);
    EXPECT_EQ(obj->getY(),  (defaultScreenHeight / 2) - defaultRect.h);
    EXPECT_EQ(obj->getWidth(), defaultScreenWidth);
    EXPECT_EQ(obj->getHeight(), defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorFullWidthBottom) {
    obj->setAnchor(Anchor::FullWidthBottom);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  defaultScreenHeight - defaultRect.h);
    EXPECT_EQ(obj->getWidth(), defaultScreenWidth);
    EXPECT_EQ(obj->getHeight(), defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorFullHeightLeft) {
    obj->setAnchor(Anchor::FullHeightLeft);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultScreenHeight);
}

TEST_F(SigmaObjectFixture, AnchorFullHeightCenter) {
    obj->setAnchor(Anchor::FullHeightCenter);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  (defaultScreenWidth / 2) - defaultRect.w);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultScreenHeight);
}

TEST_F(SigmaObjectFixture, AnchorFullHeightRight) {
    obj->setAnchor(Anchor::FullHeightRight);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultScreenWidth - defaultRect.w);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultScreenHeight);
}

TEST_F(SigmaObjectFixture, AnchorNone) {
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x);
    EXPECT_EQ(obj->getY(),  defaultRect.y);
    EXPECT_EQ(obj->getWidth(), defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultRect.h);
}

TEST_F(SigmaObjectFixture, AnchorNoneWithOffset) {
    Offset offset = { 15, 15, 0, 0};
    obj->setOffset(offset);
    obj->handlePosition(defaultScreenWidth, defaultScreenHeight);

    EXPECT_EQ(obj->getX(),  defaultRect.x + 15);
    EXPECT_EQ(obj->getY(),  defaultRect.y - 15);
    EXPECT_EQ(obj->getWidth(), defaultRect.w);
    EXPECT_EQ(obj->getHeight(), defaultRect.h);
}