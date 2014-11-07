/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D CubeCorner
 *
 */
#ifndef CUBECORNER_H
#define CUBECORNER_H
#include "triMesh.h"

/**
 * CubeCorner object
 */
class CubeCorner : public TriMesh
{
public:
    CubeCorner();
    virtual ~CubeCorner(){};
};

#endif // CUBECORNER_H
