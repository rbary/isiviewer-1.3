#include "cylinder.h"
#define NBFLOOR 4                    //floor number

Cylinder::Cylinder(int nbpoint):TriMesh()      //to do with parameters
{
    _name="Cylinder";

    //angle variation computing
    if(nbpoint < 4){
        throw std::domain_error("Dot number deficient: at least 4 dots are required to create Cylinder");
    }
    float angle=0;
    float angleV=360/nbpoint;
    //vertex coordinates/////////////////////////////////////////////////////////////////
    int kCoverVtx=0;                                        //to count top or bottom disk vertex
    std::vector<std::vector<GLfloat> > vMidCircles;         //container to store middle circles vertex
    std::vector<std::vector<GLfloat> > vTopDisk;            //container to store top disk vertex
    std::vector<std::vector<GLfloat> > vBotDisk;            //container to store bottom disk vertex
    std::vector<std::vector<GLfloat> > allVtx;              //container to store all vertices of cylinder
    std::vector<GLfloat> zMid;
    //top disk vertex////////////////////////////////////////////////////////////////////
    std::vector<GLfloat> aVtxTop(3,0);                 //any top vertex
    //we add first the center vertex
    std::vector<GLfloat> topDiskCenterVtx;
    topDiskCenterVtx.push_back(0);
    topDiskCenterVtx.push_back(0);
    topDiskCenterVtx.push_back(1);
    vTopDisk.push_back(topDiskCenterVtx);
    kCoverVtx+=1;

    while(angle<360){
        aVtxTop[0]=(cos(angle * PI/180.0));
        aVtxTop[1]=(sin(angle * PI/180.0));
        aVtxTop[2]=(1);
        vTopDisk.push_back(aVtxTop);
        kCoverVtx+=1;
        angle+=angleV;
    }
    /////////////////////////////////////////////////////////////////////////////////////

    //bottom disk vertex/////////////////////////////////////////////////////////////////
    angle=0;                                           //angle of the bottom disk (the same for the top disk re-init)
    std::vector<GLfloat> aVtxBot(3,0);                //any bottom vertex
    //we add first the center vertex
    std::vector<GLfloat> botDiskCenterVtx;
    while(angle<360){
        aVtxBot[0]=(cos(angle * PI/180.0));
        aVtxBot[1]=(sin(angle * PI/180.0));
        aVtxBot[2]=(-1);
        vBotDisk.push_back(aVtxBot);
        angle+=angleV;
    }
    botDiskCenterVtx.push_back(0);
    botDiskCenterVtx.push_back(0);
    botDiskCenterVtx.push_back(-1);
    vBotDisk.push_back(botDiskCenterVtx);
    /////////////////////////////////////////////////////////////////////////////////////
    //middle circle vertex if we have some
    if(NBFLOOR > 2){
        int nbMidCircle=NBFLOOR-2;                                  //number of middle circles
        float hBetweenCircle=((float)2/(float)(nbMidCircle+1));     //height between circle
        float zOfCircle=1-hBetweenCircle;                           //z coordinate of a middle circle
        zMid.push_back(zOfCircle);

        for(int i=0;i<nbMidCircle;i++){
            angle=0;
            std::vector<GLfloat> aMidVtx(3,0);
            while(angle<360){
                aMidVtx[0]=(cos(angle * PI/180.0));
                aMidVtx[1]=(sin(angle * PI/180.0));
                aMidVtx[2]=(zOfCircle);
                vMidCircles.push_back(aMidVtx);
                angle+=angleV;
            }
            zOfCircle=zOfCircle-hBetweenCircle;
            zMid.push_back(zOfCircle);
        }
    }
    //get all vertices in the same container to define triangles thereafter
    if(NBFLOOR > 2){
        for(unsigned int i=0;i<vTopDisk.size();i++)
            allVtx.push_back(vTopDisk[i]);

        for(unsigned int i=0;i<vMidCircles.size();i++)
            allVtx.push_back(vMidCircles[i]);

        for(unsigned int i=0;i<vBotDisk.size();i++)
            allVtx.push_back(vBotDisk[i]);
    }else{
        for(unsigned int i=0;i<vTopDisk.size();i++)
            allVtx.push_back(vTopDisk[i]);

        for(unsigned int i=0;i<vBotDisk.size();i++)
            allVtx.push_back(vBotDisk[i]);
    }


    /////////////////////////////////////////////////////////////////////////////////////
    //triangles vertex indices///////////////////////////////////////////////////////////
    int nbLatetalTrgl=2 * (kCoverVtx-1) * ((NBFLOOR-2)+1);
    std::vector<GLint> aTrgl(3,0);
    std::vector<std::vector<GLint> > lateralTrgl(nbLatetalTrgl,aTrgl);
    std::vector<std::vector<GLint> > topTrgl((kCoverVtx-1),aTrgl);
    std::vector<std::vector<GLint> > botTrgl((kCoverVtx-1),aTrgl);
    //For the top cover surface triangles////////////////////////////////////////////////
    int a=0;
    int b=1;
    int c=b+1;
    for(unsigned int i=0;i<topTrgl.size();i++){
        topTrgl[i][0]=a;
        topTrgl[i][1]=b;
        topTrgl[i][2]=c;
        b++;
        if(c==(kCoverVtx-1))
            c=a;
        c++;
    }
    //For the bottom cover surface triangles/////////////////////////////////////////////
    int d=allVtx.size()-1;
    int e=allVtx.size()-botTrgl.size()-1;
    int f=e+1;

    for(unsigned int i=0;i<botTrgl.size();i++){
        botTrgl[i][0]=d;
        botTrgl[i][1]=f;
        botTrgl[i][2]=e;
        e++;
        if(f==(allVtx.size()-2))
            f=allVtx.size()-botTrgl.size()-2;
        f++;

    }

    //For the lateral surface triangles//////////////////////////////////////////////////
    int r=1;
    int s=kCoverVtx;
    int t=s+1;

    for (unsigned int i=0;i<lateralTrgl.size();i++){
        lateralTrgl[i][0]=r;
        lateralTrgl[i][1]=s;
        lateralTrgl[i][2]=t;

        if(std::abs(r-s)==1 && std::abs(s-t)==(kCoverVtx-1)){
            r++;
            s=s+(kCoverVtx-1);
            t=t+((kCoverVtx*2)-1);
        }else{
            //r variable behavior
            if((i % 2)==1)
                r++;

            //t variable behavior
            if((t % (kCoverVtx-1))==0 && (i % 2)==1){
                t=t+1;
            }else{
                        if((i % 2)==1)
                            //t=t+5;
                            t=t+kCoverVtx;

                        if((i % 2)==0)
                            //t=t-4;
                            t=t-(kCoverVtx-1);
            }

            //s variable behavior
            if((s % (kCoverVtx-1))==0 && (i % 2)==0){
                s=s-(kCoverVtx-2);
            }else{
                    if((i % 2)==0)
                        s++;
            }
        }
    }
    //--- Fill vertices vector-------------------------------------------------------------
    for(unsigned int i=0;i<allVtx.size();i++){
        //std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
        //std::cout<<"------------------------------------------------"<<endl;
        this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
    }

    //--Fill top cover surface triangles--------------------------------------------------
    for(unsigned int i=0;i<topTrgl.size();i++){
        //std::cout<<topTrgl[i][0]<<"|"<<topTrgl[i][1]<<"|"<<topTrgl[i][2]<<endl;
        this->addTriangle(topTrgl[i][0],topTrgl[i][1],topTrgl[i][2]);
    }
    //--Fill bottom cover surface triangles-----------------------------------------------
    for(unsigned int i=0;i<botTrgl.size();i++){
        //std::cout<<botTrgl[i][0]<<"|"<<botTrgl[i][1]<<"|"<<botTrgl[i][2]<<endl;
        this->addTriangle(botTrgl[i][0],botTrgl[i][1],botTrgl[i][2]);
    }

    //--Fill lateral surface triangles----------------------------------------------------
    for(unsigned int i=0;i<lateralTrgl.size();i++){
        //std::cout<<lateralTrgl[i][0]<<"|"<<lateralTrgl[i][1]<<"|"<<lateralTrgl[i][2]<<endl;
        this->addTriangle(lateralTrgl[i][0],lateralTrgl[i][1],lateralTrgl[i][2]);
    }

    computeNormalsT();
    computeNormalsV();  //to be fixed.
}
