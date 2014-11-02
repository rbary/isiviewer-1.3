#include "cone2.h"
#define ANGLE_VARIATION 90

Cone2::Cone2(): TriMesh()
{
    _name="Cone2";
    //vertex coordinates/////////////////////////////////////////////////////////////////
    int nbBaseVtx=0;
    std::vector<std::vector<GLfloat> > vBaseDisk;     //container to store base disk vertices
    std::vector<std::vector<GLfloat> > allVtx;        //container to store all vertices
    //base vertex////////////////////////////////////////////////////////////////////////
    float coverAngle=0;                               //angle of top disk (the same for the bottom disk)
    float coverAngleV=ANGLE_VARIATION;                //variation of coverAngle
    std::vector<GLfloat> aVtxBase(3,0);               //any top vertex
    //we add first the center vertex
    std::vector<GLfloat> baseDiskCenterVtx;
    baseDiskCenterVtx.push_back(0);
    baseDiskCenterVtx.push_back(0);
    baseDiskCenterVtx.push_back(-3);
    vBaseDisk.push_back(baseDiskCenterVtx);
    nbBaseVtx++;

    while(coverAngle<360){
        aVtxBase[0]=(cos(coverAngle * PI/180.0));
        aVtxBase[1]=(sin(coverAngle * PI/180.0));
        aVtxBase[2]=(-3);
        vBaseDisk.push_back(aVtxBase);
        nbBaseVtx++;
        coverAngle+=coverAngleV;
    }

    //get all vertices in the same container to define triangles thereafter
    for(unsigned int i=0;i<vBaseDisk.size();i++){
        allVtx.push_back(vBaseDisk[i]);

    /*for(unsigned int i=0;i<vBotDisk.size();i++)
        allVtx.push_back(vBotDisk[i]);*/
    }
    /////////////////////////////////////////////////////////////////////////////////////

    //triangles vertex indices///////////////////////////////////////////////////////////
    std::vector<GLint> aTrgl(3,0);
    std::vector<std::vector<GLint> > baseTrgl((nbBaseVtx-1),aTrgl);
    //base triangles normals/////////////////////////////////////////////////////////////
    int a=0;
    int b=1;
    int c=b+1;
    for(unsigned int i=0;i<baseTrgl.size();i++){
        baseTrgl[i][0]=a;
        baseTrgl[i][1]=b;
        baseTrgl[i][2]=c;
        b++;
        if(c==(nbBaseVtx-1))
            c=a;
        c++;
    }
    /////////////////////////////////////////////////////////////////////////////////////

    //--- Fill vertices and triangles vectors
    //--- Fill vertices vectors
       for(unsigned int i=0;i<allVtx.size();i++){
           std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
           std::cout<<"----------------------------------"<<endl;
           this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
       }
    //--- Fill base triangles indices vectors
    //cout<<"***** Fill top triangles *****"<<endl;
       for(unsigned int i=0;i<baseTrgl.size();i++){
           std::cout<<baseTrgl[i][0]<<"|"<<baseTrgl[i][1]<<"|"<<baseTrgl[i][2]<<endl;
           this->addTriangle(baseTrgl[i][0],baseTrgl[i][1],baseTrgl[i][2]);
       }
   //////////////////////////////////////////////////////////////////////////////////////

       computeNormalsT();
       computeNormalsV();  // to be fixed.
}
