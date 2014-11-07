#include "off_loader.h"

offLoader::offLoader(std::string filename): TriMesh(){
    _filename=filename;
    _name=filename; //filename->get a name from file name

    //_fichier(_filename, std::ifstream::in);

    //headerRetrieving();

    /*cout<<"file type : "<<_filetype<<endl;
    cout<<"nbVertex : "<<_nbVertex<<endl;
    cout<<"nbTriangles : "<<_nbTriangles<<endl;

    vertexRetrieving();*/

}

/*void offLoader::headerRetrieving(){
    if(_fichier){
        _fichier >> _filetype >> _nbVertex >> _nbTriangles;
        //fichier.close();
    }else
        cerr<<"Impossible d'ouvrir le fichier."<<endl;
}*/

/*void offLoader::vertexRetrieving(){
    float firstVtx;
    _fichier >> firstVtx;
    cout<<"1st vertex value is: "<<firstVtx<<endl;
}*/

void offLoader::trianglesRetrieving(){
    cout<<"i can retrive triangles"<<endl;
}
