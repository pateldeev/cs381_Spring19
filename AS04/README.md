# AS04: Implementation of Specific Architecture
Deev Patel - CS 381 <br>
Email: pateldeev@nevada.unr.edu

## Building & Running
I used eclipse to build and run the program. In order for everything to work, [Ogre](https://www.ogre3d.org/) v1.9 must be installed. Additionally, eclipse must be linked to the following libraries <br>
* OgreMain
* OgreOverlay
* OIS
* boost_system
<a/><br><br> Note: Eclipse must also be setup with the correct include directories for all the libraries (in addition to the 'include' directory of project itself). You may also need to change the *.cfg files so that they reference the correct paths for everything.

## Key & Controls
* Camera Movement - relative to viewing direction
  * W/S : Move camera along z-axis
  * A/D : Move camera along x-axis
  * E/F : Move camera along y-axis 
  * LShift+A/D : Yaw camera
  * LShift+W/S : Pitch camera
  * T: Toggle Camera mode: Attach/detach camera from main selected object
* Object Selection
  * TAB : Select next object
  * LSHIFT+TAB : Select previous object
  * LEFT_CLICK: Select object
  * RIGHT_CLICK: Multiple selection - all objects will move
* Moving Selected Object
  * UP_ARROW/DOWN_ARROW : change desired speed
  * RIGHT_ARROW/LEFT_ARROW : change desired heading
  * SPACE : reset object speed and heading to default values
  * PLUS/MINUS : move object up/down (only if it is flying)

## Extra Credit
* Flying entities (alien ships can move along the y-axis with +/- keys)
* Mouse selection (left click)
* Ability to control multiple objects at once (via right clicking)
* Third person camera viewpoint for selected object (T key attaches camera to selected object)
* Group mouse selection (via right clicking)
