
#include <Python.h>
#include <stdio.h>
#include <string.h>
#include "PythonCaller.h"

void pythonInit()
{
	// Set PYTHONPATH TO working directory
	setenv("PYTHONPATH",".",1);

	// Initialize the Python Interpreter
	Py_Initialize();
}

void pythonEnd()
{	
	// Finish the Python Interpreter
	Py_Finalize();
}

//z is string 
//i is int
void callString(char* moduleName, char* functionName, char* callArg)
{
	PyObject* pValue = Py_BuildValue("(z)", callArg);
	call(moduleName, functionName, pValue);
}

void callInt(char* moduleName, char* functionName, int val)
{
	PyObject* pValue = Py_BuildValue("(i)", val);
	call(moduleName, functionName, pValue);
}

void callTriInts(char* moduleName, char* functionName, int val1, int val2, int val3)
{
	PyObject* pValue = Py_BuildValue("(iii)", val1, val2, val3);
	call(moduleName, functionName, pValue);
}


int call(char* moduleName, char* functionName,  PyObject* pValue)
{
	PyObject *pName, *pModule, *pDict, *pFunc, *presult;

	//Check input 
	if(PyTuple_Check(pValue) == 0)
	{
		return 0;
	}

	// Build the name object
	pName = PyString_FromString(moduleName);

	// Load the module object
	pModule = PyImport_Import(pName);

	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);

	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, functionName);

	if (PyCallable_Check(pFunc))
	{
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
}
