#ifndef CTria_H
#define CTria_H

#include "CFigure.h"

class CTria : public CFigure
{
private:
	Point firstPoint;
	Point secondPoint;
	Point thirdPoint;
public:
	CTria();
	CTria(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	bool isInside(int x, int y);
	//Turky
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
};

#endif
