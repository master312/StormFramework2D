#include "cTestState.h"


cTestState::cTestState() {
	std::cout << "Created " << std::endl;
}
cTestState::~cTestState() {
	
}
std::vector<uint32_t> sprites;
void cTestState::OnInit() {
    m_TestTexture = S_LoadTexture("sprite.png");
    m_TestTextureDva = S_LoadTexture("sprite.png");
    m_TestTextureTri = S_LoadTexture("sprite.png");


    S_TextureModZ(m_TestTexture, 1000);

    S_TextureModZ(m_TestTextureDva, 300);
    S_TextureModZ(m_TestTextureTri, 200);
    S_TextureModPos(m_TestTextureDva, 100, 100);
    S_TextureModPos(m_TestTextureTri, 120, 120);
	std::cout << "Inited " << std::endl;
}
void cTestState::OnGraphicsTick() {

}
double tmpAngle = 0.0;
void cTestState::OnLogicTick(uint32_t &delta) {
    for (uint32_t i = 0; i < sprites.size(); i++) {
        S_TextureModAngle(sprites[i], tmpAngle);
    }
    tmpAngle += 1;
}
void cTestState::OnEvent() {
    if (S_IsMouseLeft()) {
        S_TextureModPos(m_TestTexture, S_GetMouseLoc());
    }
    if (S_IsMouseRight()) {
        S_TextureModZ(m_TestTexture, 250);
    }
    if (S_IsKeyDown(StormKey::KEY_c)) {
        S_ClearScreen();
    }
    if (S_IsKeyDown(StormKey::KEY_s)) {
        std::cout << "Spawning .." << sprites.size() << " +100" << std::endl;
        for (int i = 0; i < 100; i++) {
            uint32_t tmp = S_LoadTexture("sprite.png");
            S_TextureModPos(tmp, (rand() % 1000) + 24, 
                                 (rand() % 740) + 28);
            sprites.push_back(tmp);
        }
    }
    if (S_IsKeyDown(StormKey::KEY_d)) {
        std::cout << "DeSpawning " << std::endl;
        for (int i = 0; i < 100; i++) {
            S_UnloadTexture(sprites[i]);
            sprites.erase(sprites.begin() + i);
        }
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