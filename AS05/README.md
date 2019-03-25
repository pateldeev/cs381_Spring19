# AS05: 3-D Motion and Mouse Selection with given architecture
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
  * LSHIFT+A/D : Yaw camera
  * LSHIFT+W/S : Pitch camera
  * R : Reset camera position and orientation
  * T : Toggle camera mode (attach/detach camera from selected object)
* Object Selection
  * TAB : Select next object
  * LSHIFT+TAB : Add next object to current selection group
  * LEFT_CLICK: Select nearest object to click
  * LSHIFT+LEFT_CLICK : Add nearest object to click to current selection group
* Moving Selected Object(s)
  * UP_ARROW/DOWN_ARROW : change desired speed
  * RIGHT_ARROW/LEFT_ARROW : change desired heading
  * PG_UP/PG_DOWN : change desired altitude (will only work if object is capable of flying)
  * SPACE : reset object speed, heading, and altitude to default values
* Adding Controls to Selected Object(s)
  * CENTER_CLICK : Add target location
  * RIGHT_CLICK : Add another target object to intercept

## Extra Credit
* Shift-selection (can select/control multiple entities)
* Third person camera viewpoint for selected entity (T key attaches camera to selected entity)
* Group mouse selection (via LSHIFT+LEFT_CLICK)
* Ability for entities to intercept each other (RIGHT_CLICK) and automatically go to desired location (CENTER_CLICK)
