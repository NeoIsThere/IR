#include "Analyzer.hpp"

ostream& operator<<(ostream& os, mainColor& mc)
{
	os << "Color: " << mc.color << endl;
	os << "Ratio: " << mc.ratio *100 << "%" << endl;
	os << "First appearance: " << mc.firstAppearance << endl;
	os << "Nombre instances: " << mc.nInstances << endl;
	return os;
}

Analyzer::Analyzer(Image& target) :target_(target), backgroundColor_({ 0,0,0 }), nBackgroundPixels_(0){
}

Analyzer::~Analyzer() {
	mainColors_.clear();
	mainLABColors_.clear();
}



void Analyzer::identifyBackgroundColor() {

	backgroundColor_ = target_.getTableau()[0][0];

}

Pixel Analyzer::getBackgroundColor() const{
	return backgroundColor_;
}

vector<mainColor>&Analyzer::getMainColors(){

	return mainColors_;
}

vector<LAB>& Analyzer::getMainLabColors() {

	return mainLABColors_;
}


Image& Analyzer::getTarget() {
	return target_;
}

int Analyzer::getNBackgroundPixels()
{
	return nBackgroundPixels_;
}

void Analyzer::setPixelToColor(Pixel& pix, Pixel& color)
{
	pix.b = color.b;
	pix.g = color.g;
	pix.r = color.r;
	
}

bool Analyzer::alreadyThere(LAB pixelLAB, int deltaEMainColors) {
	bool alreadyThere = false;
	double delta=0;
	double deltaMin=101;
	int index=0;

	for (int i = 0; i < mainLABColors_.size();i++) {
		if ((delta= CIEDE2000(pixelLAB, mainLABColors_[i])) <= deltaEMainColors) {
			alreadyThere = true;
			if (delta < deltaMin) {
				deltaMin = delta;
				index = i;
			}
		}
	}
	if(alreadyThere)
	++mainColors_[index].nInstances;
	
	return alreadyThere;
}

void Analyzer::identifyColors(int deltaEBackGround, int deltaEMainColors) {
	//deltaEBackground: if deltaE superior to that value we consider that the pixel doesn't belong to the background.
	//deltaEMainColors: if deltaE superior to that value we consider the 2 colors to be differents.
	identifyBackgroundColor();
	Pixel** pixels = target_.getTableau();
	LAB backgroundLAB = toLAB(getBackgroundColor());
	int hauteur = target_.getHauteur();
	int largeur = target_.getLargeur();
	for(int i=0; i<hauteur;i++)
		for(int j = 0; j < largeur; j++) {
			LAB pixelLAB = toLAB(pixels[i][j]);
			if (CIEDE2000(backgroundLAB, pixelLAB) > deltaEBackGround) {
				if (!alreadyThere(pixelLAB, deltaEMainColors)) {
					mainLABColors_.push_back(pixelLAB);
					mainColor mc;
					mc.color = pixels[i][j];
					mc.firstAppearance.x = j;
					mc.firstAppearance.y = i;
					mc.nInstances = 1;
					mc.ratio = 0;
					mainColors_.push_back(mc);
					
				}
				Pixel white{ 255,255,255 };
				setPixelToColor(pixels[i][j], white);
			}
			else {
				++nBackgroundPixels_;
				Pixel black{ 0,0,0 };
				setPixelToColor(pixels[i][j], black);
			}
			

		}
	
}

void Analyzer::crop()
{
	int hauteur = target_.getHauteur();
	int largeur = target_.getLargeur();

	Rectangle rect;
	rect.coin1.x = getCoordinateFirstPixel(1, 1);
	rect.coin1.y = getCoordinateFirstPixel(1, 0);
	rect.coin2.x = getCoordinateFirstPixel(0, 1);
	rect.coin2.y = getCoordinateFirstPixel(0, 0);

	//cout << rect.coin1.x <<" " << rect.coin1.y << endl;
	//cout << rect.coin2.x << " " << rect.coin2.y << endl;
	
	target_ = target_.extraireRectangle(rect);

	

	
}

void Analyzer::calculateColorRatio()
{
	int nPixels = target_.getNPixels();
	for (int i = 0; i < mainColors_.size();i++) {
		mainColors_[i].ratio = mainColors_[i].nInstances / nPixels;
	}
	
}

int Analyzer::getCoordinateFirstPixel(bool coin1, bool x)
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

