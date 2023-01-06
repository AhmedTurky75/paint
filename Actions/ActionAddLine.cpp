
#include "../Actions/ActionAddLine.h" 
#include "../Figures/CLine.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"


ActionAddLine::ActionAddLine(ApplicationManager* pApp) :Action(pApp) {}

//Execute the action
void ActionAddLine::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Triangle data from the user

	pGUI->PrintMessage("New Line: Click at the first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Line: Click at the second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);


	pGUI->ClearStatusBar();


	//Step 3 - Create a Triangle with the parameters read from the user
	CLine* R = new CLine(P1, P2, SqrGfxInfo);

	//Step 4 - Add the Triangle to the list of figures
	pManager->AddFigure(R);
}
