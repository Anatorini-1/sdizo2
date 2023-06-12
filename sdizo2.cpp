#include <iostream>
#include "Array.h"
#include "Matrix.h"
#include "GraphFactory.h"
#include "ListOfLists.h"
#include "GraphProcessor.h"
#include <cstdio>
#include "Tester.h"
#include "MinHeap.h"
#include "CLI.h"
/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/

using namespace std;



int main()
{
	CLI* c1 = new CLI();
	c1->run();
	delete c1;
}

