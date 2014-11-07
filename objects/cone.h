/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D Cone
 *
 */
#ifndef CONE_H
#define CONE_H
#include "triMesh.h"
/**
 * Cone object
 *
 */

class Cone: public TriMesh
{
public:
    Cone(int nbpoint);
    virtual ~Cone(){};
};

#endif // CONE_H
