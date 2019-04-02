# AS06: Entities with AI controls
Deev Patel - CS 381 <br>
Email: pateldeev@nevada.unr.edu

## Building & Running
I used eclipse to build and run the program. In order for everything to work, [Ogre](https://www.ogre3d.org/) v1.9 must be installed. Additionally, eclipse must be linked to the following libraries <br>
* OgreMain
* OIS
* boost_system
* alut
* openal
* ogg
* vorbisfile
<a/><br><br> Note: Eclipse must also be setup with the correct include directories for all the libraries (in addition to the 'include' directory of project itself). You may also need to change the *.cfg files so that they reference the correct paths for everything.

## Key & Controls
* Camera Movement - relative to viewing direction
  * W/S : Move camera along z-axis
   * +LSHIFT : Move at fast speed
  * A/D : Move camera along x-axis
   * +LSHIFT : Move at fast speed
  * R/F : Move camera along y-axis 
   * +LSHIFT : Move at fast speed
  * Z/X: Pitch camera
   * +LSHIFT : Rotate at fast speed
  * Q/E : Yaw camera
   * +LSHIFT : Rotate at fast speed
  * LCTR+R : Reset camera position and orientation
  * T : Toggle camera mode (attach/detach camera from selected object)
* Object Selection
  * TAB : Select next object
  * LSHIFT+TAB : Add next object to current selection group
  * LEFT_CLICK: Select nearest object to click
  * LSHIFT+LEFT_CLICK : Add nearest object to click to current selection group
  * RSHIFT+LEFT_CLICK+Movement : group mouse selection - select everything in box created by mouse movement
* Moving Selected Object(s)
  * UP_ARROW/DOWN_ARROW : change desired speed
  * RIGHT_ARROW/LEFT_ARROW : change desired heading
  * PG_UP/PG_DOWN : change desired altitude (will only work if object is capable of flying)
  * SPACE : reset object speed, heading, and altitude to default values. Also remove any AI commands
* Adding AI Controls to Selected Object(s)
  * CENTER_CLICK : Add MoveTo command at place of click
   * +LSHIFT : Queue command to back of list - will execute after all others are done
  * RIGHT_CLICK : Add Intercept command to interecept target under click
   * +LSHIFT : Queue command to back of list - will execute after all others are done
  * LCTR+RIGHT_CLICK : Add Follow command to follow target under click
   * +LSHIFT : Queue command to back of list - will execute after all others are done

## Bounding Box Colors
* Green : Main selected entity (hitting tab will increment to next entity) (hitting T will attach camera to this entity)
* Blue : Secondary selected entity(s) (commands will apply to these as well as green)
* Red : Target that is being intercepted by main selected entity (in green)
* Orange : Target that is being followed by main selected entity (in green)
* Black : Entity is not selected and being controlled by an AI
* N/A : Entity is not selected and not being controlled by an AI


## Extra Credit
* Group Selection (via RSHIFT+LEFT_CLICK+MouseMovement) and controls
* Selection sound for each entity
* Third person camera viewpoint for selected entity (T key attaches camera to selected entity)
* Follow command that has entity follow target instead of intercepting it (LCTR+RIGHT_CLICK)
