#include "funcsurface.h"


FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,float (*pMathFn)(float,float)):
    TriMesh(){

    _name ="Function surface";
    cout<<"it's work im here"<<endl;

    std::vector<std::vector<GLfloat> > allVtx;
    std::vector<GLfloat> aVtx(3,0);

    float x_variation=(maxx-minx)/nbx;
    float y_variation=(maxy-miny)/nby;

    //float x=-minx;
    //float y=-miny;

    /*for(float y=-miny;y<miny;y++){
        for(float x=-minx;x<minx;x++){
            aVtx[0]=(x);
            aVtx[1]=(y);
            //z computing
            //aVtx[2]=((*pMathFn)(x,y));
            aVtx[2]=0;
            allVtx.push_back(aVtx);
        }
    }*/

    allVtx.push_back(aVtx);


    //--- Fill vertices vector-----------------------------------------------------------
    cout<<"nb of alllVtx is"<<allVtx.size()<<endl;
    for(unsigned int i=0;i<allVtx.size();i++){
        std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
        std::cout<<"------------------------------------------------"<<endl;
        this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
    }
}

float FuncSurface::func_expcos(float x, float y){
    return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}
