
#ifndef PYTHON_CALLER_FUNCTIONS_INCLUDE
#define PYTHON_CALLER_FUNCTIONS_INCLUDE
void init();
void end();
//z is string 
//i is int
void callString(char* moduleName, char* functionName, char* callArg);
void callTriInts(char* moduleName, char* functionName, int val1, int val2, int val3);
int call(char* moduleName, char* functionName,  PyObject* pValue);
#endif
