/**
 * @author Roland Bary
 * @date October 2014
 * Defines 3D functions surface
 *
 */
#ifndef FUNCSURFACE_H
#define FUNCSURFACE_H
#include "triMesh.h"
/**
 * Function surface object
 *
 */

class FuncSurface: public TriMesh
{
public:
    FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,float (*pMathFn)(float,float)=NULL);
    static float func_expcos(float x,float y);
    static float func_freak(float x,float y);
    virtual ~FuncSurface(){};
};
#endif // FUNCSURFACE_H
