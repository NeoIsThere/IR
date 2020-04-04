#pragma once
/**
 * \struct Point
 * \brief  Un point en 2D
 *
 * Un point avec des coordonnées en X et Y, en pixels.
 */

#include <iostream>

using namespace std;


struct Point
{
	unsigned x;
	unsigned y;
};


/**
 * \struct Rectangle
 * \brief  Un rectangle.
 *
 * Un rectangle est représenté par deux points, dont chacun possède des
 * coordonnées en X et en Y. Le premier point est le coin bas-gauche et l'autre
 * est le coin haut-droit.
 */
struct Rectangle
{
	Point coin1;
	Point coin2;
};


/**
 * \struct Pixel
 * \brief  Enregistrement qui représente un pixel RGB24.
 *
 * Un pixel RGB24 possède les trois couleurs rouge, vert et bleu, dont
 * l'ordre dans la mémoire est BGR. Chaque couleur est représentée par un
 * entier non-signé à 8 bits.
 */
struct Pixel
{
	uint8_t b;
	uint8_t g;
	uint8_t r;


};



ostream& operator<<(ostream& os, Pixel pix);

ostream& operator<<(ostream& os, Point point);





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