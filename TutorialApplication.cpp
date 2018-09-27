////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2018/09/20
////////////////////////////////////////
// Student Name:
// Student ID:
// Student Email:
//
////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
    //
    // add your own stuff
    //
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	// add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("LittleCam");
	mCamera->setPosition(Ogre::Vector3(0,350,0.001));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCamera = mCameraArr[0];
}


void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
    // add your own stuff
	mCamera = mCameraArr[1];
	Viewport* vp = mWindow->addViewport(mCamera, 1, 0, 0, 0.25, 0.25);
	//float Width = 0.25, Height = 0.25;

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.7, 0.7));
	vp->setOverlaysEnabled(false);
	mViewportArr[1] = vp;
	//mCamera = mCameraArr[0];
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];

	// ambient light and shadow
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// add light
	Light *light01 = mSceneMgr->createLight("Light1"); 
	light01->setType(Light::LT_POINT); 
	light01->setPosition(Vector3(150, 250, 100));
	light01->setDiffuseColour(1.0, 1.0, 0.0); 
	light01->setSpecularColour(1.0, 0.0, 1.0); 
	
	Light *light02 = mSceneMgr->createLight("Light2"); 
	light02->setType(Light::LT_POINT); 
	light02->setPosition(Vector3(-150, 300, 250));
	light02->setDiffuseColour(1.0, 1.0, 1.0); 
	light02->setSpecularColour(1.0, 0.0, 1.0); 
	
	// add plane
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 1500, 1500, 
		20, 20, 
		true, 
		1, 
		5, 5, 
		Ogre::Vector3::UNIT_Z);
	Entity *ent = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	// add penguin 
	ent = mSceneMgr->createEntity("Penguin01", "penguin.mesh");
	SceneNode *pNode01 = mSceneMgr->getRootSceneNode()->createChildSceneNode("PenguinNode01", Ogre::Vector3(0, 50, 0));
	pNode01->attachObject(ent);
	pNode01->scale(2, 3, 2);

	ent = mSceneMgr->createEntity("Penguin02", "penguin.mesh");
	SceneNode *pNode02 = mSceneMgr->getRootSceneNode()->createChildSceneNode("PenguinNode02", Ogre::Vector3(150, 20, 0));
	Ogre::Vector3 lookPos = pNode01->getPosition();
	lookPos.y = pNode02->getPosition().y; // look at the same height 

	pNode02->attachObject(ent);
	pNode02->lookAt(lookPos, Ogre::Node::TransformSpace::TS_WORLD, Ogre::Vector3::UNIT_Z);

	// test
	int numCubes = 72;
	int L = 255;
	for (int i = 0; i < numCubes; i++) {
		String name;
		genNameUsingIndex("CircleCube", i, name);
		ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		AxisAlignedBox bb =  ent->getBoundingBox();
		Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		Real x = 0, y = 0, z = -125;
		SceneNode *snode = mSceneMgr
				->getRootSceneNode()
				->createChildSceneNode();
		snode->attachObject(ent);
		double fx = i/(double) (numCubes-1); // in range [0,1]
		double h = (1+sin(fx*PI*4))*50; // height
		double circle_radius = 100;
		double x1 = circle_radius*cos(fx*PI*2);
		double z1 = circle_radius*sin(fx*PI*2);
		double unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x1, 50, z1);
	}

	for (int i = 0; i < numCubes; i++) {
		String name;
		genNameUsingIndex("RowCube", i, name);
		ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/Chrome");

		SceneNode *snode = mSceneMgr
				->getRootSceneNode()
				->createChildSceneNode();
		snode->attachObject(ent);
		AxisAlignedBox bb =  ent->getBoundingBox();
		Real cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		double fx = 2*i/(double) (numCubes-1); //i from 0 to numCubes-1
		double x = fx*L - L/2.0;
		double h = (1+cos(fx*3.1415*2.0))*20; // height
		Real unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x, 20, 125);
	}

    // add your own stuff

    /*
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);
    */
}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
	mSceneMgr = mSceneMgrArr[1];
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Light *light = mSceneMgr->createLight();
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(0.0, 0.0, 1.0);	
	light->setSpecularColour(0.0,0.0, 1.0);	 
	
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
	"ground01", 										
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			plane, 
			1000,1000, 	// width, height
			20,20, 		// x- and y-segments
			true, 		// normal
			1, 			// num texture sets
			5,5, 		// x- and y-tiles
			Vector3::UNIT_Z	// upward vector
		);
	Entity *ent = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

	ent = mSceneMgr->createEntity("Sphere", "sphere.mesh");
	ent->setMaterialName("Examples/green");
	SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->setPosition(0, 1, 0);
	snode->scale(1.2, 0.7, 0.2);
	snode->attachObject(ent);
}

