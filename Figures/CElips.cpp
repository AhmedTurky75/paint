#include "CElips.h"

CElips::CElips()
{
	figureType = ELLIPSE;
}
CElips::CElips(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	secondPoint = P2;
	figureType = ELLIPSE;

}


void CElips::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Rect on the screen	
	pGUI->DrawElips(firstPoint, secondPoint, FigGfxInfo, Selected);


}

bool CElips::isInside(int x, int y)
{
	Point center;
	center.x = 0.5 * (firstPoint.x + secondPoint.x);
	center.y = 0.5 * (firstPoint.y + secondPoint.y);
	float a = abs(firstPoint.x - secondPoint.x) / 2;
	float b = abs(firstPoint.y - secondPoint.y) / 2;
	float check = (pow(x - center.x, 2) / pow(a, 2)) + (pow(y - center.y, 2) / pow(b, 2));
	if (check <= 1)
		return true;

	return false;

}

void CElips::Save(ofstream& OutFile) {
	OutFile << figureType;
	OutFile << ' ';
	OutFile << ID;
	OutFile << ' ';
	OutFile << firstPoint.x;
	OutFile << ' ';
	OutFile << firstPoint.y;
	OutFile << ' ';
	OutFile << secondPoint.x;
	OutFile << ' ';
	OutFile << secondPoint.y;
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

void  CElips::Load(ifstream& Infile) {
	Infile >> ID;
	Infile >> firstPoint.x;
	Infile >> firstPoint.y;
	Infile >> secondPoint.x;
	Infile >> secondPoint.y;
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

void CElips::Resize(GUI* pGUI, float size)
{


}