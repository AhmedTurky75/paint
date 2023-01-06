#include "CTria.h"

CTria::CTria()
{
	figureType = TRIANGLE;
}
CTria::CTria(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	secondPoint = P2;
	thirdPoint = P3;
	figureType = TRIANGLE;
}


void CTria::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Rect on the screen	
	pGUI->DrawTria(firstPoint, secondPoint, thirdPoint, FigGfxInfo, Selected);


}

bool CTria::isInside(int x, int y)
{



	/* Calculate area of triangle ABC */
	float A = 0.5 * abs(firstPoint.x * (secondPoint.y - thirdPoint.y) + secondPoint.x * (thirdPoint.y - firstPoint.y) + thirdPoint.x * (firstPoint.y - secondPoint.y)); //a,b,c
	/* Calculate area of triangle PBC */
	float A1 = 0.5 * abs(x * (secondPoint.y - thirdPoint.y) + secondPoint.x * (thirdPoint.y - y) + thirdPoint.x * (y - secondPoint.y)); //x,a,b
	/* Calculate area of triangle PAC */
	float A2 = 0.5 * abs(firstPoint.x * (y - thirdPoint.y) + x * (thirdPoint.y - firstPoint.y) + thirdPoint.x * (firstPoint.y - y)); //x,a,c
	/* Calculate area of triangle PAB */
	float A3 = 0.5 * abs(firstPoint.x * (secondPoint.y - y) + secondPoint.x * (y - firstPoint.y) + x * (firstPoint.y - secondPoint.y)); //x,b,c

	/* Check if sum of A1, A2 and A3 is same as A */

	return (A == A1 + A2 + A3);
}

void CTria::Save(ofstream& OutFile) {
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
	OutFile << thirdPoint.x;
	OutFile << ' ';
	OutFile << thirdPoint.y;
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

void  CTria::Load(ifstream& Infile) {

	Infile >> ID;
	Infile >> firstPoint.x;
	Infile >> firstPoint.y;
	Infile >> secondPoint.x;
	Infile >> secondPoint.y;
	Infile >> thirdPoint.x;
	Infile >> thirdPoint.y;

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