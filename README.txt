The objective is to search&find an object within a picture. A picture of the object must be provided. Search criterias: color and shape

Search is done in 3 steps:

First the object to find (target) is analyzed.
The Target class determines the main colors and the shape of the object.

The picture is then analyzed to find the object.
The Picture class class scans pixels. The trigger in this research is color.
If a pixel has a color resembling main colors the recursive construction algorithm starts.
Starting on the pixel found it checks all the adjacent pixels, if they have a color resembling the main colors then
the function gets called on these pixels and so on.
When the recursion is over (the adjacent pixels do not have a color resembling main colors), the program turns
the object built with the recursion into a concrete image. All pixels are sent in a rectangular size matrix proportional to the size of the target.
A resize is done so that this new size = target size.
Finally all the pixels which have been extracted from the picture are given a specific color (which does not already exist in the image) so that the program knows
that these pixels should no longer be scanned then the scan resumes. It keep looping through those sub steps until all pixels have been scanned.

The candidates obtained are compared by subtraction of pixels. Pixel subtraction only aims to compare the shape of 2 objects.
For the 2 pictures (target and picture of object candidate) the pixels belonging to the background are given a fixed color A, the others take a fixed color B. The equations of subtraction:
A-A = Green
A-B = Red
B-A = Red
B-B = Green
It is the equivalent of an AND gate where Green = 1 and Red = 0.

We output the images in descending order of number of Green pixels.

//INFO:

COLOR DIFFERENCES: "Same color" is vague. How to mathematically compute the difference between 2 colors? We could consider the R,G,B 3D color space where R is the X axis, G is Y axis
and B is the Z axis, each color would be a point and we would simply compute the distance between those 2 point but this method does not work since those distances don't match the
human-perceived distance between colors. Some colors really close to each other will be perceived as totally different. That's why we use CIE L*a*b* and deltaE. In short the CIE thing is 
a color space that matches human perceived distances and deltaE calculates those distances. We use deltaE 2000 which is currently the most complicated, yet most accurate, CIE color difference algorithm 
available. 
TL;DR: To compare 2 colors convert both to CIE L*a*b* then calculate delta E.

delta E table:
<= 1.0	Not perceptible by human eyes.
1 - 2	Perceptible through close observation.
2 - 10	Perceptible at a glance.
11 - 49	Colors are more similar than opposite
100	Colors are exact opposite



