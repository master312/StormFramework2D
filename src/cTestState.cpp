#include "cTestState.h"

using namespace StormFramework;


cTestState::cTestState() {
	std::cout << "Created " << std::endl;
}
cTestState::~cTestState() {
	
}
std::vector<uint32_t> sprites;
void cTestState::OnInit() {
    m_TestTexture = S_CreateGraphics("sprite.png");
    m_TestTextureDva = S_CreateGraphics("sprite.png");
    m_TestTextureTri = S_CreateGraphics("sprite.png");


    S_GraphModZ(m_TestTexture, 1000);

    S_GraphModZ(m_TestTextureDva, 300);
    S_GraphModZ(m_TestTextureTri, 200);
    S_GraphModPos(m_TestTextureDva, 100, 100);
    S_GraphModPos(m_TestTextureTri, 120, 120);
	std::cout << "Inited " << std::endl;
}
void cTestState::OnGraphicsTick() {
    if (S_IsKeyDown(KEY_c)) {
        S_ClearScreen();
    }
}
double tmpAngle = 0.0;
void cTestState::OnLogicTick(uint32_t &delta) {
 //   uint32_t start = STORM_TIME;
    for (uint32_t i = 0; i < sprites.size(); i++) {
        S_GraphModAngle(sprites[i], tmpAngle);
    }
    tmpAngle += 1;
    //std::cout << "TIME: " << (STORM_TIME - start) << std::endl;
}
void cTestState::OnKeyDown(StormKey &key) {
    if (key == KEY_s) {
        std::cout << "Spawning 100 more..." << std::endl;
        for (int i = 0; i < 100; i++) {
            uint32_t tmp = S_CreateGraphics("sprite.png");
            S_GraphModPos(tmp, (rand() % 1000) + 24, 
                                 (rand() % 740) + 28);
            sprites.push_back(tmp);
        }
    } else if (key == KEY_d) {
        std::cout << "DeSpawning..." << std::endl;
        for (int i = 0; i < 100; i++) {
            S_DestroyGraphics(sprites[i]);
            sprites.erase(sprites.begin() + i);
        }
    }
}
void cTestState::OnMouseDown(StormKey &key) {
    if (key == MOUSE_RIGHT) {
        S_GraphModZ(m_TestTexture, 250);
    }
}
void cTestState::OnMouseMotion() {
    if (S_IsMouseLeft()) {
        S_GraphModPos(m_TestTexture, S_GetMouseLoc());
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