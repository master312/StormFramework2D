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
    S_DrawTexture(m_TestTexture, 100, 100);
	S_DrawText("Ovo je sve matrix!", 200, 250);
}
void cTestState::OnLogicTick(uint32_t &delta) {
	//std::cout << "Logic delta: " << delta << std::endl;
}
void cTestState::OnEvent(uint32_t &event) {
	std::cout << "Event " << std::endl;
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