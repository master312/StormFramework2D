/* 
 * File:   cLayerManager.h
 * Author: master312
 *
 * Created on November 2, 2015, 7:04 PM
 */
#ifndef CLAYERMANAGER_H__
#define CLAYERMANAGER_H__
#include <iostream>
#include <vector>
#include "../../defines.h"
#include "cLayerBase.h"
#include "../framework/frameworkMain.h"

namespace StormFramework {

class cLayerManager {
public:
    cLayerManager();
    ~cLayerManager();

    void Init();
    /* Adds state to state manager */
    /* Last added cLayerBase with state be CREATED will be active */
    /* cLayerBase object will be automatically deleted when it's */
    /* state is set to STOPED */
    void PushLayer(cLayerBase *state);
    
    /* Deletes all states */
    void Clear();

    void LogicTick(uint32_t &delta);
    void GraphicsTick();

    void EventKeyDown(StormKey &key);
    void EventKeyUp(StormKey &key);
    void EventTextType();
    void EventMouseDown(StormKey &key);
    void EventMouseUp(StormKey &key);
    void EventMouseScroll(int &scroll);
    void EventMouseMotion();
    void EventWindowResize();
    void EventWindowStateChange(int &state);
    
    void UpdateActiveLayer();
private:
    /* WARNING: m_Layers[0] IS ALWAYS SET TO NULLPTR! */
    std::vector<cLayerBase*> m_Layers;
    uint32_t m_ActiveLayer;

};

} /* namespace StormFramework */
#endif /* CLAYERMANAGER_H__ */