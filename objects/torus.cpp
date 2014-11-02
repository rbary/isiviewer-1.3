#include "torus.h"
#define ANGLE_VARIATION 90
#define ANGLE_VARIATION_TORUS 90

Torus::Torus():TriMesh()
{
    //vertices coordinates///////////////////////////////////////////////////////////////
    std::vector<std::vector<GLfloat> > allVtx;           //container to store all vertices
    std::vector<std::vector<GLfloat> > primaryCircle;    //container to store a primary circle
    std::vector<GLfloat> > aVtx(3,0);                    //any vertex

    //Triangles vertex indices///////////////////////////////////////////////////////////
    //--The primary circle definition----------------------------------------------------
    int nbPrimaryCircleVtx=0;
    float anglePrimary=0;
    float anglePrimaryV=ANGLE_VARIATION;

    while(anglePrimary<360){
        aVtx[0]=0;
        aVtx[1]=0.25 * cos(anglePrimary * PI/180.0);
        aVtx[2]=0.25 * sin(anglePrimary * PI/180.0);

        //translation

        allVtx.push_back(aVtx);
    }




    //--- Fill vertices vector-----------------------------------------------------------

        computeNormalsT();
        computeNormalsV();  //to be fixed.*/
}
