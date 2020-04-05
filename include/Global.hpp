#pragma once


#include <iostream>
#include <vector>


using namespace std;

/**
 * \struct Point
 * \brief  Un point en 2D
 *
 * Un point avec des coordonn�es en X et Y, en pixels.
 */
struct Point
{
	unsigned x;
	unsigned y;
};


/**
 * \struct Rectangle
 * \brief  Un rectangle.
 *
 * Un rectangle est repr�sent� par deux points, dont chacun poss�de des
 * coordonn�es en X et en Y. Le premier point est le coin bas-gauche et l'autre
 * est le coin haut-droit.
 */
struct Rectangle
{
	Point coin1;
	Point coin2;
};


/**
 * \struct Pixel
 * \brief  Enregistrement qui repr�sente un pixel RGB24.
 *
 * Un pixel RGB24 poss�de les trois couleurs rouge, vert et bleu, dont
 * l'ordre dans la m�moire est BGR. Chaque couleur est repr�sent�e par un
 * entier non-sign� � 8 bits.
 */
struct Pixel
{
	uint8_t b;
	uint8_t g;
	uint8_t r;


};



ostream& operator<<(ostream& os, Pixel pix);

ostream& operator<<(ostream& os, Point point);



template<typename T>
int findMin(vector<T>& vect) {
	int min = 0;
	if (vect.size() > 0) {
		min = vect[0];
		for (auto i : vect) {
			if (i < min)
				min = i;
		}
	}
	return min;
}


struct LAB
{
	/** Lightness */
	double l;
	/** Color-opponent a dimension */
	double a;
	/** Color-opponent b dimension */
	double b;
};

LAB toLAB(Pixel c);

double deg2Rad(const double deg);

constexpr double rad2Deg(const double rad);

double CIEDE2000(const LAB& lab1, const LAB& lab2);