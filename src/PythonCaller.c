
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
	//Py_INCREF(pValue);
	PyObject* pKW = PyString_FromString("address=0x70");
	//Py_INCREF(pKW);
	call(moduleName, functionName, pValue, pKW);
	Py_DECREF(pValue);
	Py_DECREF(pKW);
}

void callInt(char* moduleName, char* functionName, int val)
{
	PyObject* pValue = Py_BuildValue("(i)", val);
	//Py_INCREF(pValue);
	PyObject* pKW = PyString_FromString("address=0x71");
	//Py_INCREF(pKW);
	call(moduleName, functionName, pValue, pKW);
	Py_DECREF(pValue);
	Py_DECREF(pKW);
}

void callTriInts(char* moduleName, char* functionName, int val1, int val2, int val3)
{
	PyObject* pValue = Py_BuildValue("(iii)", val1, val2, val3);
	//Py_INCREF(pValue);
	PyObject* pKW = PyString_FromString("address=0x71");
	//Py_INCREF(pKW);
	call(moduleName, functionName, pValue, pKW);
	Py_DECREF(pValue);
	Py_DECREF(pKW);
}

int call(char* moduleName, char* functionName,  PyObject* pValue, PyObject* pKW)
{
	
	PyObject *pName, *pModule, *pDict, *pClass, *pFunc, *pInst, *pVal, *pMeth, *presult;

	//Check input 
	if(PyTuple_Check(pValue) == 0)
	{
		return 0;
	}
	
	//begin
	
	// Load the module object
	pModule = PyImport_ImportModule(moduleName);
	
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);		

	// pClass is also a borrowed reference 
	pClass = PyDict_GetItemString(pDict, "SevenSegment");
	
	//pInst is not borrowed
	pInst = PyInstance_New(pClass, NULL, pKW);
	
	pVal = Py_BuildValue("(O)", pInst);
	
	//loop
	// pFunc is also a borrowed reference 
	pFunc = PyObject_GetAttrString(pClass, "begin");
		
	//pMeth is not borrowed
	pMeth = PyMethod_New(pFunc, pInst, pClass);
	
	if (PyCallable_Check(pFunc))
	{
		presult=PyObject_CallObject(pMeth,pVal);
		PyErr_Print();
	} else 
	{
		PyErr_Print();
	}
	
	Py_DECREF(pMeth);
	
	
	
	
	//finally
	Py_DECREF(pInst);
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	//Py_DECREF(pName);
}
