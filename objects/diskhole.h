/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D DiskHole
 *
 */
#ifndef DISKHOLE_H
#define DISKHOLE_H
#include "triMesh.h"
/**
 * DiskHole object
 *
 */
class DiskHole: public TriMesh
{
public:
    DiskHole(int nbpoint);
    virtual ~DiskHole(){};
};

#endif // DISKHOLE_H
