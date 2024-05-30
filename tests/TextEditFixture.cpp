//
// Created by thevi on 5/27/2024.
//

#include "TextEditFixture.h"


TEST_F(TextEditFixture, InsertTextTest) {
    const char testText[] = "Hello World";
    SDL_Event event;
    event.type = SDL_TEXTINPUT;
    strncpy(event.text.text, testText, sizeof(event.text.text) - 1);
    event.text.text[sizeof(event.text.text) - 1] = '\0'; // Ensure null-termination
    obj->setActive(true);
    obj->handleEvent(event);
    ASSERT_STREQ(obj->getText().c_str(), testText);
}
TEST_F(TextEditFixture, RemoveTextTest) {
    obj->setActive(true);
    const char testText[] = "Hello World";
    for(char c : testText) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = c;
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    for(size_t i = 0; i < sizeof(testText); i++) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_BACKSPACE;
        obj->handleEvent(event3);
    }

    ASSERT_STREQ(obj->getText().c_str(), "");
}
TEST_F(TextEditFixture, RemoveTextWithHigherThanCountTest) {
    obj->setActive(true);
    const char testText[] = "Hello World";
    for(char c : testText) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = c;
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    for(size_t i = 0; i < sizeof(testText) + 10; i++) { // to test if it wont throw any error
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_BACKSPACE;
        obj->handleEvent(event3);
    }

    ASSERT_STREQ(obj->getText().c_str(), "");
}
TEST_F(TextEditFixture, HandleLeftArrowOneLineTest) {

}
TEST_F(TextEditFixture, HandleLeftArrowWithSwitchToPreviousLineTest) {

}
TEST_F(TextEditFixture, HandleLeftArrowWhenBeginningOfDocumentTest) {

}
TEST_F(TextEditFixture, HandleRightArrowOneLineTest) {

}
TEST_F(TextEditFixture, HandleRightArrowWithSwitchToNextLineTest) {

}
TEST_F(TextEditFixture, HandleLeftArrowWhenEndOfDocumentTest) {

}
TEST_F(TextEditFixture, HandleUpArrow) {

}
TEST_F(TextEditFixture, HandleUpArrowWhenFirstLine) {

}
TEST_F(TextEditFixture, HandleUpArrowWhenPreviousLineIsShorter) {

}
TEST_F(TextEditFixture, HandleDownArrow) {

}
TEST_F(TextEditFixture, HandleDownArrowWhenLastLine) {

}
TEST_F(TextEditFixture, HandleDownArrowWhenNextLineIsShorter) {

}
TEST_F(TextEditFixture, HandleCTRLArrowLeft) {

}
TEST_F(TextEditFixture, HandleCTRLArrowLeftWhenEmpty) {

}
TEST_F(TextEditFixture, HandleCTRLArrowRight) {

}
TEST_F(TextEditFixture, HandleCTRLArrowRightWhenEmpty) {

}
TEST_F(TextEditFixture, HandleSHIFTArrowLeft) {

}
TEST_F(TextEditFixture, HandleSHIFTArrowRight) {

}
TEST_F(TextEditFixture, HandleSHIFTArrowUp) {

}
TEST_F(TextEditFixture, HandleSHIFTArrowDown) {

}
TEST_F(TextEditFixture, HandleSelectionRefreshment) {

}
TEST_F(TextEditFixture, HandleSHIFT_CTRLArrowLeft) {

}
TEST_F(TextEditFixture, HandleSHIFT_CTRLArrowRight) {

}