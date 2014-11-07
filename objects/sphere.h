/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D Sphere
 *
 */
#ifndef SPHERE_H
#define SPHERE_H
#include "triMesh.h"
/**
 * Sphere object
 *
 */

class Sphere: public TriMesh
{
public:
    Sphere(int nbpoint);
    virtual ~Sphere(){};
};

#endif // SPHERE_H
