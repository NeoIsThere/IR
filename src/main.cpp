#include "Global.hpp"
#include "Target.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <iomanip>
#include <iostream>
#include <string>

#include "cppitertools/range.hpp"


using namespace std;
using namespace iter;


int main() {

	
	initDebogageMemoire();
	bool ok;
	Image image;
	image.lireImage("sliced_orange.bmp");
	Target target(image);
	target.identifyBackgroundColor();
	target.identifyColors(10, 13);
	vector<ColorPixel> vect = target.getMainColors();
	target.crop();


	
	for (auto i : vect) {
		cout << "couleur: " << i.color;
		cout << "x: " << i.position.x << " y: " << i.position.y << endl;

	}
	
	Image image2 = target.getTarget();
	image2.ecrireImage("sliced_oranged_cropped.bmp");
	image.ecrireImage("sliced_orange2.bmp");

	



	/*
	for (int i = 0; i < targetCopy.getHauteur(); i++)
		for (int j = 0; j < targetCopy.getLargeur(); j++)
			if (tab[i][j].r ==16 && tab[i][j].g ==0 && tab[i][j].b ==145)
				cout << "y: " << i << " x:" << j << endl;
	
	*/

	
	
	/*
	
	Pixel c = { 102, 61, 0 };
	Pixel d = { 77, 46, 0 };


	LAB lab1 = toLAB(c);
	LAB lab2 = toLAB(d);

	cout << lab1.l << " " << lab1.a << " " << lab1.b << endl;
	cout << lab2.l << " " << lab2.a << " " << lab2.b << endl;

	cout << CIEDE2000(lab1, lab2);

	//couleurs similaires quand <11;

	*/
	
}

