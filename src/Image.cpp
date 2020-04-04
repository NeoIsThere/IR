
#pragma region "Inclusions" //{


#include "Image.hpp"



using namespace std;
using namespace gsl;
using namespace iter;

#pragma endregion //}



#pragma region "Globaux" //{

#pragma region "Fonctions" //{



EnteteDib
lireEnteteFichier(fstream& fichier)
{
	EnteteDib entete;

	fichier.seekg(sizeof(EnteteBmp), ios::beg);
	fichier.read((char*)& entete, sizeof(EnteteDib));
	return entete;

}

Pixel** Image::allouerTableau(int largeur, int hauteur) const {
	Pixel** tableau = new Pixel*[hauteur];
	for (int i = 0; i < hauteur; i++)
		tableau [i] = new Pixel[largeur];
	return tableau;
}

Image::Image(unsigned largeur, unsigned hauteur):largeur_(largeur), hauteur_(hauteur),pixels_(allouerTableau(largeur,hauteur)) {}

Image::Image(unsigned largeur, unsigned hauteur, Pixel** pixels) :largeur_(largeur), hauteur_(hauteur), pixels_(pixels){}

Image::Image(const Image& im):Image(im.largeur_, im.hauteur_) {
	for (int i = 0; i < hauteur_; i++)
		for (int j = 0; j < largeur_; j++)
			pixels_[i][j] = im.pixels_[i][j];
}

Image& Image::operator=(const Image& image) {
	if (this != &image) {
		for (auto i : range(hauteur_)) {
			delete[] pixels_[i];
		}
		delete[] pixels_;

		largeur_ = image.getLargeur();
		hauteur_ = image.getHauteur();
		pixels_ = allouerTableau(largeur_, hauteur_);

		for (int i = 0; i < hauteur_; i++)
			for (int j = 0; j < largeur_; j++)
				pixels_[i][j] = image.pixels_[i][j];
	}
	return *this;
}

void
Image::lireDonneesImage(fstream& fichier)
{
	unsigned int pad = calculerTaillePadding();

	// done (Se positionner au début du tableau de pixels_ dans le fichier.)

	fichier.seekg(54, ios::beg);


	// done (Pour chaque ligne de l'image, lire la ligne et sauter le padding.)


	for (int i = 0; i < hauteur_; i++) {
		for (int j = 0; j < largeur_; j++) {
			fichier.read((char*)& pixels_[i][j], sizeof(Pixel));

		}
		fichier.seekg(pad, ios::cur);
		}
	}



void
Image::ecrireDonneesImage(fstream& fichier)
{
	char pad = 0;
	fichier.seekg(54, ios::beg);
	for (int i = 0; i < hauteur_; i++) {
		for (int j = 0; j < largeur_; j++) {
			fichier.write((char*)& pixels_[i][j], sizeof(Pixel));

		}

		fichier.write((char*)&pad, calculerTaillePadding());

		// done Pour chaque ligne de l'image, écrire la ligne puis écrire des bytes
		//       à zéro pour le padding.

	}
}


bool
Image::ecrireImage(const string& nomFichier)
{
	EnteteBmp entetebmp;
	EnteteDib entetedib;


	// done Ouvrir un fichier en écriture binaire.

		// done Si l'ouverture n'a pas échouée :
		// done Construire les entêtes à partir de l'image.
	fstream sortie;
	sortie.open(nomFichier, ios::binary | ios::out);

	if (sortie.is_open()) {
		entetebmp = construireEnteteBmp();
		entetedib = construireEnteteDib();

		// done Écrire les entêtes dans le fichier.
		sortie.write((char*)& entetebmp, sizeof(EnteteBmp));
		sortie.write((char*)& entetedib, sizeof(EnteteDib));
		ecrireDonneesImage(sortie);
		return true;

	}
	return false;
}




Image::~Image()
{
	// Si le tableau dynamique de l'image n'est pas nul :
	// TODO: Désallouer le tableau 2D.

	

	for (int i : range(hauteur_)) {
			delete[] pixels_[i];
		}
		delete[] pixels_;
		pixels_ = 0;
	}

Pixel** Image::getTableau()
{
	return pixels_;
}

int Image::getLargeur() const{
	return largeur_;
}

int Image::getHauteur() const{
	return hauteur_;
}


void Image::setLargeur(int largeur) {
	largeur_ = largeur;
}

void Image::setHauteur(int hauteur) {
	hauteur_ = hauteur;
}





bool Image::lireImage(const string& nomFichier)
{
	// TODO: Ouvrir le fichier en lecture binaire.

	fstream fichier(nomFichier, ios::in | ios::binary);


	// Si l'ouverture n'a pas échouée :
	if (fichier.is_open()) {
		// TODO: Lire l'entête DIB.
		EnteteDib dib = lireEnteteFichier(fichier);
		// TODO: Allouer une image selon le contenu du DIB.
		largeur_ = dib.largeurImage;
		hauteur_=dib.hauteurImage;
		pixels_ = allouerTableau(largeur_, hauteur_);

		// TODO: Lire les pixels_ du fichier.
		lireDonneesImage(fichier);
		return true;
 // TODO: Retourner ce qu'il faut.
		

	}
	else {
		cout << "Cannot find the file: " << nomFichier << endl;
		return false;
	}
}


