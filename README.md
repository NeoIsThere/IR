# IR


### **RECOGNITION STEPS**
_If you think any of these steps could be done in a better way then do it in the better way but please update the README!_

The objective is to find something specific within an image. An image of what needs to be found must be provided.

The process takes 3 main steps: Analysis, Search, Results.

Let's call T the image of the object to be found and S the image the program will search.
T is first analyzed, the program determines its main colors and shape. T pixels belonging to the background are given a specific color A
and the others are given a specific color B.
When the analysis is complete, the program begins searching S, the trigger in that search is the color: if a pixel has a color resembling T's main colors the recursive construction algorithm starts.
That algorithm record the position of the pixel then checks all the adjacent pixels and if any of them has color resembling the main colors then the algorithm starts over on these pixels and so on. When the recursion is over (the adjacent pixels do not have a color resembling main colors) the program turns all the pixels recorded into a concrete image C. All pixels of C are sent in a rectangular size Z1 matrix proportional to the size Z2 of the T.
A resize is done so that Z2 = Z1. C contains all the extracted pixels and some new pixels added to fill
the matrix. Those new pixels are given the color A while the extracted pixels the color B. Extracted pixels on the source are also given a specific unique color just so the program doesn't rescan the same pixels over and over resulting in an infinite loop. 
The scan then resumes and it keeps looping through those sub steps until all pixels have been scanned. 


The candidates C obtained are compared with T by subtraction of pixels. Pixel subtraction only aims to compare the shape of 2 objects.
The equations of subtraction:
- A-A = Green
- A-B = Red
- B-A = Red
- B-B = Green
Like an AND gate where Green = 1 and Red = 0.

We output C images in descending order of number of Green pixels.

### **OOP**

Image: Class composed of a matrix of pixels and some methods to manipulate that matrix.

Pixels: Data structure containing R,G,B values.

Target: Class composed of an image and some methods to analyze that image.

Searcher: Class composed of an image and some methods to search within that image using the target.

### **INFO:**

COLOR DIFFERENCES: "Same color" is vague. How to mathematically compute the difference between 2 colors? We could consider the R,G,B 3D color space where R is the X axis, G the Y axis
and B the Z axis, each color would be a point and we would simply compute the distance between those 2 point but this method does not work since those distances don't match the human-perceived distance between colors. Some colors really close to each other in that space will be perceived as totally different. That's why we use CIE L*a*b* color space and the deltaE formula. In short the CIE thing is 
a color space that matches human perceived distances and deltaE calculates those distances. We use deltaE 2000 which is currently the most complicated, yet most accurate CIE color difference algorithm available. 
_TL;DR: To compare 2 colors convert their R,G,B to CIE L*a*b* then calculate delta E._

### **delta E table:**
- <= 1.0	Not perceptible by human eyes.
- 1 - 2	Perceptible through close observation.
- 2 - 10	Perceptible at a glance.
- 11 - 49	Colors are more similar than opposite
- 100	Colors are exact opposite.
