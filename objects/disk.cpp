#include "disk.h"

Disk::Disk(int nbpoint):TriMesh()
{
    _name = "Disk";

    //angle variation computing
    if(nbpoint < 4){
        throw std::domain_error("Dot number deficient: at least 4 dots are required to create Disk");
    }
    float angle=0;
    float angleV=360/nbpoint;
    //vertex coordinates
    std::vector<std::vector<float> > v;
    std::vector<float> aVertex(3,0);
    std::vector<float> centerVertex(3,0);

    //we have first the center vertex
    v.push_back(centerVertex);
    while(angle<360){
        aVertex[0]=(cos(angle * PI/180.0));
        aVertex[1]=(sin(angle * PI/180.0));
        aVertex[2]=(0);
        v.push_back(aVertex);
        angle+=angleV;
    }

    //triangles vertex indices
    int k=1;
    int s=2;
    std::vector<GLint> at(3,0);
    std::vector<vector<GLint> > t(v.size()-1,at);
    for(int i=0;i<v.size()-1;i++){
        t[i][0]=0;
        t[i][1]=k;
        t[i][2]=s;
        k=k+1;
        if(s==v.size()-1)
            s=0;
        s=s+1;
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
