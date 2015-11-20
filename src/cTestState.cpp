#include "cTestState.h"


cTestState::cTestState() {
	std::cout << "Created " << std::endl;
}
cTestState::~cTestState() {
	
}
void cTestState::OnInit() {
    m_TestTexture = S_LoadTexture("asdf.png");
	std::cout << "Inited " << std::endl;
}
void cTestState::OnGraphicsTick() {

}
void cTestState::OnLogicTick(uint32_t &delta) {
	//std::cout << "Logic delta: " << delta << std::endl;
}
void cTestState::OnEvent() {
    if (S_IsMouseLeft()) {
        S_TextureModPos(m_TestTexture, S_GetMouseLoc());
    }
    if (S_IsKeyDown(StormKey::KEY_c)) {
        S_ClearScreen();
    }
}
void cTestState::OnPause() {
	std::cout << "Pause " << std::endl;
}
void cTestState::OnResume() {
	std::cout << "Resume " << std::endl;
}
void cTestState::OnShutdown() {
	std::cout << "Shutdown " << std::endl;
}

int cTestState::TestCBMethod() {
    std::cout << "Dragan called at " << STORM_TIME << std::endl;
    return 777;
}