/* 
 * File:   sGraphicsGeometry.h
 * Author: master312
 *
 * Created on December 4, 2015, 5:34 PM
 */
 
#ifndef SGRAPHICSGEOMETRY_H__
#define SGRAPHICSGEOMETRY_H__
#include "../framework/frameworkMain.h"
#include "../framework/sPrimitives.h" 
namespace StormFramework {

enum eGeometryType : short {
    RECTANGLE = 1,
    CIRCLE = 2,
    TRIANGLE = 3
};

struct sGeometry {
    eGeometryType m_Type;
    bool m_IsFill;
    sColor m_Color;

    sGeometry() : m_IsFill(false) { }

    virtual bool IsRectangle() { return false; }
    virtual bool IsCircle() { return false; }
    virtual bool IsTriangle() { return false; }
};

struct sGeometryRectangle : sGeometry {
    sGeometryRectangle() { m_Type = RECTANGLE; }
    sGeometryRectangle(bool isFill) { 
        m_Type = RECTANGLE;
        m_IsFill = isFill; 
    }
    bool IsRectangle() { return true; }
};

struct sGeometryCircle : sGeometry {
    uint32_t m_Radius;

    sGeometryCircle() { m_Type = CIRCLE; }
    sGeometryCircle(uint32_t radius) { 
        m_Type = CIRCLE;
        m_Radius = radius; 
    }
    sGeometryCircle(bool isFill, uint32_t radius) { 
        m_Type = CIRCLE;
        m_Radius = radius;
        m_IsFill = isFill;
    }
    bool IsCircle() { return true; }
};

} /* namespace StormFramework*/
#endif /* SGRAPHICSGEOMETRY_H__ */