void BasicTutorial_00::createViewports(void)
{
    //Do not modify
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
    //Do not modify
	createScene_00();
	createScene_01();
	mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	//mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    
    if (arg.key == OIS::KC_C ) {
        
        //How to clear ss?
        ss.str("");
        ss.clear();
        
        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camerea position?
        //-----------------------------
        //This is incorrect.
        //Vector3 pos = mCamera->getPosition();
        //-----------------------------
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Ogre::Vector3(98.14, 450.69, 964.20));
        mCameraMan->getCamera()
            ->setDirection(Ogre::Vector3(-0.01, -0.30, -0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
		mCameraMan->getCamera()
            ->setPosition(Ogre::Vector3(-1463.00, 606.45, -513.24));
        mCameraMan->getCamera()
            ->setDirection(Ogre::Vector3(0.88, -0.47, 0.10));
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
        //-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
		mCameraMan->getCamera()
            ->setPosition(Ogre::Vector3(-1356.16, 634.32, -964.51));
        mCameraMan->getCamera()
            ->setDirection(Ogre::Vector3(0.71, -0.44, 0.55));
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
		mCameraMan->getCamera()
            ->setPosition(Ogre::Vector3(40.39, 155.23, 251.20));
        mCameraMan->getCamera()
            ->setDirection(Ogre::Vector3(-0.02, -0.41, -0.91));
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
		mCameraMan->getCamera()
			->setPosition(Ogre::Vector3(19.94, 822.63, 30.79));
		mCameraMan->getCamera()
			->setDirection(Ogre::Vector3(0.00, -0.99, -0.11));
    }

    if (arg.key == OIS::KC_M ) {
		
		Camera *c_ptr = mCameraArr[0];
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());
		Ogre::Viewport* vp = mWindow->addViewport(
			c_ptr,
			1,
			0.0,
			0.0,
			0.45,
			0.3
			);
		vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
		c_ptr->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		mViewportArr[0] = vp;       // make sure to save the new pointer

		c_ptr = mCameraArr[1];
		vp = mWindow->addViewport(
			c_ptr,
			0
			);
		vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
		c_ptr->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		vp->setOverlaysEnabled(false);
		mViewportArr[1] = vp;  
		//changeViewport();
    }

    if (arg.key == OIS::KC_N ) {
        Camera *c_ptr = mCameraArr[0];
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());
		Ogre::Viewport* vp = mWindow->addViewport(
			c_ptr,
			0
			);
		vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
		c_ptr->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		mViewportArr[0] = vp;       // make sure to save the new pointer

		c_ptr = mCameraArr[1];
		vp = mWindow->addViewport(
			c_ptr,
			1, 
			0.6,
			0.5,
			0.4,
			0.3
			);
		vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
		c_ptr->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		vp->setOverlaysEnabled(false);
		mViewportArr[1] = vp; 
    }

	if (arg.key == OIS::KC_0) {
		
	}

    // Do not delete this line
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

void BasicTutorial_00::changeViewport()
{
	int order[2];
	float position[2][4];
	Ogre::ColourValue color[2];
	for (int i=0;i<2;i++) {
		order[i] = mViewportArr[i]->getZOrder();
		position[i][0] = mViewportArr[i]->getLeft();
		position[i][1] = mViewportArr[i]->getTop();
		position[i][2] = mViewportArr[i]->getWidth();
		position[i][3] = mViewportArr[i]->getHeight();
		color[i] = mViewportArr[i]->getBackgroundColour();
		mWindow->removeViewport(mViewportArr[i]->getZOrder());
	}
	
	for (int i=0;i<2;i++) {
		int j = 2-i-1;
		mCamera = mCameraArr[i];
		Viewport *vp = mWindow->addViewport(
			mCamera, order[j], 
			position[j][0], position[j][1], position[j][2], position[j][3]
			);
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()) );
		vp->setBackgroundColour(color[j]);
		mViewportArr[i] = vp;
		if (order[j] > order[i]) {
			vp->setOverlaysEnabled(false);
		}
	}

}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    // add your own stuff
    //
	printf("%d", flg);
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////