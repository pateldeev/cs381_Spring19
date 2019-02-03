# AS00: Modification of OGRE Turtorial # 1
Deev Patel - CS 381 <br>
Email: pateldeev@nevada.unr.edu

## Demo
I have included a video (called "demo.mp4") showing the program running on my machine.

## Building & Running
I used eclipse to build and run the program. In order for everything to work, [Ogre](https://www.ogre3d.org/) v1.9 must be installed. Additionally, eclipse must be linked to the following libraries <br>
* OgreMain
* OgreOverlay
* OIS
* boost_system
<br> Note: Eclipse must also be setup with the correct include directories for all the libraries (in addition to the 'include' directory of project itself). You may also need to change the *.cfg files so that they reference the correct paths for everything.

## Notes
For the most part, I just used the [code](https://www.cse.unr.edu/~sushil/class/381/tutorials/) from [Ogre Tutorial # 1](https://ogrecave.github.io/ogre/api/latest/tut__first_scene.html). However, I made some changes in order to display bounding boxes around each head and alter the window name. I also went ahead and moved the main() function to its own source file. I felt like this was a much cleaner layout for the project.
