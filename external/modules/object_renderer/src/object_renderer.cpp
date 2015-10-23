#include "object_renderer.h"

#include <cmath>
#include <OGRE/OgreMeshManager.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreMaterialManager.h>

bool ObjectRenderer::initialize() {
    window = VisualManager::getInstance()->getWindow(this,getChannelMapping("WINDOW"));

    Ogre::Root::getSingleton().addResourceLocation(lms::Framework::configsDirectory + "/materials/", "FileSystem");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


    Ogre::ResourceManager::ResourceMapIterator it = Ogre::MaterialManager::getSingleton().getResourceIterator();

    while(it.hasMoreElements()) {
        logger.info("key") << it.peekNextKey();
        //Ogre::MaterialPtr mat = (it.peekNextValue()).get()->getName();
        logger.info("value") << it.peekNextValue().get()->getName();
        it.moveNext();
    }

    //window->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0));
    window->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    //window->getCamera()->setPolygonMode(Ogre::PolygonMode::PM_WIREFRAME);

    Ogre::Light* spotLight = window->getSceneManager()->createLight("SpotLight");
    spotLight->setDiffuseColour(1.0, 1.0, 1.0);
    spotLight->setSpecularColour(1.0, 1.0, 1.0);
    spotLight->setType(Ogre::Light::LT_POINT);
    spotLight->setPosition(Ogre::Vector3(2, 0, 0.5));
    //spotLight->setDirection(Ogre::Vector3(-1, 0, -1));
    //spotLight->setSpotlightRange(Ogre::Degree(0), Ogre::Degree(360));
    spotLight->setCastShadows(true);

    window->getCamera()->setProjectionType(Ogre::ProjectionType::PT_PERSPECTIVE);
    window->getCamera()->setPosition(Ogre::Vector3(0,0,30));
    window->getCamera()->lookAt(Ogre::Vector3(0,0,0));

    Ogre::SceneNode* cubeNode = window->getSceneManager()->getRootSceneNode()->createChildSceneNode();
    Ogre::ManualObject* cube = createCubeMesh("Cube", "Template/Red");
    cube->setCastShadows(true);
    cubeNode->attachObject(cube);

    Ogre::SceneNode* cubeNode2 = window->getSceneManager()->getRootSceneNode()->createChildSceneNode();
    cubeNode2->setPosition(-2, 0, 0);
    Ogre::ManualObject* cube2 = createCubeMesh("Cube", "Template/Red");
    cube2->setCastShadows(true);
    cubeNode2->attachObject(cube2);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);

    Ogre::MeshManager::getSingleton().createPlane("ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
        100,100,20,20,true,1,5,5,Ogre::Vector3::UNIT_Y);

    Ogre::Entity *ent = window->getSceneManager()->createEntity("GroundEntity", "ground");
    ent->setMaterialName("Template/Red");
    window->getSceneManager()->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    /*Ogre::ManualObject* manual = window->getSceneManager()->createManualObject("manual");
    manual->begin("Template/Red", Ogre::RenderOperation::OT_TRIANGLE_LIST);

    manual->position(-10.0, -10.0, 0.0); manual->normal(0,0,1); manual->textureCoord(0,0);
    manual->position( 10.0, -10.0, 0.0); manual->normal(0,0,1); manual->textureCoord(1,0);
    manual->position( 10.0,  10.0, 0.0); manual->normal(0,0,1); manual->textureCoord(1,1);
    manual->position(-10.0,  10.0, 0.0); manual->normal(0,0,1); manual->textureCoord(0,1);
    manual->position(-10.0, -10.0, 0.0); manual->normal(0,0,1); manual->textureCoord(0,0);

    manual->triangle(0,1,2);
    manual->triangle(2,3,4);

    manual->end();

    manual->setCastShadows(true);

    Ogre::MaterialManager::getSingleton().getByName("Template/Red")->getTechnique(0)
            ->getPass(0)->setShadingMode(Ogre::ShadeOptions::SO_PHONG);

    Ogre::SceneNode* planeNode = window->getSceneManager()->getRootSceneNode()->createChildSceneNode();
    planeNode->setPosition(Ogre::Vector3(0,0,-0.5));
    planeNode->attachObject(manual);*/

    return true;
}

bool ObjectRenderer::deinitialize() {
    return true;
}

bool ObjectRenderer::cycle() {
    float x = sin(cycleCounter() / 1000.0) * 10;
    float y = cos(cycleCounter() / 1000.0) * 10;
    logger.info("pos") << x << " " << y << " " << sqrt(x*x + y*y + 100);

    window->getCamera()->setPosition(Ogre::Vector3(x, y, 10));
    window->getCamera()->lookAt(Ogre::Vector3(0, 0, 0.5));

    return true;
}

Ogre::ManualObject* ObjectRenderer::createCubeMesh(Ogre::String name, Ogre::String matName) {

   Ogre::ManualObject* cube = new Ogre::ManualObject(name);
   cube->begin(matName);

   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,0);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(0,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(-0.5,-0.5,1.0);cube->normal(-0.666667,-0.333333,0.666667);cube->textureCoord(1,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(0,1);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(1,1);
   cube->position(0.5,-0.5,1.0);cube->normal(0.408248,-0.816497,0.408248);cube->textureCoord(0,0);
   cube->position(0.5,-0.5,0.0);cube->normal(0.666667,-0.333333,-0.666667);cube->textureCoord(1,0);
   cube->position(-0.5,-0.5,0.0);cube->normal(-0.408248,-0.816497,-0.408248);cube->textureCoord(0,0);
   cube->position(-0.5,0.5,1.0);cube->normal(-0.408248,0.816497,0.408248);cube->textureCoord(1,0);
   cube->position(0.5,0.5,0.0);cube->normal(0.408248,0.816497,-0.408248);cube->textureCoord(0,1);
   cube->position(-0.5,0.5,0.0);cube->normal(-0.666667,0.333333,-0.666667);cube->textureCoord(1,1);
   cube->position(0.5,0.5,1.0);cube->normal(0.666667,0.333333,0.666667);cube->textureCoord(0,0);

   cube->triangle(0,1,2);      cube->triangle(3,1,0);
   cube->triangle(4,5,6);      cube->triangle(4,7,5);
   cube->triangle(8,9,10);      cube->triangle(10,7,8);
   cube->triangle(4,11,12);   cube->triangle(4,13,11);
   cube->triangle(14,8,12);   cube->triangle(14,15,8);
   cube->triangle(16,17,18);   cube->triangle(16,19,17);
   cube->end();

   return cube;
}
