#include "GUI.h"
#include "iostream"
//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 60;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = GRAY;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames
	UI.isFilled = 0;
	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if (Key == 8) { 	//BackSpace is pressed
			if(Label.size()>0)
			Label.resize(Label.size() - 1);
		}
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_LINE: return DRAW_LINE;
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_TRIA: return DRAW_TRIA;
			case ITM_ELPS: return DRAW_ELPS;
				//Todo:: Sohaile ->
			case BORDER_SHAPE: return CHNG_DRAW_CLR;
			case FILLED_SHAPE: return CHNG_FILL_CLR;
			case BACK_GROUND: return CHNG_BK_CLR;

				// Turky
			case ITM_HEX: return DRAW_HEX;
			case ITM_DELETE: return DEL;
			case ITM_SELECT: return DRAW_SLCT;
			case ITM_RESIZE: return RESIZE;
			case ITM_EXIT: return EXIT;	
			case ITM_SAVE: return SAVE;
			case ITM_OPEN: return LOAD;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}else if (UI.InterfaceMode == MODE_SIZE)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{
			case ITM_BACK1:
				return BACK1;
			case ITM_QUARTER:
				return QUARTER;
			case ITM_HALF:
				return HALF;

			case ITM_DOUBLE:
				return DOUBLE1;
			case ITM_QUADRUPLE:
				return QUADRUPLE;
			default: return EMPTY;
			}
		}
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\Menu_Line.jpg";
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_TRIA] = "images\\MenuItems\\Menu_Tria.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	//Turky
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Menu_Hex.JPG";
	MenuItemImages[BORDER_SHAPE] = "images\\MenuItems\\Border.JPG";
	MenuItemImages[FILLED_SHAPE] = "images\\MenuItems\\Fill_shape.JPG";
	MenuItemImages[BACK_GROUND] = "images\\MenuItems\\Back_ground.JPG";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.JPG";
	MenuItemImages[ALL_COLORS] = "images\\MenuItems\\Colors.JPG";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\Menu_Delete.JPG";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.JPG";
	MenuItemImages[ITM_SENDTOBACK] = "images\\MenuItems\\Menu_SendToBack.JPG";
	MenuItemImages[ITM_BRINGTOFRONT] = "images\\MenuItems\\Menu_BringToFront.JPG";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\Menu_Undo.JPG";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\Menu_Redo.JPG";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Menu_Resize.JPG";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.JPG";
	MenuItemImages[ITM_OPEN] = "images\\MenuItems\\Menu_Open.JPG";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.JPG";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
//Todo:: Sohaile ->
void GUI::changeCrntDrawColor(Point p) const //change current drwawing color
{
	UI.DrawColor = pWind->GetColor(p.x, p.y);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

//Todo:: Sohaile ->
void GUI::changeCrntFillColor(Point p) const // change filling color
{
	UI.isFilled = 1;
	UI.FillColor = pWind->GetColor(p.x, p.y);
}
//////////////////////////////////////////////////////////////////////////////////////////

 //Todo:: Sohaile ->
void GUI::changeCrntBackGroungColor(Point p) const	// change  BackGroung 
{
	UI.BkGrndColor = pWind->GetColor(p.x, p.y);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

//Turky
color GUI::getBkGrndColor() const	//get current Background color
{
	return UI.BkGrndColor;
}
void GUI::setCrntDrawColor(color c ){
	UI.DrawColor = c;
}

void GUI::setCrntFillColor(color c) {
	UI.FillColor = c;
}

	void GUI::setBkGrndColor(color c){
		UI.BkGrndColor = c;
}
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//


//======================================================================================//
//								Line Drawing Functions								//
//======================================================================================//

void GUI::DrawLine(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

//======================================================================================//
//								Square Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
	

}

//======================================================================================//
//								Rectangle Drawing Functions								//
//======================================================================================//

void GUI::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
}


//======================================================================================//
//								Triangle Drawing Functions								//
//======================================================================================//

void GUI::DrawTria(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}


//======================================================================================//
//								Elips Drawing Functions								//
//======================================================================================//

void GUI::DrawElips(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);
}

//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Resize Shape								//
//======================================================================================//
//Afnan
void GUI::CreateSizeBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_SIZE;

	string MenuItemImages[SIZE_ITM_COUNT];

	MenuItemImages[ITM_BACK1] = "images\\MenuItems\\back.jpg";
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\quartter.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\hallf.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\two.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\four.jpg";


	///TODO: write code to create Size mode menu
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}


GUI::~GUI()
{
	delete pWind;
}