Image Image::extraireRectangle( const Rectangle& zone) const
{
	
	// Si la zone demandée est valide :
	if (estZoneValide(zone)) {
		// TODO: Allouer une image de la taille de la zone à extraire.
		unsigned largeur = zone.coin2.x - zone.coin1.x;
		unsigned hauteur = zone.coin2.y - zone.coin1.y;
		unsigned debutX = zone.coin1.x, debutY = zone.coin1.y;

		Pixel** pixels = allouerTableau(largeur, hauteur);
		
		for (int i = 0; i < hauteur; i++)
			for (int j = 0; j < largeur; j++) {
				pixels[i][j] = pixels_[i + debutY][j + debutX];
			}
	
		return Image(largeur, hauteur, pixels);
		


	}

	return Image(0, 0);
	

}

/**
 * Convertit une image en nuance de gris.
 *
 * \param [in,out] image
 *        L'image à convertir.
 */
void
Image::convertirNoirEtBlanc()
{
	for (unsigned y : range(hauteur_)) {
		for (unsigned x : range(largeur_)) {
			Pixel& pixel = pixels_[y][x];
			uint8_t nuanceGris = uint8_t((int(pixel.r) + pixel.g + pixel.b) / 3);
			pixel = { nuanceGris, nuanceGris, nuanceGris };
		}
	}
}


/**
 * Détermine si les coins du rectangle sont dans le bon ordre, c'est-à-dire
 * \c coin1 est inférieur gauche et \c coin2 est supérieur droit.
 *
 * \param [in] rectangle
 *        Le rectangle à valider.
 *
 * \return Vrai si le rectangle est valide, faux sinon.
 */
bool
Image::estRectangleValide(const Rectangle& rectangle) const
{
	return rectangle.coin1.x <= rectangle.coin2.x and
		rectangle.coin1.y <= rectangle.coin2.y;
}


/**
 * Détermine si une zone donnée fait bien partie de l'image donnée.
 *
 * \param [in] image
 *        L'image contenant la zone.
 * \param [in] rectangle
 *        La zone à valider.
 *
 * \return Vrai si le rectangle est à l'intérieur de l'image. Faux sinon.
 */
bool
Image::estZoneValide( const Rectangle& rectangle) const
{
	return estRectangleValide(rectangle) and
		rectangle.coin2.x <= largeur_ and
		rectangle.coin2.y <= hauteur_;
}


/**
 * Construit un entête BMP avec les informations spécifiques au TD, mais en
 * laissant vide la taille du fichier.
 *
 * \return Un \c EnteteBmp valide et vide.
 */
EnteteBmp
construireBmpVide() 
{
	EnteteBmp resultat = {};
	resultat.id = BMP_ID;
	resultat.positionTableau = sizeof(EnteteBmp) + sizeof(EnteteDib);

	return resultat;
}


/**
 * Construit un entête DIB avec les informations spécifiques au TD, mais en
 * laissant vide les dimensions de l'image et du tableau de pixels_.
 *
 * \return Un \c EnteteDib valide et vide.
 */
EnteteDib
construireDibVide() 
{
	EnteteDib resultat = {};

	resultat.tailleEntete = sizeof(EnteteDib);
	resultat.nbPlansCouleur = 1;
	resultat.bpp = sizeof(Pixel) * 8;
	resultat.compression = COMPRESSION_BI_RGB;
	resultat.resolutionImpression[0] = resultat.resolutionImpression[1] = RESOLUTION_IMPRESSION;

	return resultat;
}


/**
 * Calcule le nombre d'octets de \e padding nécessaire pour chaque ligne
 * de pixels_ dans une image.
 *
 * \param [in] image
 *        L'image à traiter.
 *
 * \return Le nombre d'octet de padding.
 */
unsigned
Image::calculerTaillePadding() const
{
	unsigned tailleBruteLigne = largeur_ * sizeof(Pixel);

	return (ALIGNEMENT_PIXELS - (tailleBruteLigne % ALIGNEMENT_PIXELS)) %
		ALIGNEMENT_PIXELS;
}


/**
 * Calcule la taille de la séquence de pixels_ dans le fichier bitmap, en
 * incluant le padding nécessaire.
 *
 * \param [in] image
 *        L'image à traiter.
 *
 * \return Le nombre d'octet du tableau dans le fichier.
 */
unsigned
Image::calculerTailleTableau() const
{
	unsigned padding = calculerTaillePadding();
	unsigned tailleLigne = largeur_ * sizeof(Pixel) + padding;

	return tailleLigne * hauteur_;
}


