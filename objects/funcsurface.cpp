#include "funcsurface.h"


FuncSurface::FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy,float (*pMathFn)(float,float)):
    TriMesh(){

    _name ="Function surface";
    std::vector<std::vector<GLint> > line;
    std::vector<GLint> aTrgl;

    std::vector<std::vector<GLfloat> > allVtx;
    std::vector<GLfloat> aVtx(3,0);
    float x_range=maxx-minx;
    float y_range=maxy-miny;

    float delta_x=x_range/(nbx);
    float delta_y=y_range/(nby);

    for(float x=minx;x<=maxx;x+=delta_x){
        for(float y=miny;y<=maxy;y+=delta_y){
            aVtx[0]=x/(x_range/2);
            aVtx[1]=y/(y_range/2);
            aVtx[2]=((*pMathFn)(x,y));
            allVtx.push_back(aVtx);

            aTrgl.push_back(allVtx.size()-1);
        }
        line.push_back(aTrgl);
        aTrgl.clear();
    }


    vector<vector<GLint> > triangles;
    vector<GLint> att;

    for(int i=0;i<line.size()-1;i++)
    {
        for(int j=0;j<nbx-1; j++)
        {
            att.push_back(line[i][j]);
            att.push_back(line[i+1][j+1]);
            att.push_back(line[i][j+1]);
            triangles.push_back(att);
            att.clear();

            att.push_back(line[i][j]);
            att.push_back(line[i+1][j]);
            att.push_back(line[i+1][j+1]);

            triangles.push_back(att);
            att.clear();
      }
    }
    //--- Fill vertices vector-----------------------------------------------------------
    //cout<<"Number of allVtx is: "<<allVtx.size()<<endl;
    for(unsigned int i=0;i<allVtx.size();i++){
        //std::cout<<allVtx[i][0]<<"|"<<allVtx[i][1]<<"|"<<allVtx[i][2]<<endl;
        //std::cout<<"------------------------------------------------"<<endl;
        this->addVertex(allVtx[i][0],allVtx[i][1],allVtx[i][2]);
    }

    for(unsigned int i=0;i<triangles.size();i++){
        //std::cout<<triangles[i][0]<<triangles[i][1]<<triangles[i][2]<<endl;
        //std::cout<<"------------------------------------------------"<<endl;
        this->addTriangle(triangles[i][0],triangles[i][1],triangles[i][2]);
    }

    this->normalize();
    computeNormalsT();
    computeNormalsV();

}

float FuncSurface::func_expcos(float x, float y){
    return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}

float FuncSurface::func_freak(float x,float y){
    //return exp(-(x*x/2+y*y/2))*sin(2*x*x+2*y*y);
    return .75/exp(pow(2,(x*5))*pow(2,(y*5)));
    //return sin(5 * x)*cos(5 * y)/5;

}
