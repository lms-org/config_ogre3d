#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include <lms/datamanager.h>
#include <lms/module.h>
#include <ogre/visualmanager.h>

#include <OGRE/OgreManualObject.h>

class ObjectRenderer : public lms::Module {
public:
    bool initialize();
    bool deinitialize();
    bool cycle();
private:
    Ogre::ManualObject* createCubeMesh(Ogre::String name, Ogre::String matName);

    visual::Window *window;
};

#endif // OBJECT_RENDERER_H
