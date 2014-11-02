#include "cubecorner.h"

CubeCorner::CubeCorner():TriMesh()
{
    _name = "cubeCorner";

    //vertex coordinates
    static const GLfloat v[10][3]={
        {-1,-1,-1},         //pt0
        {-1,1,-1},          //pt1
        {1,1,-1},           //pt2
        {1,-1,-1},          //pt3
        {-1,-1,1},          //pt4
        {-1,1,1},           //pt5
        {0,1,1},            //pt6
        {1,1,0},            //pt7
        {1,0,1},            //pt8
        {1,-1,1}            //pt9
    };

    //triangles vertex indices
    static const GLint t[16][3]={
        {0,1,2},{0,2,3},                                                                //bottom triangles
        {0,3,4},{3,9,4},{0,4,1},{1,4,5},                                                //simple sides triangles
        {1,5,6},{1,6,7},{1,7,2},{9,8,4},{8,6,4},{6,5,4},{3,8,9},{3,7,8},{3,2,7},        //corned sides triangles
        {7,6,8}                                                                         //corned side
    };

    //triangles vertex normals
    //--- Fill vertices and triangles vectors

    // Fill vertices vector
    for(unsigned int i=0;i<10;i++)
        this->addVertex(v[i][0],v[i][1],v[i][2]);
    // Fill triangles vector
    for(unsigned int i=0;i<16;i++)
        this->addTriangle(t[i][0],t[i][1],t[i][2]);

    computeNormalsT();
    computeNormalsV();  // to be fixed.
}

