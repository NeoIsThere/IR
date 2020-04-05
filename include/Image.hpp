
#pragma once


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>

#include "gsl/span"
#include "cppitertools/range.hpp"
#include <iostream>

#include <vector>
#include "debogageMemoire.h"
#include "Global.hpp"


using namespace std;

#pragma endregion //}




#pragma region "Déclarations" //{

#pragma region "Macros" //{

#if defined(__GNUC__) || defined(__clang__)
#define PACKED_STRUCT(declaration) \
	declaration  __attribute__((__packed__))
#elif defined(_MSC_VER)
#define PACKED_STRUCT(declaration) \
	__pragma(pack(push, foo, 1)) declaration __pragma(pack(pop, foo))
#else
#error Compiler not supported.
#endif

#pragma endregion //}


#pragma region "Constantes" //{

static const unsigned ALIGNEMENT_PIXELS = 4;

static const unsigned BMP_ID = 0x4D42; // "BM"
static const unsigned COMPRESSION_BI_RGB = 0; // Pas de compression
static const unsigned RESOLUTION_IMPRESSION = 2835; // 72 DPI

#pragma endregion //}

#pragma region "Structures d'enregistrement" //{



/**
 * \struct Image
 * \brief  Enregistrement représentant une image.
 *
 * Une image possède à la base une largeur, une hauteur et une séquence de
 * pixels_.
 * <p>
 * Il est important de noter que les pixels_ sont organisés en un tableau de
 * lignes. La première dimension représente le numéro de ligne et la deuxième
 * dimension représente le numéro de colonne. Les coordonnées des pixels_ sont
 * donc en (Y,X), <b>PAS EN (X,Y)</b>.
 */



/**
 * \struct EnteteBmp
 * \brief  Entête BMP d'un bitmap.
 *
 * L'entête BMP d'une image bitmap vient en premier dans le fichier et le
 * format est toujours le même. Elle contient de l'information générale sur
 * le fichier d'image.
 */
PACKED_STRUCT(
	struct EnteteBmp
{
	uint16_t id;
	uint32_t tailleFichier;
	uint16_t inutilise[2];
	uint32_t positionTableau;
});


/**
 * \struct EnteteDib
 * \brief  Entête DIB d'un bitmap.
 *
 * L'entête DIB d'une image bitmap vient après l'entête BMP dans le fichier
 * et il existe beaucoup de formats différents. Elle contient de
 * l'information détaillée sur l'image et définit le format de pixel.
 * <p>
 * Dans ce TD, nous utilisons le format BITMAPINFOHEADER avec des pixels
 * RGB24.
 */
PACKED_STRUCT(
	struct EnteteDib
{
	uint32_t tailleEntete;
	int32_t  largeurImage;
	int32_t  hauteurImage;
	uint16_t nbPlansCouleur;
	uint16_t bpp;
	uint32_t compression;
	uint32_t tailleTableau;
	int32_t  resolutionImpression[2];
	uint32_t nbPalettes;
	uint32_t nbCouleursImportantes;
});

#pragma endregion //}


EnteteDib lireEnteteFichier(fstream&);




class Image{

public:
	Image(unsigned largeur = 0, unsigned hauteur = 0);

	Image(unsigned largeur, unsigned hauteur, Pixel** pixels);

	Image(const Image&);

	~Image();

	Image& operator=(const Image&);

	Pixel** getTableau();
	
	int getNPixels() const;

	int getLargeur() const;
	
	int getHauteur() const;

	void setLargeur(int largeur);

	void setHauteur(int hauteur);

	bool ecrireImage(const string&);

	bool lireImage(const string&);

	void convertirNoirEtBlanc();

	void tracerLigneHorizontale(Pixel, const Point[2], unsigned);

	void tracerLigneVerticale(Pixel, const Point[2], unsigned);

	void dessinerCarre(Pixel, const Point&, unsigned);

	void tracerContourRectangle(Pixel, const Rectangle&, unsigned);

	Image extraireRectangle(const Rectangle&) const;

private:
		void lireDonneesImage(fstream&);
		void ecrireDonneesImage(fstream&);
		bool estRectangleValide(const Rectangle&) const;
		unsigned calculerTaillePadding() const;
		unsigned calculerTailleTableau() const;
		EnteteBmp construireEnteteBmp() const;
		EnteteDib construireEnteteDib() const;
		bool estZoneValide(const Rectangle&) const;
		Pixel** allouerTableau(int largeur, int hauteur) const;
		unsigned largeur_;
		unsigned hauteur_;
		Pixel** pixels_;
		
};



#pragma endregion //}

