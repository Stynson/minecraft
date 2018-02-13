#include <iostream>
#include "renderSystem.h"

int _main_(int _argc, char** _argv)
{
	mc::ExampleCubes app("05-instancing", "Almafa");
	return entry::runApp(&app, _argc, _argv);
}
