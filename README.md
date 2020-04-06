# IR



_If you think something could be done in a better way then do it but keep this readme up to date._

In the current version only bmp files are supported. The program will search image T within image S, the process takes 3 main steps: Analysis, Search, Results. 

### Analysis:

- Class Analyser
- T is first analyzed, the program determines its main colors and shape.
- The program computes color ratio, colors that have really low ratio are discarded just to get rid of potential "corrupted" pixels. 
- T pixels belonging to the background are given a specific color A and the others are given a specific color B. 



### Search: 

- Class Searcher
- If a pixel has a color resembling T's main colors the recursive construction algorithm starts.
- That algorithm record the position of the pixel then checks all the adjacent pixels and if any of them has color resembling the main colors then the algorithm starts over on these pixels and so on. When the recursion is over (the adjacent pixels do not have a color resembling main colors) the program turns all the pixels recorded into a concrete image C. 
- All pixels of C are sent in a rectangular size Z1 matrix proportional to the size Z2 of the T.
- A comparison of the color ratio of C and T is performed, if C ratios don't match then C is destroyed, or else a resize is done so that Z2 = Z1. 
- Image C contains all the extracted pixels and some new pixels added to fill the matrix. Those new pixels are given the color A while the extracted pixels are given the color B. Extracted pixels in image S are also given a specific unique color just so the program doesn't rescan the same pixels. 
- The scan then resumes and it keeps looping through those sub steps until all pixels have been scanned. 

### Results:
The candidates C obtained are compared with T by subtraction of pixels. Pixel subtraction only aims to compare the shape of 2 objects.
The equations of subtraction:

- Class Results
- A-A = Green
- A-B = Red
- B-A = Red
- B-B = Green
We output C images in descending order of number of Green pixels.

## **OOP**

Analyzer, Searcher and Results methods have already been described above.

**Other classes:**

Image: Class composed of a matrix of pixels and some methods to manipulate that matrix.

Pixels: Data structure containing R,G,B values.


## **MISC:**

**Color differentiation:** "Same color" is vague. How to mathematically compute the difference between 2 colors? We could consider the R,G,B 3D color space where R is the X axis, G the Y axis
and B the Z axis, each color would be a point and we would simply compute the distance between those 2 point but this method does not work since those distances don't match the human-perceived distance between colors. Some colors really close to each other in that space will be perceived as totally different. That's why we use CIE L*a*b* color space and the deltaE formula. In short the CIE thing is 
a color space that matches human perceived distances and deltaE calculates those distances. We use deltaE 2000 which is currently the most complicated, yet most accurate CIE color difference algorithm available. 
_TL;DR: To compare 2 colors convert their R,G,B to CIE L*a*b* then calculate delta E._

### **delta E table:**
- <= 1.0	Not perceptible by human eyes.
- 1 - 2	Perceptible through close observation.
- 2 - 10	Perceptible at a glance.
- 11 - 49	Colors are more similar than opposite
- 100	Colors are exact opposite.
