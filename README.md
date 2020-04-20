## HOW IT WORKS:

The whole process is divived into steps managed by different classes. This READ ME gives a description of each step. It can change anytime, _if you think any of those steps could be done in a better way then update it._

Let's call T the image to be found and S the image to be searched.
### Analysis:
The program must first acquire data on the image T.
- Class Analyser
- determining T main color and shape.
- computing color ratio, colors that have really low ratio are discarded to get rid of unwanted "image corruption".
- T pixels belonging to background are given color A while others are given  color B. 



### Search: 
The program can then start looking for the image T.
- Class Searcher
- If a pixel has a color resembling T main colors recursive construction starts.
- recursive construction records the position of the pixel then checks all the adjacent pixels and if any of them has color resembling the main colors then the algorithm starts over on these pixels. 
- **Collected pixels must then be prepared for a serie of tests:**
- collected pixels are sent in an image C of size Z1 proportional to the size Z2 of T.
- **Serie of tests**
- #1 color ratio, #2 image size
- to eliminate candidates with very low probability of being T
- these are eliminatory-tests means C is immediately destroyed if not passed
- if passed Z1 is resized so Z1 = Z2 
- C then contains all the extracted pixels and some new pixels of color A added to fill the matrix. Extracted pixels in image S are given a specific unique color so the program doesn't rescan pixels. 
- it keeps looping through those sub steps until all pixels have been scanned. 

### Results:
- for all retained images C a final test #3 is run to determine which is the closest to t
- class results
- test #3 compares color distribution within the picture 
- to run the test pixels of original color (not A) are given color B. 
- pixel subtraction is performed with image T
The equations of subtraction:
- A-A = Green
- A-B = Red
- B-A = Red
- B-B = Green
- the image with highest number of Green pixels is highlighted in S


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

**Ideas for new features:**
- A database of pictures of thousands of differents objects so we can tell the program to look for a "TV", a "lion" or anything
specific without providing a picture. 
- The database could have many pictures of the same object under different angles and coloration for better recognition
- Self improving algorithms by trial and error. The algorithm would suggest what he thinks is a "car" for example and a human would confirm or reject. The algorithm will have to adapt consequently to provide better suggestions.


_keep this README updated!_


