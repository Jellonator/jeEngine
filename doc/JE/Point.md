#Point
##JE::Point
###Description
A class that represents a point

###Constructors
#####Point(float x = 0, float y = 0)
Creates a new point.  
x: x position of point.  
y: y position of point.

###Methods(class functions)
#####bool moveTo(float x, float y, float speed = 20, float dt = dt, float snap = 1, float dead = 0)
function that moves the point progessively closer to another point.  
float x: x coord to move to.  
float y: y coord to move to.  
speed: speed of which to move.  
dt: delta-time.  
snap: distance before the gap is closed.
dead: distance of which to stop moving.

###Variables
#####float x
x position of point.  
#####float y
y position of point.
