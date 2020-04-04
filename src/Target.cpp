#include "Target.hpp"

Target::Target(Image& target) :target_(target), backgroundColor_({ 0,0,0 }){
}

Target::~Target() {
	mainColors_.clear();
	mainLABColors_.clear();
}



void Target::identifyBackgroundColor() {

	backgroundColor_ = target_.getTableau()[0][0];

}

Pixel Target::getBackgroundColor() const{
	return backgroundColor_;
}

vector<ColorPixel>&Target::getMainColors(){

	return mainColors_;
}

Image& Target::getTarget() {
	return target_;
}

bool Target::alreadyThere(LAB pixelLAB, int deltaEMainColors) {
	for (auto i : mainLABColors_) {
		if (CIEDE2000(pixelLAB, i) <= deltaEMainColors) {
			return true;
		}
	}
	return false;
}

void Target::identifyColors(int deltaEBackGround, int deltaEMainColors) {
	//deltaEBackground: if deltaE superior to that value we consider that the pixel doesn't belong to the background.
	//deltaEMainColors: if deltaE superior to that value we consider the 2 colors to be differents.
	identifyBackgroundColor();
	Pixel** pixels = target_.getTableau();
	LAB backgroundLAB = toLAB(getBackgroundColor());
	int hauteur = target_.getHauteur();
	int largeur = target_.getLargeur();
	for(int i=0; i<hauteur;i++)
		for(int j = 0; j < largeur; j+=2) {
			LAB pixelLAB = toLAB(pixels[i][j]);
			if (CIEDE2000(backgroundLAB, pixelLAB) > deltaEBackGround) {
				if (!alreadyThere(pixelLAB, deltaEMainColors)) {
				mainLABColors_.push_back(pixelLAB);
				ColorPixel cp;
				cp.color = pixels[i][j];
				cp.position.x = j;
				cp.position.y = i;
				mainColors_.push_back(cp);
			}
			}
		}
	
}

void Target::crop()
{
	int hauteur = target_.getHauteur();
	int largeur = target_.getLargeur();

	Rectangle rect;
	rect.coin1.x = getCoordinateFirstPixel(1, 1);
	rect.coin1.y = getCoordinateFirstPixel(1, 0);
	rect.coin2.x = getCoordinateFirstPixel(0, 1);
	rect.coin2.y = getCoordinateFirstPixel(0, 0);

	cout << rect.coin1.x <<" " << rect.coin1.y << endl;
	cout << rect.coin2.x << " " << rect.coin2.y << endl;
	
	target_ = target_.extraireRectangle(rect);

	

	
}

int Target::getCoordinateFirstPixel(bool coin1, bool x)
{
	int hauteur = target_.getHauteur();
	int largeur = target_.getLargeur();

	Pixel bgColor = getBackgroundColor();
	LAB bgLAB = toLAB(bgColor);
	Pixel** pixels = target_.getTableau();

	if (x) {
		if (coin1) {
			for (int i = 0; i < largeur; i++)
				for (int j = 0; j < hauteur; j++)
					if (CIEDE2000(bgLAB, toLAB(pixels[j][i])) > 10)
						return i;
		}
		else {
			for (int i = largeur - 1; i > -1; i--)
				for (int j = 0; j < hauteur; j++)
					if (CIEDE2000(bgLAB, toLAB(pixels[j][i])) > 10)
						return i;
		}
	}
	else {
		if(coin1){
			for (int i = 0; i < hauteur; i++)
				for (int j = 0; j < largeur; j++)
					if (CIEDE2000(bgLAB, toLAB(pixels[i][j])) > 10)
						return i;
		}
		else {
			for (int i = hauteur - 1; i > -1; i--)
				for (int j = 0; j < largeur; j++)
					if (CIEDE2000(bgLAB, toLAB(pixels[i][j])) > 10)
						return i;
		}
	}
}

