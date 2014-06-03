#Time
##JE::TIME::
###Description
Namespace full of timing variables and functions 

###Functions
#####void calculate()
Function that calculates time, should only be called once by frame via JE::update()  
Do not use if you use JE::update()

###Variables
#####int time;
the time of the current frame.
#####int frames;
frame count.  Used to calculate FPS. Reset when seconds == 1.
#####float seconds;
Not really useful, just used to calculate FPS once a second.
#####int ptime;
the previous time.
#####float dt;
the delta time. The time between the last frame and the current frame.
#####float fps;
the frames per second.  Used for benchmarking.
