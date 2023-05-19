#include <iostream>
#include "Array.h"
#include "Matrix.h"
#include "GraphFactory.h"
#include "ListOfLists.h"
using namespace std;

int main()
{
	GraphFactory gf;
	gf.litsDirectedGraph(5, 40)->print();
	
	

}
