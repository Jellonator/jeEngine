/*  You can't put typedefs in .cpp files without having some weird linkage crap, so yeah.
 *  I could delete this file, but I won't. Don't ask why.
 *
 *  I could probably write some joke code if I wanted to though.
 *  This entire file is entirely dedicated to random crap
#include <iostream>
#define cloud butt
void ofContract(){
	double jeopardy;
	long long time;
	auto bots = "rollout";
	char* b = "hue\0";
	char** c = &b;
	char*** d = &c;
	char**** e = &d;
	char***** f = &e;
	std::cout << ****f << std::endl;

	bool ian;
	int elligence;

	bool that = true;
	(true==that);

	uint to=that?               0:1;

	int oYourButt_C=3;
}
*/
//the following jooke only makes sense if you have colored comments
/***//* *//***//* *//***//***//***//* *//***/
/***//* *//***//* *//* *//***//* *//* *//***/
/***//***//***//* *//* *//***//* *//* *//***/
/***//* *//***//* *//* *//***//* *//* *//* */
/***//* *//***//* *//***//***//***//* *//***/
/* 330 byte implimentation of jeManager.h
#include <map>
#include <memory>
using namespace std;
template<class K,class V,class R>
struct M{
void newResource(K k, R r){this->f[k]=r;}
shared_ptr<V>getResource(K k){
if(this->p[k].expired()){
auto r=make_shared<V>(this->f[k]);
this->p[k]=r;
return r;
}else
return this->p[k].lock();
}
map<K,R> f;
map<K,weak_ptr<V>>p;
};
*/

