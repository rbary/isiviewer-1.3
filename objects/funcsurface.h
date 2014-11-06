#ifndef FUNCSURFACE_H
#define FUNCSURFACE_H
#include "triMesh.h"

class FuncSurface: public TriMesh
{
public:
    FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,float (*pMathFn)(float,float)=NULL);
    static float func_expcos(float x,float y);
    virtual ~FuncSurface(){};
};
#endif // FUNCSURFACE_H
