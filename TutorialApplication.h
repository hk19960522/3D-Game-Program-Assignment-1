//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Chien-Yao Huang
\n
My ID: 0656651
\n
My Email: hk850522@gmail.com
\n Date: 2018/09/20

This is an assignment of 3D Game Programming
*/

////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	
	
    //
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
    // Add your own stuff.
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return None.
	*/
	void createViewport_00(void);
	/*!
	\brief Create a viewport

	Create a viewport for the screen that is on the corner.

	\return None.
	*/
	void createViewport_01(void);
	/*!
	\brief Create a camera

	Create a camera for the main screen.

	\return None.
	*/
	void createCamera_00();
	/*!
	\brief Create a camera

	Create a camera for the second screen.

	\return None.
	*/
	void createCamera_01();

	/*!
	\brief Create the main scene.

	In this scene, it contains two penguins and several cubes which is arranged in particular shape

	\return None.
	*/
	void createScene_00();
	/*!
	\brief Create the second scene.

	In this scene, it contains a sphere

	\return None.
	*/
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    //
    // Add your own stuff.
    //
	void changeViewport();
	
	
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
    // Add your own stuff.
    //
	bool playAnim;
	bool isUpward;
	float max_height;
	float min_height;
	float max_velo;
	Ogre::Vector3 velocity;
	Ogre::Vector3 up_acc;
	Ogre::Vector3 down_acc;
};


#endif // #ifndef __BasicTutorial_00_h_