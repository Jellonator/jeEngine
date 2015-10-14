#include "../jeMain.h"
#include "jeTime.h"
#include <iostream>
namespace JE{
namespace TIME{
	int time = 0;
	int frames = 0;
	double seconds = 0;
	int ptime = 0;
	float dt = 0;
	double _dt = 0;
	double fps = 0;
	double limit = -1;
	bool printFPS = false;
	void setDeltaTimeLimit(double limit){
		JE::TIME::limit = limit;
	}
	void calculate(){
		//set ptime to current time
		ptime = time;
		//add 1 to frame count; get the time.
		frames ++;
		time = SDL_GetTicks();
		//calculate the delta time.
		_dt = double(time - ptime)/1000.0;
		//if dt is non-zero
		if (time-ptime != 0){
			//add dt to seconds, then calculate the FPS(This is why dt must be non-zero)
			seconds += _dt;
		}
		//If a second has passed, then reset seconds and frames to 0.
		if (seconds > 1){
			fps = (double(frames)/double(seconds));
			if (printFPS) std::cout << "JE-FPS: " << fps << "\n";
			seconds = 0;
			frames = 0;
		}
		//cout << time << endl;
		if (_dt > limit && limit > 0) _dt = limit;
		if (_dt < 0) _dt = 0;
	}
};
}
