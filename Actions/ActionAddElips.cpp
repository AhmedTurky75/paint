#include "ActionAddElips.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\Figures\CElips.h";

ActionAddElips::ActionAddElips(ApplicationManager* pApp) :Action(pApp) {}

//Execute the action
void ActionAddElips::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	if (UI.isFilled == 1) {
		SqrGfxInfo.isFilled = true;
	}
	else {
		SqrGfxInfo.isFilled = false;
	}
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Triangle data from the user

	pGUI->PrintMessage("New Elips: Click at the first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Elips: Click at the second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->ClearStatusBar();


	//Step 3 - Create a Triangle with the parameters read from the user
	CElips* R = new CElips(P1, P2, SqrGfxInfo);

	//Step 4 - Add the Triangle to the list of figures
	pManager->AddFigure(R);
}
