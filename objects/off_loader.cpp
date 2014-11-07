#include "off_loader.h"

offLoader::offLoader(std::string filename): TriMesh(){

    _filename=(char *)filename.c_str();
    _name=filename.substr(5);
    cout<<"Off file loaded >> "<<_filename<<endl;
    _fichier.open(_filename,ios::in);

    this->headerRetrieving();
    //cout<<"file type >> "<<_filetype<<endl;
    //cout<<"Vertices number >> "<<_nbVertex<<endl;
    //cout<<"Triangles number >> "<<_nbTriangles<<endl;

    this->vertexRetrieving();
    this->trianglesRetrieving();

    _fichier.close();

    //--- Fill vertices vectors----------------------------------------------------------

    for(unsigned int i=0;i<_nbVertex;i++){
        //std::cout<<_allVtx[i][0]<<"|"<<_allVtx[i][1]<<"|"<<_allVtx[i][2]<<endl;
        this->addVertex(_allVtx[i][0],_allVtx[i][1],_allVtx[i][2]);
    }

    for(unsigned int i=0;i<_nbTriangles;i++){
        //std::cout<<_Trgl[i][0]<<"|"<<_Trgl[i][1]<<"|"<<_Trgl[i][2]<<endl;
        this->addTriangle(_Trgl[i][0],_Trgl[i][1],_Trgl[i][2]);
    }


    this->normalize();
    computeNormalsT();
    computeNormalsV();

}

void offLoader::headerRetrieving(){
    int unknown;
    if(_fichier){
        _fichier >> _filetype >> _nbVertex >> _nbTriangles >> unknown;
    }else
        throw std::logic_error("Can't open the file");
}
void offLoader::vertexRetrieving(){
    float x=0;
    float y=0;
    float z=0;
    std::vector<GLfloat> aVtx(3,0);

    for(unsigned int i=0;i<_nbVertex;i++){

        _fichier >> x >> y >> z;
        aVtx[0]=x;
        aVtx[1]=y;
        aVtx[2]=z;
        _allVtx.push_back(aVtx);
    }
}

void offLoader::trianglesRetrieving(){
    int indicesNb=0;
    for(unsigned int i=0;i<_nbTriangles;i++){
        _fichier >> indicesNb;
        if(indicesNb == 3){
            for(unsigned int k=0;k<indicesNb;k++){
                int ti;
                _fichier>>ti;
                aTrgl.push_back(ti);
            }
            _Trgl.push_back(aTrgl);
            aTrgl.clear();
        }else{
            for(unsigned int k=0;k<indicesNb;k++){
                int it;
                _fichier>>it;
                aTrgl.push_back(it);
            }

            for(unsigned int j=0;j<aTrgl.size()-1;j++){
                vector<GLint> tp;
                tp.push_back(aTrgl[0]);
                tp.push_back(aTrgl[j]);
                tp.push_back(aTrgl[j+1]);
                _Trgl.push_back(tp);
            }
            aTrgl.clear();
        }
    }
}

offLoader::~offLoader(){}
