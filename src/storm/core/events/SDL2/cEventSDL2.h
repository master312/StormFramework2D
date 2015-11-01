/* 
 * File:   cEventSDL2.h
 * Author: master312
 *
 * Created on September 26, 2015, 8:43 PM
 */

#ifndef CINPUTSDL2_H__
#define CINPUTSDL2_H__
#include <SDL2/SDL.h>
#include "../cEventBase.h"

namespace StormFramework {


class cEventSDL2 : public cEventBase {
public:
    bool Update();
private:
    SDL_Event m_Event;
};


} /* namespace StormFramework */
#endif  /* CINPUTSDL2_H__ */

