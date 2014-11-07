#ifndef OFF_LOADER_H
#define OFF_LOADER_H
#include "triMesh.h"
#include "fstream"
#include "iostream"


class offLoader : public TriMesh
{
public:
    offLoader(string filename);
    void setNbTriangles(int nb);
    void setNbVertex(int nb);
    void headerRetrieving();
    void vertexRetrieving();
    void trianglesRetrieving();

    virtual ~offLoader(){};
private:

    int _nbTriangles;
    int _nbVertex;
    std::string _filetype;
    std::string _filename;
    ifstream _fichier;
};
#endif // OFF_LOADER_H
