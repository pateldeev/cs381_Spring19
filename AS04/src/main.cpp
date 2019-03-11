/*
 -----------------------------------------------------------------------------
 Filename: Main.cpp
 -----------------------------------------------------------------------------
 Author: Deev Patel (For CS 381)
 -----------------------------------------------------------------------------
 This file contains the main driver function for Assignment 3.
 */

#include "Engine.h"

int main(int argc, char *argv[]) {

	Engine *engine = new Engine();

	engine->Init();
	engine->Run();
	engine->Cleanup();

	return 0;
}

