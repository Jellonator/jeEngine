#include "jeParticle.h"
#include "JE.h"
namespace JE{namespace GRAPHICS{
Particle::Particle(float x, float y, float life, float angle, float speed, float bounce, float gravityX, float gravityY, float slow,
Emitter* parent, int type, Spritemap* spritemap, int spritemapType):JE::Entity(x, y){
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
	this->mask = this->parent->types[this->type]->hitbox;
	this->spritemap = NULL;
	if (spritemap && (spritemapType == SPRITEMAP_TYPE_ANIM_INDIVIDUAL || spritemapType == SPRITEMAP_TYPE_FADE)){
		this->spritemap = new JE::GRAPHICS::Spritemap();
		this->spritemap->useTexture(spritemap->texture);
		this->spritemap->useData(spritemap->data);
		this->spritemap->play(spritemap->anim, true);
	}
	this->spritemapType = spritemapType;
}
Particle::~Particle(){
	this->mask = NULL;
	if (this->spritemap) delete this->spritemap;
}
void Particle::OnUpdate(){if (JE::TIME::dt < 0) return;
	this->life -= JE::TIME::dt;
	if (this->life > 0){
		this->velocx -= this->velocx*this->slow*JE::TIME::dt;
		this->velocy -= this->velocy*this->slow*JE::TIME::dt;
		this->velocx += this->accelx*JE::TIME::dt;
		this->velocy += this->accely*JE::TIME::dt;
		if (this->parent->types[this->type]->collide && this->mask){
			JE::MASK::collideGroup(this,this->parent->types[this->type]->collide,this->velocx*JE::TIME::dt,this->velocy*JE::TIME::dt,true);
		}else{
			this->x += this->velocx*JE::TIME::dt;
			this->y += this->velocy*JE::TIME::dt;
		}
		if (this->spritemap){
			if (this->spritemapType == SPRITEMAP_TYPE_ANIM_INDIVIDUAL) this->spritemap->update();
			else if (this->spritemapType == SPRITEMAP_TYPE_FADE) {
				float a = this->life;
				float b = this->mlife;
				float c = 1-a/b;
				float r = c * this->spritemap->data->anims[this->spritemap->anim]->frames.size();
				int d = std::max(0,std::min((int)this->spritemap->data->anims[this->spritemap->anim]->frames.size() - 1,int(r)));
				this->spritemap->setFrame(d);
			}
		}
	}else{
		this->destroy();
	}
}
void Particle::OnDraw(){
	if (this->spritemap){
		if (this->parent->types[this->type]->fade == FADE_ALPHA) {
			if (this->life < this->mlife-this->parent->types[this->type]->fadeAt) {
				float a = this->life;
				float b = this->mlife - this->parent->types[this->type]->fadeAt;
				float c = a/b;
				c *= 255;
				int d = std::min(255,std::max(0,int(c)));
				this->spritemap->setColor(255,255,255,d);
			}else this->spritemap->setColor(255,255,255,255);
		}else this->spritemap->setColor(255,255,255,255);
		this->spritemap->draw(this->parent->x,this->parent->y,this->parent->camera,this);
	}
	else if (this->parent->types[this->type]->graphic) {
		if (this->parent->types[this->type]->fade == FADE_ALPHA) {
			if (this->life < this->mlife - this->parent->types[this->type]->fadeAt) {
				float a = this->life;
				float b = this->mlife - this->parent->types[this->type]->fadeAt;
				float c = a/b;
				c *= 255;
				int d = std::min(255,std::max(0,int(c)));
				//std::cout << d << std::endl;
				this->parent->types[this->type]->graphic->setColor(255,255,255,d);
			}else this->parent->types[this->type]->graphic->setColor(255,255,255,255);
		}else this->parent->types[this->type]->graphic->setColor(255,255,255,255);
		this->parent->types[this->type]->graphic->draw(this->parent->x,this->parent->y,this->parent->camera,this);
	}
	else if (this->parent->types[this->type]->spritemap) {
		if (this->parent->types[this->type]->fade == FADE_ALPHA) {
			if (this->life < this->mlife-this->parent->types[this->type]->fadeAt) {
				float a = this->life;
				float b = this->mlife - this->parent->types[this->type]->fadeAt;
				float c = a/b;
				c *= 255;
				int d = std::min(255,std::max(0,int(c)));
				this->parent->types[this->type]->spritemap->setColor(255,255,255,d);
			}else this->parent->types[this->type]->spritemap->setColor(255,255,255,255);
		}else this->parent->types[this->type]->spritemap->setColor(255,255,255,255);
		this->parent->types[this->type]->spritemap->draw(this->parent->x,this->parent->y,this->parent->camera,this);
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
	this->collide = NULL;
	this->hitbox = NULL;
	this->graphic = NULL;
	this->custom = NULL;
	this->spritemap = NULL;
	this->spritemapType = SPRITEMAP_TYPE_NONE;
}
EmitterType::~EmitterType(){
	if (this->hitbox) delete this->hitbox;
	if (this->spritemap) delete this->spritemap;
}
Emitter::Emitter(float x, float y):Graphic(x, y){
	this->camera = NULL;
	this->world = new World(JE_ORDER_HALF);
}
Emitter::~Emitter(){
	this->world->deleteAll();
	delete this->world;
}
void Emitter::draw(float x, float y, Camera* camera, Entity* entity){
	if (entity != NULL){
		this->x += entity->x;
		this->y += entity->y;
	}
	Camera*c = this->camera;
	if (camera != NULL){
		this->camera = camera;
	}
	this->x += x;
	this->y += y;
	this->world->draw();
	if (entity != NULL){
		this->x -= entity->x;
		this->y -= entity->y;
	}
	if (camera != NULL){
		this->camera = c;
	}
	this->x -= x;
	this->y -= y;
}
void Emitter::newType(int type){
	for (int i = this->types.size()-1; i < type; i ++){
		this->types.push_back(new EmitterType());
	}
}
void Emitter::emit(int type, float x, float y, int count){
	if (this->types.size() <= type) this->newType(type);
	for (int i = 0; i < count; i ++){
		float sx = this->types[type]->spawnX + JE::MATH::random(-this->types[type]->spawnXrand, this->types[type]->spawnXrand);
		float sy = this->types[type]->spawnY + JE::MATH::random(-this->types[type]->spawnYrand, this->types[type]->spawnYrand);
		float life = this->types[type]->life + JE::MATH::random(0, this->types[type]->randLife);
		float angle = this->types[type]->angle + JE::MATH::random(-this->types[type]->randAngle, this->types[type]->randAngle);
		float speed = this->types[type]->speed + JE::MATH::random(0, this->types[type]->randSpeed);
		float bounce = this->types[type]->bounce + JE::MATH::random(0, this->types[type]->randBounce);
		float gravityX = this->types[type]->gravityX + JE::MATH::random(-this->types[type]->gravityXrand, this->types[type]->gravityXrand);
		float gravityY = this->types[type]->gravityY + JE::MATH::random(-this->types[type]->gravityYrand, this->types[type]->gravityYrand);
		float slow = this->types[type]->slow + JE::MATH::random(0, this->types[type]->randSlow);
		Group* group = this->types[type]->custom;
		if (group == NULL) group = this->world;
		group->add(new Particle(sx+x, sy+y, life, angle, speed, bounce, gravityX, gravityY, slow, this, type,
																	this->types[type]->spritemap, this->types[type]->spritemapType));
	}
}
void Emitter::emit(int type, float x1, float x2, float y1, float y2, int count){
	for (int i = 0; i < count; i ++){
		this->emit(type, JE::MATH::random(x1, x2), JE::MATH::random(y1, y2),1);
	}
}
void Emitter::setGravity(int type, float x, float y, float randX, float randY){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->gravityX = x;
	this->types[type]->gravityY = y;
	this->types[type]->gravityXrand = randX;
	this->types[type]->gravityYrand = randY;
}
void Emitter::setPos(float x, float y){
	this->x = x;
	this->y = y;
}
void Emitter::setSpawn(int type, float x, float y, float randX , float randY ){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->spawnX = x;
	this->types[type]->spawnY = y;
	this->types[type]->spawnXrand = randX;
	this->types[type]->spawnYrand = randY;
}
void Emitter::setSpeed(int type, float angle, float speed, float rangle , float rspeed ){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->angle = angle;
	this->types[type]->speed = speed;
	this->types[type]->randAngle = rangle;
	this->types[type]->randSpeed = rspeed;
}
void Emitter::setLife(int type, float life, float rlife ){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->life = life;
	this->types[type]->randLife = rlife;
}
void Emitter::setBounce(int type, float bounce, float rbounce ){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->bounce = bounce;
	this->types[type]->randBounce = rbounce;
}
void Emitter::setImage(int type, Image* graphic){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->graphic = graphic;
	this->types[type]->spritemap = NULL;
	this->types[type]->spritemapType = SPRITEMAP_TYPE_NONE;
}
void Emitter::setCamera(Camera* camera){
	this->camera = camera;
}
void Emitter::setCollide(int type, int group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->collide = world->groups[group];
}
void Emitter::setCollide(int type, Group* group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->collide = group;
}
void Emitter::setSlow(int type, float slow, float rslow ){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->slow = slow;
	this->types[type]->randSlow = rslow;
}
void Emitter::setHitbox(int type, JE::MASK::HitBox* hitbox){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->hitbox = hitbox;
}
void Emitter::update(){
	for (int i = 0; i < this->types.size(); i ++){
		if (this->types[i]->spritemapType == SPRITEMAP_TYPE_ANIM){
			this->types[i]->spritemap->update(JE::TIME::dt);
		}
	}
	this->world->update();
}
void Emitter::setFadeType(int type, int fadeType, float start){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->fade = fadeType;
	this->types[type]->fadeAt = start;
}
void Emitter::setWorld(int type, Group* group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->custom = group;
}
void Emitter::setWorld(int type, int group){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->custom = JE::world->groups[group];
}
void Emitter::setSpritemap(int type, Spritemap* spritemap, int spritemapType){
	if (this->types.size() <= type) this->newType(type);
	this->types[type]->spritemap = spritemap;
	this->types[type]->spritemapType = spritemapType;
	this->types[type]->graphic = NULL;
}
};};//and entire short worth of lines :D
