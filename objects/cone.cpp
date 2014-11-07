#include "cone.h"

Cone::Cone(int nbpoint): TriMesh()
{
    _name="Cone";

    //angle variation computing
    if(nbpoint < 4){
        throw std::domain_error("Dot number deficient: at least 4 dots are required to create Cone");
    }
    float angle=0;
    float angleV=360/nbpoint;
    //Vertices coordinates///////////////////////////////////////////////////////////////
    std::vector<std::vector<GLfloat> > vBaseDisk;
    std::vector<std::vector<GLfloat> > allVtx;
    int nbBaseVtx=0;
    //Peak vertex coordinates------------------------------------------------------------
    std::vector<GLfloat> peakVtx;
    peakVtx.push_back(0);
    peakVtx.push_back(0);
    peakVtx.push_back(1);
    //base vertices coordinates----------------------------------------------------------
    std::vector<GLfloat> aVtxBase(3,0);               //any base vertex
    //we add first the base center vertex
    std::vector<GLfloat> baseDiskCenterVtx;
    baseDiskCenterVtx.push_back(0);
    baseDiskCenterVtx.push_back(0);
    baseDiskCenterVtx.push_back(-1);
    vBaseDisk.push_back(baseDiskCenterVtx);
    nbBaseVtx+=1;
    while(angle<360){
        aVtxBase[0]=(cos(angle * PI/180.0));
        aVtxBase[1]=(sin(angle * PI/180.0));
        aVtxBase[2]=(-1);
        vBaseDisk.push_back(aVtxBase);
        nbBaseVtx+=1;
        angle+=angleV;
    }

    //get all vertices in the same container to define triangles thereafter
    allVtx.push_back(peakVtx);
    for(unsigned int i=0;i<vBaseDisk.size();i++)
        allVtx.push_back(vBaseDisk[i]);

    //Triangles vertices indices/////////////////////////////////////////////////////////
    //int nbLatetalTrgl=2 * (kCoverVtx-1) * ((NBFLOOR-2)+1);
    std::vector<GLint> aTrgl(3,0);
    std::vector<std::vector<GLint> > lateralTrgl(nbBaseVtx-1,aTrgl);
    std::vector<std::vector<GLint> > baseTrgl(nbBaseVtx-1,aTrgl);
    //Base surface vertices indices------------------------------------------------------
    int a=1;
    int b=a+1;
    int c=b+1;
    for(unsigned int i=0;i<baseTrgl.size();i++){
        baseTrgl[i][0]=a;
        baseTrgl[i][1]=c;
        baseTrgl[i][2]=b;
        b++;
        if(c==(nbBaseVtx))
            c=a;
        c++;
    }
    //Lateral surface vertices indices---------------------------------------------------
    int d=0;
    int e=d+2;
    int f=e+1;

    for(unsigned int i=0;i<lateralTrgl.size();i++){
        lateralTrgl[i][0]=d;
        lateralTrgl[i][1]=e;
        lateralTrgl[i][2]=f;
        e++;
        if(f==(nbBaseVtx))
            f=d+1;
        f++;
    }

    //--- Fill vertices and triangles vectors////////////////////////////////////////////
    //--- Fill vertices vectors----------------------------------------------------------
    for(unsigned int i=0;i<allVtx.size();i++){
        //std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
        this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
    }

    //-- Fill base surface triangles vectors----------------------------------------------
    for(unsigned int i=0;i<baseTrgl.size();i++){
        //std::cout<<baseTrgl[i][0]<<"|"<<baseTrgl[i][1]<<"|"<<baseTrgl[i][2]<<endl;
        this->addTriangle(baseTrgl[i][0],baseTrgl[i][1],baseTrgl[i][2]);
    }

    cout<<"************************************"<<endl;

    //-- Fill lateral surface triangles vectors------------------------------------------
    for(unsigned int i=0;i<lateralTrgl.size();i++){
        //std::cout<<lateralTrgl[i][0]<<"|"<<lateralTrgl[i][1]<<"|"<<lateralTrgl[i][2]<<endl;
        this->addTriangle(lateralTrgl[i][0],lateralTrgl[i][1],lateralTrgl[i][2]);
    }

    computeNormalsT();
    computeNormalsV();  // to be fixed
}
