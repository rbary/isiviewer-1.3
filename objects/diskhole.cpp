#include "diskhole.h"

DiskHole::DiskHole(): TriMesh ()
{
    _name = "DiskHole";

    //vertex coordinates
    std::vector<std::vector<GLfloat> > v;
    float agl=0;
    float dagl=10;                             //Variation dangle
    std::vector<GLfloat> aVertexSd(3,0);       //A temporary vertex for the small disk
    std::vector<GLfloat> aVertexBd(3,0);       //A temporary vertex for the big disk

    while(agl<360){
        aVertexSd[0]=0.5 * cos(agl * PI/180.0);
        aVertexSd[1]=0.5 * sin(agl * PI/180.0);
        aVertexSd[2]=0;

        aVertexBd[0]=cos(agl * PI/180.0);
        aVertexBd[1]=sin(agl * PI/180.0);
        aVertexBd[2]=0;

        v.push_back(aVertexSd);
        v.push_back(aVertexBd);

        agl+=dagl;
    }

    //triangles vertex indices
    int r=2;
    int s=1;
    int q=3;
    std::vector<GLint> tempTriangle(3,0);
    std::vector<vector<GLint> > t(v.size(),tempTriangle);
    //the first triangle
    t[0][0]=0;
    t[0][1]=1;
    t[0][2]=2;


    //the last triangle
    t[t.size()-1][0]=0;
    t[t.size()-1][1]=t.size()-1;
    t[t.size()-1][2]=1;

    for(int i=1;i<t.size()-1;i++){
        t[i][0]=r;
        t[i][1]=s;
        t[i][2]=q;

        //test on r before inc
        if(q-r==1)
            r=r;
        if(q-r==2)
            r+=2;

        //test on s before inc
        if(q-s==2)
            s+=2;
        if(q-s==1)
            s=s;
        if(q<t.size()-1){
            q+=1;
        }
        else{
            q=0;
        }
    }

    //triangles vertex normals
       //--- Fill vertices and triangles vectors

       // Fill vertices vector
       for(unsigned int i=0;i<v.size();i++){
           //std::cout<<v[i][0]<<"|"<<v[i][1]<<"|"<<v[i][2]<<endl;
           //std::cout<<"----------------------------------"<<endl;
           this->addVertex(v[i][0],v[i][1],v[i][2]);
       }
       // Fill triangles vector
       for(unsigned int i=0;i<t.size();i++){
           //std::cout<<t[i][0]<<"|"<<t[i][1]<<"|"<<t[i][2]<<endl;
           this->addTriangle(t[i][0],t[i][1],t[i][2]);
       }


       computeNormalsT();
       computeNormalsV();  // to be fixed.
}
