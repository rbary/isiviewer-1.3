/**
 * @author Roland Bary
 * @date October 2014
 * Defines a off file loader
 *
 */
#ifndef OFF_LOADER_H
#define OFF_LOADER_H
#include "triMesh.h"
#include "fstream"
#include "iostream"
/**
 * Off file loader object
 *
 */

class offLoader : public TriMesh
{
public:
    offLoader(string filename);
    void setNbTriangles(int nb);
    void setNbVertex(int nb);
    void headerRetrieving();
    void vertexRetrieving();
    void trianglesRetrieving();

    virtual ~offLoader();
private:

    int _nbTriangles;
    int _nbVertex;
    std::string _filetype;
    char * _filename;
    ifstream _fichier;
    std::vector<std::vector<GLfloat> > _allVtx;
    std::vector<std::vector<GLint> > _Trgl;
    std::vector<GLint>  aTrgl;
};
#endif // OFF_LOADER_H
