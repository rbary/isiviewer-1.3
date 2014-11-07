#include "sphere.h"
#define MAX_COLATITUDE 180
#define MAX_LONGITUDE 360

Sphere::Sphere(int nbpoint):TriMesh()
{
    _name="Sphere";
    //angle variation computing
    if(nbpoint < 5){
        throw std::domain_error("Dot number deficient: at least 5 dots are required to create Sphere");
    }
    float angleV=360/nbpoint;

    //Vertex coordinates/////////////////////////////////////////////////////////////////
    float colatitude=0;
    float longitude=0;
    int nbCircleVtx=0;                 //top or bottom respectively first or last circle vertices number
    std::vector<std::vector<GLfloat> > topFirstCircleVtx;
    std::vector<std::vector<GLfloat> > botLastCircleVtx;
    std::vector<std::vector<GLfloat> > remainingSfVtx;
    std::vector<std::vector<GLfloat> > allVtx;
    std::vector<GLfloat> aVtx(3,0);

    std::vector<GLfloat> topPeakVtx;
    std::vector<GLfloat> botPeakVtx;

    topPeakVtx.push_back(0);
    topPeakVtx.push_back(0);
    topPeakVtx.push_back(1);


    botPeakVtx.push_back(0);
    botPeakVtx.push_back(0);
    botPeakVtx.push_back(-1);

    //top first circle vertices coordinates------------------------------------------------------
    colatitude=angleV;
    while(longitude < 360){
        aVtx[0]= sin(colatitude * PI/180.0) * cos(longitude * PI/180.0);
        aVtx[1]= sin(colatitude * PI/180.0) * sin(longitude * PI/180.0);
        aVtx[2]= cos(colatitude * PI/180.0);

        topFirstCircleVtx.push_back(aVtx);
        nbCircleVtx++;
        longitude+=angleV;
    }
    longitude=0;

    //remaining surface vertices coordinates---------------------------------------------
    colatitude+=angleV;
    while(colatitude < (MAX_COLATITUDE-angleV)){

        while(longitude < MAX_LONGITUDE){
            aVtx[0]= sin(colatitude * PI/180.0) * cos(longitude * PI/180.0);
            aVtx[1]= sin(colatitude * PI/180.0) * sin(longitude * PI/180.0);
            aVtx[2]= cos(colatitude * PI/180.0);

            remainingSfVtx.push_back(aVtx);
            longitude+=angleV;
        }
        longitude=0;
        colatitude = colatitude + angleV;
    }

    //bottom last circle vertices coordinates---------------------------------------------------
    colatitude=MAX_COLATITUDE-angleV;
    while(longitude < MAX_LONGITUDE){
        aVtx[0]= sin(colatitude * PI/180.0) * cos(longitude * PI/180.0);
        aVtx[1]= sin(colatitude * PI/180.0) * sin(longitude * PI/180.0);
        aVtx[2]= cos(colatitude * PI/180.0);

        botLastCircleVtx.push_back(aVtx);
        longitude+=angleV;
    }
    longitude=0;
    colatitude=0;

    //get all vertices in the same container to define triangles thereafter
    allVtx.push_back(topPeakVtx);
    allVtx.push_back(botPeakVtx);
    for(unsigned int i=0;i<topFirstCircleVtx.size();i++){
        allVtx.push_back(topFirstCircleVtx[i]);
    }
    for(unsigned int i=0;i<remainingSfVtx.size();i++){
        allVtx.push_back(remainingSfVtx[i]);
    }
    for(unsigned int i=0;i<botLastCircleVtx.size();i++){
        allVtx.push_back(botLastCircleVtx[i]);
    }


    //Triangles vertices indices/////////////////////////////////////////////////////////
    //int nbRemT=2 * (allVtx.size()-2 + nbCircleVtx);
    int nbRTrgl=2 * nbCircleVtx * (((allVtx.size()-2)/nbCircleVtx)-1);
    std::vector<GLint> aTrgl(3,0);
    std::vector<std::vector<GLint> > topHatTrgl(nbCircleVtx,aTrgl);
    std::vector<std::vector<GLint> > botHatTrgl(nbCircleVtx,aTrgl);
    std::vector<std::vector<GLint> > remainingTrgl(nbRTrgl,aTrgl);

    int a=0;
    int b=2;
    int c=b+1;
    for(unsigned int i=0;i<topHatTrgl.size();i++){
        topHatTrgl[i][0]=a;
        topHatTrgl[i][1]=b;
        topHatTrgl[i][2]=c;
        b++;
        if(c==(nbCircleVtx+1))
            c=a+1;
        c++;
    }

    int d=1;
    int e=allVtx.size()-nbCircleVtx;
    int f=e+1;
    for(unsigned int i=0;i<botHatTrgl.size();i++){
        botHatTrgl[i][0]=d;
        botHatTrgl[i][1]=f;
        botHatTrgl[i][2]=e;
        e++;
        if(f==(allVtx.size()-1))
            f=allVtx.size()-nbCircleVtx-1;
        f++;
    }

    int r=2;
    int s=nbCircleVtx+2;
    int t=s+1;

    for (unsigned int i=0;i<remainingTrgl.size();i++){
           remainingTrgl[i][0]=r;
           remainingTrgl[i][1]=s;
           remainingTrgl[i][2]=t;

           if(std::abs(r-s)==1 && std::abs(s-t)==(nbCircleVtx)){
               r++;
               s=s+(nbCircleVtx);
               t=t+((nbCircleVtx*2)+1);
           }else{
               //r variable behavior
               if((i % 2)==1)
                   r++;

               //t variable behavior
               if(((t-1) % (nbCircleVtx))==0 && (i % 2)==1){
                   t=t+1;
               }else{
                           if((i % 2)==1)
                               t=t+(nbCircleVtx+1);

                           if((i % 2)==0)
                               t=t-(nbCircleVtx);
               }

               //s variable behavior
               if(((s-1) % (nbCircleVtx))==0 && (i % 2)==0){
                   s=s-(nbCircleVtx-1);
               }else{
                       if((i % 2)==0)
                           s++;
               }
           }
       }


    //--- Fill vertices and triangles vectors////////////////////////////////////////////
    //--- Fill vertices vectors----------------------------------------------------------
      for(unsigned int i=0;i<allVtx.size();i++){
          //std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
          //std::cout<<"-----------------------------------------------"<<endl;
          this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
      }

      //-- Fill base surface triangles vectors----------------------------------------------
         for(unsigned int i=0;i<topHatTrgl.size();i++){
             //std::cout<<topHatTrgl[i][0]<<"|"<<topHatTrgl[i][1]<<"|"<<topHatTrgl[i][2]<<endl;
             this->addTriangle(topHatTrgl[i][0],topHatTrgl[i][1],topHatTrgl[i][2]);
         }
         //cout<<"***************************"<<endl;

         for(unsigned int i=0;i<botHatTrgl.size();i++){
             //std::cout<<botHatTrgl[i][0]<<"|"<<botHatTrgl[i][1]<<"|"<<botHatTrgl[i][2]<<endl;
             this->addTriangle(botHatTrgl[i][0],botHatTrgl[i][1],botHatTrgl[i][2]);
         }

         //cout<<"***************************"<<endl;

         for(unsigned int i=0;i<remainingTrgl.size();i++){
             //std::cout<<remainingTrgl[i][0]<<"|"<<remainingTrgl[i][1]<<"|"<<remainingTrgl[i][2]<<endl;
             this->addTriangle(remainingTrgl[i][0],remainingTrgl[i][1],remainingTrgl[i][2]);
         }


      computeNormalsT();
      computeNormalsV();  // to be fixed
}
