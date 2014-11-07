/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D Sphere
 *
 */
#ifndef TORUS_H
#define TORUS_H
#include "triMesh.h"
/**
 * Torus object
 *
 */

class Torus:public TriMesh
{
public:
    Torus(int nbpoint);
    virtual ~Torus(){};
};

#endif // TORUS_H
