#include "JE.h"
#include <sstream>
namespace JE{
void print(std::string s){std::cout << s << std::endl;}
std::string toString(int number){
	std::ostringstream ss;
	ss << number;
	return ss.str();
}
int toInt(std::string string){
	int numb;
	std::istringstream(string) >> numb;
	return numb;
}
namespace GRAPHICS{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext glcontext;
	Color* backcolor;
	Color* forecolor;
	void draw(){
		/*glClearColor(((float)backcolor->r)/255.0f,((float)backcolor->g)/255.0f,((float)backcolor->b)/255.0f,((float)backcolor->a)/255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		world->draw();
	}
	void flip(){
		SDL_GL_SwapWindow(window);*/
		SDL_SetRenderDrawColor(renderer,backcolor->r,backcolor->g,backcolor->b,backcolor->a);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,forecolor->r,forecolor->g,forecolor->b,forecolor->a);
		world->draw();
	}
	void flip(){
		SDL_RenderPresent(renderer);
	}
};
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
		//add 1 to frame count; get the time.
		frames ++;
		time = SDL_GetTicks();
		//calculate the delta time.
		_dt = double(time - ptime)/1000.0;
		//if dt is non-zero
		if (_dt != 0){
			//add dt to seconds, then calculate the FPS(This is why dt must be non-zero)
			seconds += _dt;
		}
		//If a second has passed, then reset seconds and frames to 0.
		if (seconds > 1){
			fps = (double(frames)/double(seconds));
			if (printFPS) std::cout << "JE-FPS: " << fps << std::endl;
			seconds = 0;
			frames = 0;
		}
		//cout << time << endl;
		ptime = time;
		if (_dt > limit && limit > 0) _dt = limit;
		if (_dt < 0) _dt = 0;
	}
};
namespace MATH{
	float RAD = 0.0174532925f;
	float DEG = 57.295779515f;
	int getSign(float num){
		if (num == 0) return 0;
		return (num > 0) ? 1 : -1;
	}
	float random(float a, float b){
    float random = ((float)rand())/(float)RAND_MAX;
    float d = b-a;
    float r = random * d;
    return a + r;
	}
	float distance(float x1, float y1, float x2, float y2){
			return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
	float squareDistance(float x1, float y1, float x2, float y2){
			return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	}
	float Xangle(float angle, float distance, float x){return std::cos(RAD*angle)*distance+x;}
	float Yangle(float angle, float distance, float y){return std::sin(RAD*angle)*distance+y;}
	bool chance(float value){
		float num = JE::MATH::random(0, 100);
		if (value >= num) return true;
		return false;
	}
	bool chance(float a, float b){
		if (b == 0) return true;
		float c = a / b;
		c *= 100;
		return chance(c);
	}
	float getAngle(float x1, float y1, float x2, float y2){
		return std::atan2(y2 - y1, x2 - x1)*DEG;
	}
	float smoothTween(float pos, float to, float speed, float minSpeed){
		bool left = (pos < to);
		float distance = std::sqrt(std::abs(pos - to));
		speed *= distance;
		speed = std::max(speed, minSpeed);
		pos += speed * JE::TIME::dt * ((pos > to)? -1 : 1);
		if (!left != !(pos < to)) pos = to;
		return pos;
	}
	float clamp(float value, float min, float max){
		if (min > max) {float t = min; min = max; max = t;}
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
};
World* world;/**< \brief jeWorld* world, the active world. */
void init(){
	setWorld(new World());
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {std::cout << SDL_GetError() << std::endl;}
	if (IMG_Init(IMG_INIT_PNG) != 0) {std::cout << SDL_GetError() << std::endl;}
	std::cout << "JE: Initiated Engine." << std::endl;
	SDL_version ver;
	SDL_GetVersion(&ver);
	std::cout << "JE: Using SDL version " << JE::toString(ver.major) << "." << JE::toString(ver.minor) << "." << JE::toString(ver.patch) << std::endl;
}
void quit(){
	//SDL_GL_DeleteContext(GRAPHICS::glcontext);
	std::cout << "JE: Quit Engine." << std::endl;
	IMG_Quit();
	SDL_Quit();
}
void initWindow(std::string name, int x, int y, int w, int h, int wflags, int rflags){
	init();
	//SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
	//SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );

	//glEnable(GL_DEPTH_TEST);
	GRAPHICS::window = SDL_CreateWindow(name.c_str(), x, y, w, h, wflags);
    if (GRAPHICS::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::renderer = SDL_CreateRenderer(GRAPHICS::window, -1, rflags);
    if (GRAPHICS::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
	//GRAPHICS::glcontext = SDL_GL_CreateContext(GRAPHICS::window);
		//if (GRAPHICS::glcontext == NULL) {std::cout << SDL_GetError() << std::endl;}
		//else{

	//}
	GRAPHICS::backcolor = new GRAPHICS::Color();
	GRAPHICS::forecolor = new GRAPHICS::Color();
	GRAPHICS::setColor(255,255,255,255);
	GRAPHICS::setBackgroundColor(0,0,0,255);
    SDL_SetRenderDrawBlendMode(GRAPHICS::renderer, SDL_BLENDMODE_BLEND);
	//SDL_GL_CreateContext(GRAPHICS::window);

	// Specify prototype of function
	//glewExperimental = GL_TRUE;
	//glewInit();
	// Load address of function and assign it to a function pointer
	//GENBUFFERS glGenBuffers = (GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// or Linux:
	//GENBUFFERS glGenBuffers = (GENBUFFERS)glXGetProcAddress((const GLubyte *) "glGenBuffers");
	// or OSX:
	//GENBUFFERS glGenBuffers = (GENBUFFERS)NSGLGetProcAddress("glGenBuffers");

	// Call function as normal
	std::cout << "JE: Initiated Window." << std::endl;
}

void update(){
	TIME::calculate();
	JE::TIME::dt = JE::TIME::_dt;
	world->update();
}
std::string fileOpen(std::string file){
	std::ifstream in(file.c_str());
	std::string text = "";
	std::string temp = "";
	int i = 0;
	if (!in.is_open()) {
		std::cout << "JE: File " << file << " does not exist!" << std::endl;
		text += "JE: File ";
		text += file;
		text += " does not exist!";
		return (char*)text.c_str();
	}
	while (getline (in,temp))
	{
		i ++;
		//std::cout << i << ":\t" << temp << std::endl;
		text += temp;
		text += '\n';
	}
	//std::cout << text << std::endl;
	return text;
}
};
