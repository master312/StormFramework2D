/* 
 * File:   sPrimitives.h
 * Author: master312
 *
 * Created on September 27, 2015, 12:32 PM
 */

#ifndef SPRIMITIVES_H__
#define SPRIMITIVES_H__
#include "cFloat.h"

struct sRect {
    int x, y;
    int w, h;
    
    sRect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) { }
    sRect(int _x, int _y) : x(_x), y(_y), w(0.0f), h(0.0f) { }
    sRect(int _x, int _y, int _width, int _height) :
           x(_x), y(_y), w(_width), h(_height) { }

    void Set(int _x, int _y, int _width, int _height) {
        x = _x;
        y = _y;
        w = _width;
        h = _height;
    }
    //Check weather this point is inside rect
    bool IsInside(int _x, int _y) {
        return _x > x && _x < x + w && _y > y && _y < y + h;
    }
    /* Do not change isRec variable. It will couse error */
    bool IsCollision(sRect *rect, bool isRec = false) {
        bool tmp = (rect->x > x && rect->x < x + w) && 
                    (rect->y > y && rect->y < y + h);
        if (!isRec) {
            tmp = tmp || rect->IsCollision(this, true);            
        }

        return tmp;
    }
    //Returns true if x, y, w and h are zero
    bool IsZero() {
        return StormFramework::cFloat::IsZero4(x, y, w, h);
    }
    //Print rect values to screen
    void Print() {
        std::cout << "Rect X: " << x << " Y: " << y 
                  << " W: " << w << " H: " << h << std::endl;
    }
    bool operator==(const sRect &rect) {
        return StormFramework::cFloat::IsEqual(rect.x, this->x) &&
               StormFramework::cFloat::IsEqual(rect.y, this->y) &&
               StormFramework::cFloat::IsEqual(rect.w, this->w) &&
               StormFramework::cFloat::IsEqual(rect.h, this->h);
    }
};

struct sColor {
    uint8_t r, g, b;
    sColor() : r(0), g(), b(0) { }
};

struct sPoint { 
    int x, y;
    
    sPoint() : x(0), y(0) { }
    sPoint(int _x, int _y) : x(_x), y(_y) { }
};

struct sCircle {
    
};
#endif  /* SPRIMITIVES_H */

