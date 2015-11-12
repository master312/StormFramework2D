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
double tmp = 0.0;
uint8_t tmpo = 0;
void cTestState::OnGraphicsTick() {
    tmp -= 0.4;
    S_TextureModAngle(m_TestTexture, tmp);
    S_TextureModOpacity(m_TestTexture, tmpo);
    tmpo++;
    if(tmpo == 100){
        tmpo = 0;
    }
    S_DrawTexture(m_TestTexture, 100, 100);
	S_DrawText("Ovo je sve matrix!", 200, 250);
}
void cTestState::OnLogicTick(uint32_t &delta) {
	//std::cout << "Logic delta: " << delta << std::endl;
}
void cTestState::OnEvent() {
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
