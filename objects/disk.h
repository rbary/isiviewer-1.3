/**
 * @author Roland Bary
 * @date October 2014
 * Defines a 3D Disk
 *
 */
#ifndef DISK_H
#define DISK_H
#include "triMesh.h"

/**
 * Disk object
 */

class Disk : public TriMesh
{
public:
    Disk(int nbpoint);
    virtual ~Disk(){};
};
#endif // DISK_H
