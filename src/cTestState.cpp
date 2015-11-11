#include "cTestState.h"


cTestState::cTestState() {
	std::cout << "Created " << std::endl;
}
cTestState::~cTestState() {
	
}
void cTestState::OnInit() {
	std::cout << "Inited " << std::endl;
}
void cTestState::OnGraphicsTick() {
	std::cout << "Grephics " << std::endl;
}
void cTestState::OnLogicTick(uint32_t &delta) {
	std::cout << "Logic delta: " << delta << std::endl;
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