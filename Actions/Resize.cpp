#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include "Resize.h"
#include <iostream>

Resize::Resize(ApplicationManager* pApp) :Action(pApp)
{}

void Resize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("");


	if (pManager->AnySelected())
	{

		ActionType pAct;
		do {

			pGUI->CreateSizeBar();
			UI.InterfaceMode = MODE_SIZE;
			pAct = pGUI->MapInputToActionType();
			pGUI->PrintMessage("");
			cout << pAct << endl;

			switch (pAct) {
			case HALF:
				cout << "here";
				pManager->Resize_figure(pGUI, 0.5);
				pManager->UpdateInterface();
				break;
			case QUARTER:
				cout << "here";

				pManager->Resize_figure(pGUI, 0.25);
				pManager->UpdateInterface();
				break;
			case DOUBLE1:
				cout << "here";

				pManager->Resize_figure(pGUI, 2);
				pManager->UpdateInterface();
				break;
			case QUADRUPLE:
				cout << "here";

				pManager->Resize_figure(pGUI, 4);
				pManager->UpdateInterface();
				break;
			case BACK1:
				cout << "here";

				UI.InterfaceMode = MODE_DRAW;
				pGUI->CreateDrawToolBar();
				pGUI->PrintMessage("");
				break;
			}
		} while (pAct != BACK1);


	}//pGUI->CreateDrawToolBar();

	else
	{
		pGUI->PrintMessage("there isn't a selected figure.. Please Select :)");
		//Sleep(1000);
	}

	//ahmed
	pManager->setLastSaveState(false);
}