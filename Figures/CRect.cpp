#include "CRect.h"
CRect::CRect() :CFigure()
{

	figureType = RECTANGLE;
}

CRect::CRect(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	figureType = RECTANGLE;
}


void CRect::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Rect on the screen	
	pGUI->DrawRect(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);
}
bool CRect::isInside(int x, int y)
{
	if (x >= TopLeftCorner.x && x <= BottomRightCorner.x  && y >= TopLeftCorner.y && y <= BottomRightCorner.y )
	{
		return true;
	}
	return false;
}

void CRect::Save(ofstream& OutFile) {
	OutFile << figureType;
	OutFile << ' ';
	OutFile << ID;
	OutFile << ' ';
	OutFile << TopLeftCorner.x;
	OutFile << ' ';
	OutFile << TopLeftCorner.y;
	OutFile << ' ';
	OutFile << BottomRightCorner.x;
	OutFile << ' ';
	OutFile << BottomRightCorner.y;
	OutFile << ' ';
	OutFile << int(FigGfxInfo.DrawClr.ucRed);
	OutFile << ' ';
	OutFile << int(FigGfxInfo.DrawClr.ucGreen);
	OutFile << ' ';
	OutFile << int(FigGfxInfo.DrawClr.ucBlue);
	OutFile << ' ';
	if (FigGfxInfo.isFilled) {
		OutFile << int(FigGfxInfo.FillClr.ucRed);
		OutFile << ' ';
		OutFile << int(FigGfxInfo.FillClr.ucGreen);
		OutFile << ' ';
		OutFile << int(FigGfxInfo.FillClr.ucBlue);
	}
	else {
		OutFile << -1;
	}
	OutFile << "\n";
}

void  CRect::Load(ifstream& Infile) {

	Infile >> ID;
	Infile >> TopLeftCorner.x;
	Infile >> TopLeftCorner.y;
	Infile >> BottomRightCorner.x;
	Infile >> BottomRightCorner.y;

	int ucRed, ucGreen, ucBlue;
	Infile >> ucRed;
	Infile >> ucGreen;
	Infile >> ucBlue;
	color drawColor = color(ucRed, ucGreen, ucBlue);
	FigGfxInfo.DrawClr = drawColor;
	Infile >> ucRed;
	if (ucRed == -1)
	{
		FigGfxInfo.isFilled = false;

	}
	else {

		Infile >> ucGreen;
		Infile >> ucBlue;
		color fillColor = color(ucRed, ucGreen, ucBlue);
		this->ChngFillClr(fillColor);
	}
	// FigGfxInfo.FillClr = fillColor;
	FigGfxInfo.BorderWdth = 3;
	SetSelected(false);
}