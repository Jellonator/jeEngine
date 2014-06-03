#Line
##JE::Line
###Description
A class for lines and line collision/raytracing(in the future)

###Constructors
#####Line(float x1, float y1, float x2, float y2)
Creates a new line with coordinates.  
x1: first x position  
y1: first y position  
x2: second x position  
y2: second y position  

###Functions
#####bool testLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *ox = NULL, float *oy = NULL)
Tests two lines and outputs whether they collide and where they collided  
x1: first x position  
y1: first y position  
x2: second x position  
y2: second y position  
x3: third x position  
y3: third y position  
x4: fourth x position  
y4: fourth y position  
ox: pointer for x output(x coord where lines meet).  
oy: pointer for y output(y coord where lines meet).  
#####bool testLines(Line* a, Line* b, float *ox = NULL, float *oy = NULL)
a: first line to compare  
b: second line to compare  
ox: pointer for x output(x coord where lines meet).  
oy: pointer for y output(y coord where lines meet). 

###Variables
#####float x1
first x position  
#####float y1
first y position  
#####float x2
second x position  
#####float y2
second y position  
