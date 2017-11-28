
#include <Python.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

/*
 * This program will manage countdowns for Halo CE PowerUp Spawns
 *  main is an infinite loop that will allow map selection
 * 	once a map is selected by scrolling to it and pressing start
 * 		a run countdown method will begin to keep track of time
 * 		as well as percent cooldown remaining for each powerup
*/

const char* maps[5] = 
	{ 
		"Chill Out",
		"Damnation", 
		"Derelict", 
		"Hang 'Em High", 
		"Prisoner" 
	};

const char* powers[4] = 
	{ "Rocks", "Snipe", "Camo", "Ovy" };

const int cools[5][4] = 
	{ 
		{120, 30, 120, 60}, 
		{120, 30, 60, 60}, 
		{75, 30, 60, 60}, 
		{120, 30, 60, 60}, 
		{120, 30, 60, 60} 
	};
 
int main(int argc, char **argv)
{
 	char* outBuf[] = {"Pick an Option", "->Map Selection"}; 
	while(1)
	{
		mapSelection();
		break;
	}

} 

void mapSelection()
{			
	char* outBuf[] = {"Pick an Option", "->Map"}; 
	int map = 0;
	while(1)
	{
		countGame(map);
		map = map+1;
		break;
	}
}

void countGame(int map)
{

 	// Set PYTHONPATH TO working directory
	setenv("PYTHONPATH",".",1);

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;


	// Initialize the Python Interpreter
	Py_Initialize();


	// Build the name object
	pName = PyString_FromString((char*)"pythonTest");

	// Load the module object
	pModule = PyImport_Import(pName);

	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);


	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, (char*)"someFunction");

	if (PyCallable_Check(pFunc))
	{
		pValue=Py_BuildValue("(z)",(char*)"something");
		PyErr_Print();
		printf("Let's give this a shot!\n");
		presult=PyObject_CallObject(pFunc,pValue);
		PyErr_Print();
	} else 
	{
		PyErr_Print();
	}
	
	printf("Result is %d\n",PyInt_AsLong(presult));
	Py_DECREF(pValue);

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);

	// Finish the Python Interpreter
	Py_Finalize();

}
