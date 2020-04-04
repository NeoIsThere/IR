#pragma once

#include "Image.hpp"

/*Finds main colors of target. Bottom left corner (0,0) is used to determine background color. Slight variations of background color allowed thanks to Delta E calculator. */

struct ColorPixel {
	Pixel color;
	Point position;
};

class Target {
public:
	Target(Image& target);
	~Target();
	void identifyBackgroundColor();
	void identifyColors(int deltaEBackGround, int deltaEMainColors);
	void crop();
	Pixel getBackgroundColor() const;
	vector<ColorPixel>& getMainColors();
	Image& getTarget();
	

private:
	bool alreadyThere(LAB pixelLAB, int deltaEMainColors);
	int getCoordinateFirstPixel(bool coin1, bool x);
	Image target_;
	Pixel backgroundColor_;
	vector<LAB> mainLABColors_;
	vector<ColorPixel> mainColors_;

};