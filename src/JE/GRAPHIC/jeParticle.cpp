#include "JE/UTIL/jeMath.h"
#include "JE/UTIL/jeTime.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/GRAPHIC/jeParticle.h"
#include "JE/GRAPHIC/jeSpritemap.h"

namespace JE{namespace GRAPHICS{
Particle::Particle(float x, float y, float life, float angle, float speed, float bounce, float gravityX, float gravityY,
float slow, const std::shared_ptr<Emitter>& parent, int type, const std::shared_ptr<Spritemap>& spritemap,
int spritemapAnim, int spritemapType):JE::Entity(x, y){//such a long constructor .-.
	this->velocx = JE::MATH::Xangle(angle,speed);
	this->velocy = JE::MATH::Yangle(angle,speed);
	this->bounce = bounce;
	this->life = life;
	this->mlife = life;
	this->accelx = gravityX;
	this->accely = gravityY;
	this->slow = slow;
	this->parent = parent;
	this->type = type;
	//this->mask = this->parent->types[this->type]->hitbox;
	this->spritemap = NULL;
	this->use_spritemap = false;
	if (spritemap && (spritemapType == SPRITEMAP_TYPE_ANIM_INDIVIDUAL || spritemapType == SPRITEMAP_TYPE_FADE)){
		this->spritemap = std::shared_ptr<Spritemap>(new JE::GRAPHICS::Spritemap());
		this->spritemap->useTexture(spritemap->texture);
		this->spritemap->useData(*spritemap);
		this->spritemap->play(spritemapAnim, true);
		this->use_spritemap = true;
	}
	this->spritemapType = spritemapType;
}

Particle::~Particle(){
	//this->mask = NULL;
	//if (this->spritemap) delete this->spritemap;
}

void Particle::OnUpdate(){if (JE::TIME::dt < 0) return;
	this->life -= JE::TIME::dt;
	if (this->life > 0){
		this->velocx -= this->velocx*this->slow*JE::TIME::dt;
		this->velocy -= this->velocy*this->slow*JE::TIME::dt;
		this->velocx += this->accelx*JE::TIME::dt;
		this->velocy += this->accely*JE::TIME::dt;
			this->x += this->velocx*JE::TIME::dt;
			this->y += this->velocy*JE::TIME::dt;
		if (this->spritemap){
			if (this->spritemapType == SPRITEMAP_TYPE_ANIM_INDIVIDUAL) this->spritemap->update();
			else if (this->spritemapType == SPRITEMAP_TYPE_FADE) {
				std::shared_ptr<Emitter> emitter = this->parent.lock();
				float a = this->life / this->mlife;
				a = JE::MATH::normalize(a, 0.0f, 1-emitter->types[this->type].fadeAt);
				int n_frames = this->spritemap->getCurrentAnim().getFrameCount();
				int d = JE::MATH::clamp(int(a*n_frames), 0, n_frames - 1);
				this->spritemap->setFrame(d);
			}
		}
	}else{
		this->destroy();
	}
}
uint8_t Particle::getFade(){
	std::shared_ptr<Emitter> emitter = this->parent.lock();
	if (emitter->types[this->type].fade == FADE_ALPHA) {
			float a = this->life / this->mlife;
			a = JE::MATH::normalize(a, 0.0f, 1-emitter->types[this->type].fadeAt);
			int d = JE::MATH::clamp(int(a*255), 0, 255);
			return d;
	}else return 255;
}
void Particle::OnDraw(){
	std::shared_ptr<Emitter> emitter = this->parent.lock();
	if (this->spritemap){
		//this->spritemap->setColor(255,255,255,this->getFade());
		JE::GRAPHICS::setColor(255,255,255,this->getFade());
		this->spritemap->draw(emitter->x,emitter->y,0,shared_from_this());
	}
	else if (emitter->types[this->type].use_graphic) {
		//emitter->types[this->type].graphic.setColor(255,255,255,this->getFade());
		JE::GRAPHICS::setColor(255,255,255,this->getFade());
		emitter->types[this->type].graphic.draw(emitter->x,emitter->y,0,shared_from_this());
	}
	else if (emitter->types[this->type].use_spritemap) {
		//emitter->types[this->type].spritemap->setColor(255,255,255,this->getFade());
		JE::GRAPHICS::setColor(255,255,255,this->getFade());
		emitter->types[this->type].spritemap->draw(emitter->x,emitter->y,0,shared_from_this());
	}
}
EmitterType::EmitterType(){
	this->speed = 100;
	this->randSpeed = 0;
	this->angle = 0;
	this->randAngle = 360;
	this->slow = 0;
	this->randSlow = 0;
	this->life = 1;
	this->randLife = 0;
	this->bounce = 0.8;
	this->randBounce = 0;
	this->spawnX = 0;
	this->spawnY = 0;
	this->spawnXrand = 0;
	this->spawnYrand = 0;
	this->gravityX = 0;
	this->gravityY = 0;
	this->gravityXrand = 0;
	this->gravityYrand = 0;
	this->fade = FADE_NONE;
	this->fadeAt = 0;
	this->use_graphic = false;
	this->use_spritemap = false;
	this->spritemapType = SPRITEMAP_TYPE_NONE;
}
EmitterType::~EmitterType(){

}
Emitter::Emitter(float x, float y):Graphic(x, y), world(){
	this->world.disableSort();
	this->world.correct_remove = true;
}
Emitter::~Emitter(){

}
void Emitter::draw(float x, float y, float angle, const std::shared_ptr<Entity>& entity){
	float px = this->x;
	float py = this->y;
	this->x += x;
	this->y += y;
	if (entity != NULL){
		this->x += entity->x;
		this->y += entity->y;
	}

	this->world.draw();

	this->x = px;
	this->y = py;
}
void Emitter::newType(int type){
	for (int i = this->types.size()-1; i < type; i ++){
		this->types.emplace_back();
	}
}
void Emitter::emit(int type, float x, float y, int count){
	if ((int)this->types.size() <= type) this->newType(type);
	for (int i = 0; i < count; i ++){
		float sx = this->types[type].spawnX + JE::MATH::random(-this->types[type].spawnXrand, this->types[type].spawnXrand);
		float sy = this->types[type].spawnY + JE::MATH::random(-this->types[type].spawnYrand, this->types[type].spawnYrand);
		float life = this->types[type].life + JE::MATH::random(0, this->types[type].randLife);
		float angle = this->types[type].angle + JE::MATH::random(-this->types[type].randAngle, this->types[type].randAngle);
		float speed = this->types[type].speed + JE::MATH::random(0, this->types[type].randSpeed);
		float bounce = this->types[type].bounce + JE::MATH::random(0, this->types[type].randBounce);
		float gravityX = this->types[type].gravityX + JE::MATH::random(-this->types[type].gravityXrand, this->types[type].gravityXrand);
		float gravityY = this->types[type].gravityY + JE::MATH::random(-this->types[type].gravityYrand, this->types[type].gravityYrand);
		float slow = this->types[type].slow + JE::MATH::random(0, this->types[type].randSlow);
		//Group* group = this->types[type]->custom;
		//if (group == NULL) group = this->world;
		this->world.add(std::make_shared<Particle>(sx+x, sy+y, life, angle, speed, bounce, gravityX, gravityY, slow,
		shared_from_this(), type, this->types[type].spritemap, this->types[type].spritemapAnim, this->types[type].spritemapType));
	}
}
void Emitter::emit(int type, float x1, float x2, float y1, float y2, int count){
	for (int i = 0; i < count; i ++){
		this->emit(type, JE::MATH::random(x1, x2), JE::MATH::random(y1, y2),1);
	}
}
void Emitter::setGravity(int type, float x, float y, float randX, float randY){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].gravityX = x;
	this->types[type].gravityY = y;
	this->types[type].gravityXrand = randX;
	this->types[type].gravityYrand = randY;
}
void Emitter::setPos(float x, float y){
	this->x = x;
	this->y = y;
}
void Emitter::setSpawn(int type, float x, float y, float randX , float randY ){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].spawnX = x;
	this->types[type].spawnY = y;
	this->types[type].spawnXrand = randX;
	this->types[type].spawnYrand = randY;
}
void Emitter::setSpeed(int type, float angle, float speed, float rangle , float rspeed ){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].angle = angle;
	this->types[type].speed = speed;
	this->types[type].randAngle = rangle;
	this->types[type].randSpeed = rspeed;
}
void Emitter::setLife(int type, float life, float rlife ){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].life = life;
	this->types[type].randLife = rlife;
}
void Emitter::setBounce(int type, float bounce, float rbounce ){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].bounce = bounce;
	this->types[type].randBounce = rbounce;
}
void Emitter::setImage(int type, const std::shared_ptr<Image>& graphic){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].graphic.useTexture(graphic);
	this->types[type].use_graphic = true;
	this->types[type].use_spritemap = false;
	this->types[type].spritemap = NULL;
	this->types[type].spritemapType = SPRITEMAP_TYPE_NONE;
}
/*void Emitter::setCamera(Camera* camera){
	this->camera = camera;
}*/
/*void Emitter::setCollide(int type, int group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->collide = world.groups[group];
}
void Emitter::setCollide(int type, Group* group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->collide = group;
}*/
void Emitter::setSlow(int type, float slow, float rslow ){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].slow = slow;
	this->types[type].randSlow = rslow;
}
/*void Emitter::setHitbox(int type, JE::MASK::HitBox* hitbox){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->hitbox = hitbox;
}*/
void Emitter::update(float dt){
	for (unsigned int i = 0; i < this->types.size(); i ++){
		if (this->types[i].spritemapType == SPRITEMAP_TYPE_ANIM && this->types[i].use_spritemap){
			this->types[i].spritemap->update(JE::TIME::dt);
		}
	}
	this->world.update(dt);
}
void Emitter::setFadeType(int type, int fadeType, float start){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].fade = fadeType;
	this->types[type].fadeAt = start;
}
/*void Emitter::setWorld(int type, Group* group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type].custom = group;
}
void Emitter::setWorld(int type, int group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->custom = JE::world->groups[group];
}*/
void Emitter::setSpritemap(int type, const std::shared_ptr<Spritemap>& spritemap, int anim, int spritemapType){
	if ((int)this->types.size() <= type) this->newType(type);
	this->types[type].spritemap = std::make_shared<Spritemap>();
	this->types[type].spritemap->useTexture(spritemap->texture);
	this->types[type].spritemap->useData(*spritemap);
	this->types[type].spritemapType = spritemapType;
	this->types[type].spritemapAnim = anim;
	this->types[type].spritemap->play(anim, true);
	this->types[type].use_spritemap = true;
	this->types[type].use_graphic = false;
	//this->types[type].graphic = NULL;
}
};};
