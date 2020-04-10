## HOW IT WORKS:

The whole process is divived into steps managed by different classes. This READ ME gives a description of each step. It is absolutely not permanent _if you think any of those steps could be done in a better way then change it._

Let's call T the image to be found and S the image to be searched.
### Analysis:

- Class Analyser
- determining T main color and shape.
- computing color ratio, colors that have really low ratio are discarded to get rid of unwanted "corruption".
- T pixels belonging to background are given color A while others are given  color B. 



### Search: 

- Class Searcher
- If a pixel has a color resembling T main colors recursive construction starts.
- recursive construction records the position of the pixel then checks all the adjacent pixels and if any of them has color resembling the main colors then the algorithm starts over on these pixels. 
- collected pixels are sent in an image C of size Z1 proportional to the size Z2 of the T.
- comparison of the color ratio of C and T is performed, if C ratios don't match C is destroyed
- or else Z1 is resized so Z1 = Z2 
- If not destroyed C contains all the extracted pixels and some new pixels added to fill the matrix. Those new pixels are given color A while the extracted pixels are given color B. Extracted pixels in image S are also given a specific unique color so the program doesn't rescan pixels. 
- it keeps looping through those sub steps until all pixels have been scanned. 

### Results:
The candidates C obtained are compared with T by subtraction of pixels. Pixel subtraction only aims to compare the shape of 2 objects.
The equations of subtraction:

- Class Results
- A-A = Green
- A-B = Red
- B-A = Red
- B-B = Green
We output C images in descending order of number of Green pixels.


## **MISC:**

In the current version only bmp files are supported. 

**Color differentiation:** "Same color" is vague. How to mathematically compute the difference between 2 colors? We could consider the R,G,B 3D color space where R is the X axis, G the Y axis
and B the Z axis, each color would be a point and we would simply compute the distance between those 2 point but this method does not work since those distances don't match the human-perceived distance between colors. Some colors really close to each other in that space will be perceived as totally different. That's why we use CIE L*a*b* color space and the deltaE formula. In short the CIE thing is 
a color space that matches human perceived distances and deltaE calculates those distances. We use deltaE 2000 which is currently the most complicated, yet most accurate CIE color difference algorithm available. 
_TL;DR: To compare 2 colors convert their R,G,B to CIE L*a*b* then calculate delta E._

**Delta E table:**
- <= 1.0	Not perceptible by human eyes.
- 1 - 2	Perceptible through close observation.
- 2 - 10	Perceptible at a glance.
- 11 - 49	Colors are more similar than opposite
- 100	Colors are exact opposite.

_keep this README updated!_
