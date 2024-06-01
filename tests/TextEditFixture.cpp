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

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
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
    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
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
    obj->setActive(true);

    const char testText[] = "Hello World";
    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }

    for(size_t i = 0; i < sizeof(testText); i++) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }

    ASSERT_EQ(obj->getCursor().Position, 0);
}
TEST_F(TextEditFixture, HandleLeftArrowWithSwitchToPreviousLineTest) {
    obj->setActive(true);

    const char testText[] = "Hello World\nasdf";
    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }

    for(size_t i = 0; i < sizeof(testText); i++) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }

    ASSERT_EQ(obj->getCursor().Position, 0);
}
TEST_F(TextEditFixture, HandleRightArrowOneLineTest) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);
    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().Position, 0);

    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_RIGHT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);

}
TEST_F(TextEditFixture, HandleRightArrowWithSwitchToNextLineTest) {
    obj->setActive(true);

    const char testText[] = "Hello World\nasdf";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);
    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().Position, 0);

    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_RIGHT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);
}
TEST_F(TextEditFixture, HandleUpArrow) {
    obj->setActive(true);

    const char testText[] = "Hello World\nasdf";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);
    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.Position, 4); // second line is asdf, so it should move to 4 position of first line
}
TEST_F(TextEditFixture, HandleUpArrowWhenOneLine) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);
    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.Position,  0);
}
TEST_F(TextEditFixture, HandleUpArrowWhenPreviousLineIsShorter) {
    obj->setActive(true);

    const char testText[] = "asdfgh\nHello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);

    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.Position,  6); // previous line is shorter, so it should go to the last position
}
TEST_F(TextEditFixture, HandleDownArrow) {
    obj->setActive(true);

    const char testText[] = "asdfgh\nHello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().Position, sizeof(testText) - 1);

    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_DOWN;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.Position,  6); // previous line is shorter, so it should go to the last position
}
TEST_F(TextEditFixture, HandleDownArrowWhenOneLine) {

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