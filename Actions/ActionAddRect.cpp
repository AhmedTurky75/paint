#include "ActionAddRect.h"

#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\Figures\CRect.h";

ActionAddRect::ActionAddRect(ApplicationManager* pApp):Action(pApp) {}

//Execute the action
void ActionAddRect::Execute()
{
	Point P1, P2 ;

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


	//Step 1 - Read Rect data from the user

	pGUI->PrintMessage("New Rect: Click at the point of Top-Left Corner");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New Rect: Click at the point of Bottom-Right Corner");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);


	pGUI->ClearStatusBar();


	//Step 3 - Create a Rect with the parameters read from the user
	CRect* R = new CRect(P1, P2, SqrGfxInfo);

	//Step 4 - Add the Rect to the list of figures
	pManager->AddFigure(R);
}
