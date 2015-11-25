#include "eventsMain.h"
#include "cEventManager.h"

StormFramework::cEventManager eventManager;

int S_InitEventManager() {
    if (S_GetGraphicsApi() == -1) {
        return -1;
    }
    eventManager.SetApi(S_GetGraphicsApi());
    return 1;
}

StormFramework::cEventManager &S_GetEventManager() {
    return eventManager;
}

bool S_IsKeyDown(StormKey key) {
    return eventManager.GetInput()->IsKeyDown(key);
}
bool S_IsKeyUp(StormKey key) {
    return eventManager.GetInput()->IsKeyUp(key);
}
sPoint &S_GetMouseLoc() {
    return eventManager.GetInput()->GetMouseLoc();
}
int S_GetMouseScroll() {
    return eventManager.GetInput()->GetMouseScroll();
}
bool S_IsMouseLeft() {
    return eventManager.GetInput()->IsMouseLeft();
}
bool S_IsMouseRight() {
    return eventManager.GetInput()->IsMouseRight();
}
bool S_IsMouseMiddle() {
    return eventManager.GetInput()->IsMouseMiddle();
}
void S_StartTextInput() {
    eventManager.GetInput()->StartTextInput();
}
void S_StopTextInput() {
    eventManager.GetInput()->StopTextInput();
}
bool S_IsTextInput() {
    return eventManager.GetInput()->IsTextInput();
}
std::string &S_GetTextInput() {
    return eventManager.GetInput()->GetText();
}
void S_SetTextInput(const std::string &text) {
    eventManager.GetInput()->SetText(text);
}