/**
 * Construit un entête BMP à partir des dimensions d'une image.
 *
 * \param [in] image
 *        L'image à traiter.
 *
 * \return Un \c EnteteBmp complet.
 */
EnteteBmp
Image::construireEnteteBmp() const
{
	EnteteBmp resultat = construireBmpVide();

	resultat.tailleFichier = sizeof(EnteteBmp) + sizeof(EnteteDib) +
		calculerTailleTableau();

	return resultat;
}


/**
 * Construit un entête DIB à partir des dimensions d'une image.
 *
 * \param [in] image
 *        L'image à traiter.
 *
 * \return Un \c EnteteDib complet.
 */
EnteteDib
Image::construireEnteteDib() const
{
	EnteteDib resultat = construireDibVide();

	resultat.largeurImage = largeur_;
	resultat.hauteurImage = hauteur_;
	resultat.tailleTableau = calculerTailleTableau();

	return resultat;
}


/**
 * Trace une ligne horizontale sur une image entre deux points avec une
 * certaine épaisseur (largeur du trait).
 *
 * \param [in,out] image
 *        L'image à modifier.
 * \param [in] couleur
 *        Couleur du trait.
 * \param [in] ligne
 *        Les deux points de la lignes. Ils doivent être alignés en Y.
 * \param [in] epaisseur
 *        Épaisseur du trait, en pixels_.
 */
void
Image::tracerLigneHorizontale(Pixel couleur, const Point ligne[2], unsigned epaisseur)
{
	unsigned debutX = min(ligne[0].x, ligne[1].x);
	unsigned finX = max(ligne[0].x, ligne[1].x) + 1;

	unsigned debutY = ligne[0].y - min(epaisseur / 2, ligne[0].y);
	unsigned finY = min(debutY + epaisseur, hauteur_ - 1);

	for (unsigned y : range(debutY, finY))
		for (unsigned x : range(debutX, finX))
			pixels_[y][x] = couleur;
}


/**
 * Trace une ligne verticale sur une image entre deux points avec une
 * certaine épaisseur (largeur du trait).
 *
 * \param [in,out] image
 *        L'image à modifier.
 * \param [in] couleur
 *        Couleur du trait.
 * \param [in] ligne
 *        Les deux points de la lignes. Ils doivent être alignés en X.
 * \param [in] epaisseur
 *        Épaisseur du trait, en pixels_.
 */
void
Image::tracerLigneVerticale(Pixel couleur, const Point ligne[2], unsigned epaisseur)
{
	unsigned debutY = min(ligne[0].y, ligne[1].y);
	unsigned finY = max(ligne[0].y, ligne[1].y) + 1;

	unsigned debutX = ligne[0].x - min(epaisseur / 2, ligne[0].x);
	unsigned finX = min(debutX + epaisseur, largeur_ - 1);

	for (unsigned y : range(debutY, finY))
		for (unsigned x : range(debutX, finX))
			pixels_[y][x] = couleur;
}


/**
 * Dessine un carré plein sur une image.
 *
 * \param [in,out] image
 *        L'image à modifier.
 * \param [in] couleur
 *        Couleur du carré.
 * \param [in] centre
 *        Le centre du carré.
 * \param [in] dimension
 *        Taille du côté du carré, en pixels_.
 */
void
Image::dessinerCarre(Pixel couleur, const Point& centre, unsigned dimension)
{
	unsigned debutX = centre.x - min(dimension / 2, centre.x);
	Point ligne[2] = {
		{debutX                                        , centre.y},
		{min(debutX + dimension - 1, largeur_ - 1), centre.y}
	};

	tracerLigneHorizontale(couleur, ligne, dimension);
}


/**
 * Trace un contour de rectangle dans une image.
 *
 * \param [in,out] image
 *        L'image à modifier.
 * \param [in] couleur
 *        Couleur des pixels_ à tracer.
 * \param [in] rectangle
 *        Rectangle à tracer.
 * \param [in] epaisseur
 *        Épaisseur, en pixels_, des côtés du rectangle à tracer.
 */
void
Image::tracerContourRectangle(Pixel couleur, const Rectangle& rectangle, unsigned epaisseur)
{
	Point sommets[4];

	sommets[0] = rectangle.coin1;
	sommets[1] = { rectangle.coin2.x, rectangle.coin1.y };
	sommets[2] = rectangle.coin2;
	sommets[3] = { rectangle.coin1.x, rectangle.coin2.y };

	if (estZoneValide(rectangle))
		for (int i : range(4)) {
			Point ligne[2] = { sommets[i], sommets[(i + 1) % 4] };

			if (i % 2 == 0)
				tracerLigneHorizontale(couleur, ligne, epaisseur);
			else
				tracerLigneVerticale(couleur, ligne, epaisseur);

			dessinerCarre(couleur, sommets[i], epaisseur);
		}
}




	



#pragma endregion //}

#pragma endregion //}
