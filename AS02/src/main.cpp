/*
 -----------------------------------------------------------------------------
 Filename: Main.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 This file contains the main driver function for the TutorialApplication.
 */

#include "TutorialApplication.h"

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct parameters {
	int surfaceHeight;
	std::string windowName;

	//default parameters
	parameters(void) :
		surfaceHeight(0), windowName("CS381_DeevPatel") {
	}
};

//function to parse command line arguments and get parameter values
bool parseCLArgs(int argc, char *argv[], parameters &p);

//function to display command line usage
void displayCLArgsUsage(void);

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
	{

	//load command line arguments
	parameters params;
	if (!parseCLArgs(argc, argv, params)) {
		std::cerr << "ERROR: could not parse command line arguments" << std::endl
			<< "Note you can run the program with default parameters by not providing any arguments." << std::endl;
		displayCLArgsUsage();
		return -1;
	}

	// Create application object
	TutorialApplication myApp(params.windowName, params.surfaceHeight);
	try {
		myApp.go();
	} catch (Ogre::Exception &e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred: " << e.getFullDescription() << std::endl;
#endif
	}

	return 0;
}

//function to display command line usage
void displayCLArgsUsage(void) {
	std::cout << std::endl << "COMMAND LINE ARGUMENT USAGE:" << std::endl
		<< "You can provide command line arguments by giving the variable name followed by the value (ie: -windowName <name>)" << std::endl
		<< "The various parameters don't have to be in order and if any are not provided, the default value will be used." << std::endl;
	std::cout << std::endl << "LIST OF POSSIBLE ARGUMENTS <default value>:" << std::endl << "-windowName <CS381_DeevPatel>" << std::endl
		<< "-surfaceHeight <0>" << std::endl << std::endl;
}

//function to parse command line arguments and get parameter values
bool parseCLArgs(int argc, char *argv[], parameters &p) {
	for (int i = 1; i < argc; ++i) { //get parameter values
		if (!std::strcmp(argv[i], "--help")) {
			displayCLArgsUsage();
		} else if (!std::strcmp(argv[i], "-windowName")) {
			if (++i < argc) {
				p.windowName = argv[i];
			} else {
				std::cerr << "No value provided for windowName parameter!" << std::endl;
				return false;
			}
		} else if (!std::strcmp(argv[i], "-surfaceHeight")) {
			if (++i < argc) {
				try {
					p.surfaceHeight = std::stoi(argv[i]);
				} catch (...) {
					std::cerr << "Could not make sense of surfaceHeight parameter value. Please give an integer value!" << std::endl;
					return false;
				}
			} else {
				std::cerr << "No value provided for surfaceHeight parameter!" << std::endl;
				return false;
			}
		} else {
			std::cerr << "ERROR: Could not understand command line argument: " << argv[i] << std::endl;
			return false;
		}
	}
	return true;
}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------

