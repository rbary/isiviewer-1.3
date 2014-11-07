/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D Cylinder
 *
 */
#ifndef CYLINDER_H
#define CYLINDER_H
#include "triMesh.h"
/**
 * Cylinder object
 */
class Cylinder : public TriMesh
{
public:
    Cylinder(int nbpoint);
    virtual ~Cylinder(){};
};

#endif // CYLINDER_H
