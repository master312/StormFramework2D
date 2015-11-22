#include "storm/storm.h"
#include "storm/thirdparty/tinyxml2.h"

#include "cTestState.h"


#ifdef OS_WINDOWS
#undef main
#endif

using namespace tinyxml2;

int main(int argc, char *argv[]) {
    S_SetGraphicsApi(STORM_API_SDL2);
    S_InitAll();
    S_PushLayer(new cTestState());

    S_StartMain();


/*    uint32_t asdf = S_LoadTexture("asdf.png");

    sRect rct;
    rct.x = 70;
    rct.y = 5;
    rct.w = 100;
    rct.h = 100;

    uint32_t sectId = S_CreateSection(asdf, rct);


    StormAnimation tmpA;
    tmpA.SetTexture(asdf);
    tmpA.Init(5, 5);
    tmpA.SetFps(5);


    
    uint32_t animationId = S_AddAnimation(tmpA, "NoName!");
    uint32_t animatorId = S_CreateAnimator(animationId);

    while (!S_GetEventManager()->ToQuit()) {
        S_ClearScreen();

        S_DrawTexture(asdf, 50, 50);

        for (int i = 0; i < 5; i++){
            S_DrawSection(sectId, 80 + i * 110, 350);
        }

        S_DrawAnimation(animationId, animatorId, 555, 555);
        S_GetAnimationManager()->Tick();

        S_TickGraphics();
        S_TickEvents();
        STORM_SLEEP(2);
    }*/
    return 1;
}