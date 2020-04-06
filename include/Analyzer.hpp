#pragma once

#include "Image.hpp"



struct mainColor {
	Pixel color;
	Point firstAppearance;
	double nInstances;
	double ratio;
};


ostream& operator<<(ostream& os, mainColor& mc);

class Analyzer {
public:
	Analyzer(Image& target);
	~Analyzer();
	void identifyBackgroundColor();
	void identifyColors(int deltaEBackGround, int deltaEMainColors);
	void crop();
	void calculateColorRatio();
	Pixel getBackgroundColor() const;
	vector<mainColor>& getMainColors();
	vector<LAB>& getMainLabColors();
	Image& getTarget();
	int getNBackgroundPixels();
	void setPixelToColor(Pixel& pix, Pixel& color);
	

private:
	bool alreadyThere(LAB pixelLAB, int deltaEMainColors);
	int getCoordinateFirstPixel(bool coin1, bool x);
	Image target_;
	Pixel backgroundColor_;
	vector<LAB> mainLABColors_;
	vector<mainColor> mainColors_;
	int nBackgroundPixels_;

};