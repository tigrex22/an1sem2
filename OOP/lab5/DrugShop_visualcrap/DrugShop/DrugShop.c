#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#include "tester.h"
#include "repository.h"
#include "controller.h"
#include "userinterface.h"
#include "undo.h"

/**
	*Initialize some drugs in application's database
*/
void initSomeDrugs(DrugController* ctr) {
	addDrug(ctr,1, "Algocalmin", "15%", 100);
	addDrug(ctr,2, "Borenar", "20%", 20);
	addDrug(ctr,3, "Tusin", "80%", 200);
	addDrug(ctr,4, "Paracetamol", "30%", 50);
	addDrug(ctr,5, "Strepsils", "55%", 30);
	addDrug(ctr, 6, "Ambroxol", "67%", 70);
}

int main()
{
	runAllTests();
	Node* undo = createUndoList();
	DrugRepo* repository = createRepo();
	DrugController* controller = createController(repository, undo);
	initSomeDrugs(controller);
	startUI(controller);
	destroyController(controller);
	_CrtDumpMemoryLeaks();
	system("pause");
    return 0;
}

