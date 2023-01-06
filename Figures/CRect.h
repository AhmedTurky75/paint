#ifndef CRect_H
#define CRect_H

#include "CFigure.h"

class CRect : public CFigure
{
private:
	Point TopLeftCorner;
	Point BottomRightCorner;
public:
	CRect();
	CRect(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	bool isInside(int x, int y);
	//Turky
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
};

#endif
