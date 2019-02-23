# AS02: Multiple movable objects and Engine Architectures
Deev Patel - CS 381 <br>
Email: pateldeev@nevada.unr.edu

## Building & Running
I used eclipse to build and run the program. In order for everything to work, [Ogre](https://www.ogre3d.org/) v1.9 must be installed. Additionally, eclipse must be linked to the following libraries <br>
* OgreMain
* OgreOverlay
* OIS
* boost_system
<a/><br><br> Note: Eclipse must also be setup with the correct include directories for all the libraries (in addition to the 'include' directory of project itself). You may also need to change the *.cfg files so that they reference the correct paths for everything.

## Demo
I included a demo of the program running. It is called "demo.mp3"

## Key & Controls
* Camera Movement - relative to viewing direction
  * W/S : Move camera along z-axis
  * A/D : Move camera along x-axis
  * E/F : Move camera along y-axis 
  * LShift+A/D : Yaw camera
* Object Selection
  * TAB : Select next object
* Moving Selected Object
  * UP_ARROW/DOWN_ARROW : change z component of object velocity
  * RIGHT_ARROW/LEFT_ARROW : change x component of object velocity
  * PG_UP/PG_DOWN : change y component of object velocity
  * SPACE : reset object velocity to 0 

## Command Line Arguments
You can change various paramaters via the command line arugments. The program will display usage if you pass along the arugment of --help.
