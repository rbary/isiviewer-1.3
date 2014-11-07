/**
 * @file   main.cpp
 * @author Bruno Jobard
 * @author Author1
 * @author Author2
 * @date   Sep 2012
 *
 * @brief  Declares an application, a main window and a 3D scene
 *
 *
 */
#include <QApplication>
#include "my_main_window.h"
#include "tclap/CmdLine.h"
#include "iostream"


#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"
#include "objects/cubecorner.h"
#include "objects/disk.h"
#include "objects/diskhole.h"
#include "objects/cylinder.h"
#include "objects/cone.h"
#include "objects/sphere.h"
#include "objects/torus.h"
#include "objects/funcsurface.h"
#include "objects/off_loader.h"

/**
* Program usage
* Should be handled with the tclap library
*/
void usage(char* name){
  cout<< "usage: " << name << " [options]" <<endl;
  cout<< "options:" <<endl;
  cout<< "  -h, --help                 shows this message" <<endl;
  cout<< "  --off file                 loads OFF file" <<endl;
}

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  // Parse program arguments here
  // with the tclap library
  // http://tclap.sourceforge.net/manual.html
  //

  // initialize my custom 3D scene
  float objectRadius = 1.;
  QPointer<MyScene> myScene = new MyScene(objectRadius);

  //add simple objects
  myScene->addObject(new Cube());
  myScene->addObject(new Pyramid());
  myScene->addObject(new CubeCorner());
  myScene->addObject(new Disk());
  myScene->addObject(new DiskHole());
  myScene->addObject(new Cylinder());
  myScene->addObject(new Cone());
  myScene->addObject(new Sphere());
  myScene->addObject(new Torus());


  // add surface functions
  myScene->addObject(new FuncSurface(50,50,-PI,PI,-PI,PI,FuncSurface::func_expcos));
  //myScene->addObject(new FuncSurface(50,50,-PI,PI,-PI,PI,FuncSurface::func_expcos));

  // add user defined OFF files
  // ...
  try{
    TCLAP::CmdLine cmd("Command description message",' ', "0.9");
    TCLAP::ValueArg<std::string> offFileArg("o", "off", "Off file loading",false,"","string");
    cmd.add(offFileArg);
    cmd.parse(argc, argv);
    std::string offFileName = offFileArg.getValue();

    //off file name handling
    std::cout << "File name is: "<<offFileName<<std::endl;
    myScene->addObject(new offLoader(offFileName));

  } catch (TCLAP::ArgException &e) //catch any exceptions
  {
    std::cerr << "error: "<<e.error() << "for arg " << e.argId() << std::endl;
  }

  // initialize my custom main window
  QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
  // display the window
  myMainWindow->show();
  // enter in the main loop
  return app.exec();
}

