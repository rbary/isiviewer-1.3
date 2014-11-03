#include "torus.h"
#define ANGLE_VARIATION 10
#define ANGLE_VARIATION_TORUS 10

Torus::Torus():TriMesh()
{
    //vertices coordinates///////////////////////////////////////////////////////////////
    std::vector<std::vector<GLfloat> > allVtx;           //container to store all vertices
    std::vector<std::vector<GLfloat> > primaryCircle;    //container to store a primary circle
    std::vector<GLfloat> aVtx(3,0);                      //any vertex
    //glm::vec3 rotVtx;

    //Triangles vertex indices///////////////////////////////////////////////////////////
    //--The primary circle definition----------------------------------------------------
    int nbPcVtx=0;
    float anglePrimary=0;
    float anglePrimaryV=ANGLE_VARIATION;
    float angleTorus=0;
    float angleTorusV=ANGLE_VARIATION_TORUS;



    while(anglePrimary<360){
        aVtx[0]=0;
        aVtx[1]=0.25 * cos(anglePrimary * PI/180.0);
        aVtx[2]=0.25 * sin(anglePrimary * PI/180.0);

        primaryCircle.push_back(aVtx);
        nbPcVtx++;

        anglePrimary+=anglePrimaryV;
    }

    cout<<"Primary circle vertices number is: "<<nbPcVtx<<endl;

    //primary circle translation following y to get the right position for the torus construction
    for(unsigned int i=0;i<primaryCircle.size();i++)
        primaryCircle[i][1]+=0.75;

    //we add the primary circle to allVtx container
    for(unsigned int i=0;i<primaryCircle.size();i++){
        allVtx.push_back(primaryCircle[i]);
    }

    //torus remaining circle computing
    while(angleTorus<360){
        for(unsigned int i=0;i<primaryCircle.size();i++){
            glm::vec3 vtxToRotate(primaryCircle[i][0],allVtx[i][1],allVtx[i][2]);
            glm::vec3 vtxRotated = glm::rotateZ(vtxToRotate,angleTorus);
            aVtx[0]=vtxRotated[0];
            aVtx[1]=vtxRotated[1];
            aVtx[2]=vtxRotated[2];

            allVtx.push_back(aVtx);
        }
        angleTorus+=angleTorusV;
    }
    //triangles vertex indices///////////////////////////////////////////////////////////
    int nbTrgl=2 * allVtx.size();
    std::vector<GLint> aTrgl(3,0);
    std::vector<std::vector<GLint> > torusTrgl(nbTrgl,aTrgl);

    cout<<"nb primary circle vertices is: "<<nbPcVtx;

    int r=0;
    int s=nbPcVtx;
    int t=s+1;

    for (unsigned int i=0;i<torusTrgl.size()-(2 * nbPcVtx);i++){
        torusTrgl[i][0]=r;
        torusTrgl[i][1]=s;
        torusTrgl[i][2]=t;

        /*if(r==(allVtx.size() - (nbPcVtx+1)) && (i % 2)==1){
            r++;
            s=0;
            t=1;
        }else{*/

        if((std::abs(r-s)==1) && (std::abs(s-t)==nbPcVtx)){
            r++;
            s=s+(nbPcVtx);
            t=t+(2 * nbPcVtx)+1;
        }else{
            //r variable behavior
            if((i % 2)==1)
                r++;

            //t variable behavior
            if(((t+1) % nbPcVtx)==0 && (i % 2)==1){
                    t=t+1;
            }else{
                if((i % 2)==1)
                    t=t+nbPcVtx+1;

                if((i % 2)==0)
                    t=t-(nbPcVtx);
            }


            //s variable behavior
            if(((s+1) % (nbPcVtx)) == 0 && (i % 2)==0){
                    s=s-(nbPcVtx-1);
            }else{
                if((i % 2)==0)
                    s++;
            }
        }

        int r=allVtx.size()-nbPcVtx;
        int s=0;
        int t=s+1;

        for(unsigned int i=torusTrgl.size()-(2 * nbPcVtx);i<torusTrgl.size();i++){
            torusTrgl[i][0]=r;
            torusTrgl[i][1]=s;
            torusTrgl[i][2]=t;

            //r variable behavior
            if((i % 2)==1)
                r++;

            //t variable behavior
            if(t==(allVtx.size()-1) && (i % 2)==1){
                    t=0;
            }else{
                if((i % 2)==1)
                    t=t-(allVtx.size()-nbPcVtx-1);

                if((i % 2)==0)
                    t=t+(allVtx.size()-nbPcVtx);
            }

            //s variable behavior
            if(((s+1) % (nbPcVtx)) == 0 && (i % 2)==0){
                    s=s-(nbPcVtx-1);
            }else{
                if((i % 2)==0)
                    s++;
            }

        }
}

    //--- Fill vertices vector-----------------------------------------------------------
    cout<<"allVtx size is: "<<allVtx.size()<<endl;
    for(unsigned int i=0;i<allVtx.size();i++){
        std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
        std::cout<<"-------------------------------"<<endl;
        this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
    }

    cout<<"********************************************"<<endl;

    cout<<"torusTrgl size is: "<<torusTrgl.size()<<endl;
    //--Fill surface triangles-----------------------------------------------------------
    for(unsigned int i=0;i<torusTrgl.size();i++){
        std::cout<<torusTrgl[i][0]<<"|"<<torusTrgl[i][1]<<"|"<<torusTrgl[i][2]<<endl;
        this->addTriangle(torusTrgl[i][0],torusTrgl[i][1],torusTrgl[i][2]);
    }

        computeNormalsT();
        computeNormalsV();  //to be fixed.
}
