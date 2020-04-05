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
	Image image;
	image.lireImage("sliced_orange.bmp");
	Target target(image);
	target.identifyBackgroundColor();
	target.crop();
	target.identifyColors(10, 13);
	vector<mainColor>& MC = target.getMainColors();
	vector<LAB>& ML = target.getMainLabColors();
	target.calculateColorRatio();
	

	//cout << MC.size() << endl;
	//cout << ML.size();


	Image image2 = target.getTarget();
	image2.ecrireImage("sliced_oranged_cropped.bmp");
	image.ecrireImage("sliced_orange2.bmp");




	/*
	int instances = 0;
	double pourcentage = 0;
	double nPixels = target.getTarget().getNPixels();
	double pourcentageBg = double(target.getNBackgroundPixels()) / nPixels;
	

	

	for (auto i : MC) {
		cout << i << endl;
		instances += i.nInstances;
		pourcentage += i.ratio;
	}

	
	cout << target.getNBackgroundPixels() + instances << endl;
	cout << nPixels << endl;
	cout << pourcentage + pourcentageBg << endl;
	

	*/
	



	
	

	/*

	Pixel violet = { 52,175,146 };
	Pixel bleu = { 52,175,171};
	Pixel cyan = { 52,138,175 };

	LAB violetL = toLAB(violet);
	LAB bleuL = toLAB(bleu);
	LAB cyanL = toLAB(cyan);

	cout << "violet cyan: " << CIEDE2000(violetL, cyanL) << endl;
	cout << "violet bleu " << CIEDE2000(violetL, bleuL) << endl;
	cout << "bleu cyan " << CIEDE2000(cyanL, bleuL) << endl;

	*/
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

