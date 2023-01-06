#include "ApplicationManager.h"
#include "Actions\ActionAddLine.h"
#include "Actions\ActionAddSquare.h"
#include "Actions/ActionAddRect.h"
#include "Actions/ActionAddTria.h"
#include "Actions/ActionAddElips.h"
#include "Actions\ActionSelect.h"
#include "Actions\ActionDelete.h"
#include "Actions\ActionChangeColor.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionOpen.h"
#include "Actions\Resize.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	selectedfigure = NULL;
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	//Todo:: Sohaile ->
	ChangeColorFun currenColorFun = BORDER_SHAPE_FUN;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_LINE:
			newAct = new ActionAddLine(this);
			break;
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;
		case DRAW_RECT:
			newAct = new ActionAddRect(this);
			break;
		case DRAW_TRIA:
			newAct = new ActionAddTria(this);
			break;
		case DRAW_ELPS:
			newAct = new ActionAddElips(this);
			break;

		case CHNG_DRAW_CLR:
			//Todo:: Sohaile ->
			currenColorFun = BORDER_SHAPE_FUN;
			newAct = new ActionChangeColor(this, &currenColorFun);
			break;
		case CHNG_FILL_CLR:
			//Todo:: Sohaile ->
			currenColorFun = FILLED_SHAPE_FUN;
			newAct = new ActionChangeColor(this, &currenColorFun);
			break;
		case CHNG_BK_CLR:
			//Todo:: Sohaile ->
			currenColorFun = BACK_GROUND_FUN;
			newAct = new ActionChangeColor(this, &currenColorFun);
			break;


		case DRAW_SLCT:
			newAct = new ActionSelect(this);
			break;
			//v02
		case DEL:
			newAct = new ActionDelete(this);
			break;

		case UNDO:
			break;
		case REDO:
			break;
			//Turky
		case SAVE:
			///save to file txt
			newAct = new ActionSave(this);
			break;

		case LOAD:
			///load from txt

			if (FigCount > 0) {
				int msgboxID = MessageBoxW(
					NULL,
					(LPCWSTR)L"All figures will be deleted ,Are You Sure ?\n",
					(LPCWSTR)L"Warning",
					MB_ICONWARNING | MB_YESNOCANCEL | MB_DEFBUTTON2
				);
				switch (msgboxID)
				{
				case IDYES://case of confirmation
					newAct = new ActionOpen(this);
					break;
				case IDCANCEL://case of cnacel or deny the deletion
				case IDNO:
					pGUI->PrintMessage("Deletion canceled!");
					break;
				}
			}else{
				newAct = new ActionOpen(this);
			}
			
			break;

			///Afnan Resize v02
		case RESIZE:
			newAct = new Resize(this);

		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	///Add your code here to search for a figure given a point x,y	
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->isInside(x, y))
			return FigList[i];

	}
	return NULL;

	
}
//-----------------------
//Delete v02-----
void ApplicationManager::DeleteFigure()
{
	int flag = 1;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = 0;
			for (int j = i; j < FigCount - 1; j++)
			{
				swap(FigList[j], FigList[j + 1]);
			}
			delete FigList[FigCount - 1];
			FigList[FigCount - 1] = NULL;
			this->FigCount--;
			i--;
		}
	}
}

void ApplicationManager::changeFigDrawColor(Point p)
{

	for (int i = 0; i < FigCount; i++)
	{		
		if (FigList[i]->IsSelected()) {
			FigList[i]->ChngDrawClr(pGUI->pWind->GetColor(p.x, p.y));
			FigList[i]->SetSelected(false);
		}
	}
}

void ApplicationManager::changeFigFillColor(Point p)
{

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected()) {
			FigList[i]->ChngFillClr(pGUI->pWind->GetColor(p.x, p.y));
			FigList[i]->SetSelected(false);
		}
	}
}

bool ApplicationManager::AnySelected()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			return true;
		}
	}
	return false;
}

//Resize Figure 
void ApplicationManager::Resize_figure(GUI* pGUI, float size) const {
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->Resize(pGUI, size);
		}
	}
}

int ApplicationManager::GetFigureCount() {
	return FigCount;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pGUI->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////

//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
//Turky
void ApplicationManager::clearInterface()
{
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	FigCount = 0;
	pGUI->ClearDrawArea();
}



void ApplicationManager::saveAll(string fileName) {

	ofstream fout(fileName);
	if (fout.fail())
	{
		pGUI->PrintMessage("Can't open the output file");
	}
	fout << int(pGUI->getCrntDrawColor().ucRed);
	fout << ' ';
	fout << int(pGUI->getCrntDrawColor().ucGreen);
	fout << ' ';
	fout << int(pGUI->getCrntDrawColor().ucBlue);
	fout << ' ';
	fout << int(pGUI->getCrntFillColor().ucRed);
	fout << ' ';
	fout << int(pGUI->getCrntFillColor().ucGreen);
	fout << ' ';
	fout << int(pGUI->getCrntFillColor().ucBlue);
	fout << ' ';
	fout << int(pGUI->getBkGrndColor().ucRed);
	fout << ' ';
	fout << int(pGUI->getBkGrndColor().ucGreen);
	fout << ' ';
	fout << int(pGUI->getBkGrndColor().ucBlue);
	fout << "\n";
	fout << FigCount;
	fout << "\n";

	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(fout);

	fout.close();

}

void ApplicationManager::loadAll(ifstream& fin) {
	//unsigned char ucRed , ucGreen , ucBlue;
	int ucRed, ucGreen, ucBlue;

	fin >> ucRed;
	fin >> ucGreen;
	fin >> ucBlue;
	color drawColor(ucRed, ucGreen, ucBlue);
	pGUI->setCrntDrawColor(drawColor);

	fin >> ucRed;
	fin >> ucGreen;
	fin >> ucBlue;
	color fillColor(ucRed, ucGreen, ucBlue);
	pGUI->setCrntFillColor(fillColor);

	fin >> ucRed;
	fin >> ucGreen;
	fin >> ucBlue;
	color bkGrndColor(ucRed, ucGreen, ucBlue);
	pGUI->setBkGrndColor(bkGrndColor);


}
