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

    ASSERT_EQ(obj->getCursor().getPos(), 0);
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

    ASSERT_EQ(obj->getCursor().getPos(), 0);
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().getPos(), 0);

    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_RIGHT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().getPos(), 0);

    for(size_t i = 0; i < sizeof(testText) - 1; ++i) {
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_RIGHT;
        obj->handleEvent(event3);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.getPos(), 4); // second line is asdf, so it should move to 4 getPos() of first line
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.getPos(),  0);
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.sym = SDLK_UP;
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    ASSERT_EQ(cursor.getPos(),  6); // previous line is shorter, so it should go to the last getPos()
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    while(obj->getCursor().getPos() > 6) {
        SDL_Event event;
        event.type = SDL_KEYDOWN;
        event.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event);
    }
    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_DOWN;
    obj->handleEvent(event);

    ASSERT_EQ(obj->getCursor().getPos(),  13); // next line is shorted so it should go to the same getPos() in next line (6+6+1), where 1 is new line character
}
TEST_F(TextEditFixture, HandleDownArrowWhenOneLine) {
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

    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event2;
    event2.type = SDL_KEYDOWN;
    event2.key.keysym.sym = SDLK_LEFT;
    event2.key.keysym.mod = KMOD_NONE;
    obj->handleEvent(event2);
    obj->handleEvent(event2);

    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 3);


    event2.type = SDL_KEYDOWN;
    event2.key.keysym.sym = SDLK_DOWN;
    obj->handleEvent(event2);


    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1); // previous line is shorter, so it should go to the last getPos()
}
TEST_F(TextEditFixture, HandleDownArrowWhenNextLineIsShorter) {
    obj->setActive(true);

    const char testText[] = "Hello World\nasdfgh";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    while(obj->getCursor().getPos() > 10) {
        SDL_Event event;
        event.type = SDL_KEYDOWN;
        event.key.keysym.sym = SDLK_LEFT;
        obj->handleEvent(event);
    }
    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_DOWN;
    obj->handleEvent(event);

    ASSERT_EQ(obj->getCursor().getPos(),  sizeof(testText) - 1); // we're going to last character of next line
}
TEST_F(TextEditFixture, HandleCTRLArrowLeft) {
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_LEFT;
    event.key.keysym.mod = KMOD_CTRL;
    obj->handleEvent(event);

    ASSERT_EQ(obj->getCursor().getPos(),  (sizeof(testText) - 1) - 5); // 5 is length of 'World'
}
TEST_F(TextEditFixture, HandleCTRLArrowLeftWhenEmpty) {
    obj->setActive(true);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_LEFT;
    event.key.keysym.mod = KMOD_CTRL;
    obj->handleEvent(event);

    ASSERT_EQ(obj->getCursor().getPos(),  0); // 5 is length of 'World'
}
TEST_F(TextEditFixture, HandleCTRLArrowRight) {
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
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_LEFT;
    event.key.keysym.mod = KMOD_CTRL;
    obj->handleEvent(event);
    ASSERT_EQ(obj->getCursor().getPos(),  (sizeof(testText) - 1) - 5); // 5 is length of 'World'

    SDL_Event event2;
    event2.type = SDL_KEYDOWN;
    event2.key.keysym.sym = SDLK_RIGHT;
    event2.key.keysym.mod = KMOD_CTRL;
    obj->handleEvent(event2);
    ASSERT_EQ(obj->getCursor().getPos(),  (sizeof(testText) - 1));
}
TEST_F(TextEditFixture, HandleCTRLArrowRightWhenEmpty) {
    obj->setActive(true);

    SDL_Event event2;
    event2.type = SDL_KEYDOWN;
    event2.key.keysym.sym = SDLK_RIGHT;
    event2.key.keysym.mod = KMOD_CTRL;
    obj->handleEvent(event2);
    ASSERT_EQ(obj->getCursor().getPos(),  0);
}
TEST_F(TextEditFixture, HandleSHIFTArrowLeft) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event2;
    event2.type = SDL_KEYDOWN;
    event2.key.keysym.sym = SDLK_LEFT;
    event2.key.keysym.mod = KMOD_SHIFT;
    obj->handleEvent(event2);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  (sizeof(testText) - 1) - 1);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, sizeof(testText) - 1);
    ASSERT_EQ(selection.SelectionEnd, (sizeof(testText) - 1) - 1);
}
TEST_F(TextEditFixture, HandleSHIFTArrowRight) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event2;
    event2.type = SDL_KEYDOWN;
    event2.key.keysym.mod = KMOD_NONE;
    event2.key.keysym.sym = SDLK_LEFT;

    obj->handleEvent(event2);
    obj->handleEvent(event2);
    obj->handleEvent(event2);


    SDL_Event event3;
    event3.type = SDL_KEYDOWN;
    event3.key.keysym.mod = KMOD_SHIFT;
    event3.key.keysym.sym = SDLK_RIGHT;

    obj->handleEvent(event3);
    obj->handleEvent(event3);
    obj->handleEvent(event3);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  (sizeof(testText) - 1));
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, (sizeof(testText) - 1) - 3);
    ASSERT_EQ(selection.SelectionEnd, (sizeof(testText) - 1));
}
TEST_F(TextEditFixture, HandleSHIFTArrowUpOneLine) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_SHIFT;
    event.key.keysym.sym = SDLK_UP;

    obj->handleEvent(event);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  0);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, (sizeof(testText) - 1));
    ASSERT_EQ(selection.SelectionEnd, 0);
}
TEST_F(TextEditFixture, HandleSHIFTArrowUpMultiline) {
    obj->setActive(true);

    const char testText[] = "Hello World\nHello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);

    SDL_Event event;
    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_SHIFT;
    event.key.keysym.sym = SDLK_UP;

    obj->handleEvent(event);
    obj->handleEvent(event);
    //invoking twice, beacuse first get second line fully covered and then second is filling the rest of characters

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  0);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, (sizeof(testText) - 1));
    ASSERT_EQ(selection.SelectionEnd, 0);
}
TEST_F(TextEditFixture, HandleSHIFTArrowDownOneLine) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);



    SDL_Event event;

    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_NONE;
    event.key.keysym.sym = SDLK_UP;

    obj->handleEvent(event);

    event.key.keysym.mod = KMOD_SHIFT;
    event.key.keysym.sym = SDLK_DOWN;

    obj->handleEvent(event);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  sizeof(testText) - 1);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, 0);
    ASSERT_EQ(selection.SelectionEnd, (sizeof(testText) - 1));
}
TEST_F(TextEditFixture, HandleSHIFTArrowDownMultiline) {
    obj->setActive(true);

    const char testText[] = "Hello World\nHello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);



    SDL_Event event;

    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_NONE;
    event.key.keysym.sym = SDLK_UP;

    obj->handleEvent(event);
    obj->handleEvent(event);
    //invoking twice, go to the beginning

    event.key.keysym.mod = KMOD_SHIFT;
    event.key.keysym.sym = SDLK_DOWN;

    obj->handleEvent(event);
    obj->handleEvent(event);
    //invoking twice, go to cover everything until very end

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  sizeof(testText) - 1);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, 0);
    ASSERT_EQ(selection.SelectionEnd, (sizeof(testText) - 1));
}
TEST_F(TextEditFixture, HandleSHIFT_CTRLArrowLeft) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);



    SDL_Event event;

    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_SHIFT;
    // event.key.keysym.sym;
    obj->handleEvent(event);

    event.key.keysym.mod = KMOD_SHIFT | KMOD_CTRL;
    event.key.keysym.sym = SDLK_LEFT;
    obj->handleEvent(event);
    obj->handleEvent(event);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  5);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, (sizeof(testText) - 1));
    ASSERT_EQ(selection.SelectionEnd, 5);
}
TEST_F(TextEditFixture, HandleSHIFT_CTRLArrowRight) {
    obj->setActive(true);

    const char testText[] = "Hello World";

    for(int  i = 0; i < sizeof(testText) - 1 ; ++i) {
        printf("inserting: %c \n", testText[i]);
        SDL_Event event;
        event.type = SDL_TEXTINPUT;
        event.key.keysym.mod = KMOD_NONE;
        event.text.text[0] = testText[i];
        event.text.text[1] = '\0';
        obj->handleEvent(event);
    }
    ASSERT_EQ(obj->getCursor().getPos(), sizeof(testText) - 1);
    
    SDL_Event event;

    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_CTRL;
    event.key.keysym.sym = SDLK_LEFT;
    obj->handleEvent(event);

    event.type = SDL_KEYDOWN;
    event.key.keysym.mod = KMOD_SHIFT;
    event.key.keysym.sym = SDLK_UNKNOWN;
    obj->handleEvent(event);

    event.key.keysym.mod = KMOD_SHIFT | KMOD_CTRL;
    event.key.keysym.sym = SDLK_RIGHT;
    obj->handleEvent(event);

    auto cursor = obj->getCursor();
    auto selection = obj->getSelection();
    ASSERT_EQ(cursor.getPos(),  sizeof(testText) - 1);
    ASSERT_EQ(selection.IsSelecting, true);
    ASSERT_EQ(selection.SelectionStart, 6);
    ASSERT_EQ(selection.SelectionEnd, sizeof(testText) - 1);
}