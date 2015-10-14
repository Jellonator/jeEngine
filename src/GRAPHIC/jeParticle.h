#pragma once
#include <memory>
#include "../jeEntity.h"
#include "../jeWorld.h"
#include "jeGraphic.h"
#include "jeImage.h"
namespace JE{
class World;
namespace GRAPHICS{
enum FADE{FADE_NONE, FADE_ALPHA};
enum SPRITEMAP_TYPE{SPRITEMAP_TYPE_NONE, SPRITEMAP_TYPE_ANIM, SPRITEMAP_TYPE_FADE, SPRITEMAP_TYPE_ANIM_INDIVIDUAL};
class Spritemap;
class Emitter;
class Particle;
class EmitterType;

class Particle:public Entity{
	public:
		float velocx;
		float velocy;
		float accelx;
		float accely;
		float life;
		float mlife;
		float bounce;
		float slow;
		std::weak_ptr<Emitter> parent;
		std::shared_ptr<Spritemap> spritemap;
		bool use_spritemap;
		int spritemapType;
		int type;
		Particle(float x, float y, float life, float angle, float speed, float bounce, float gravityX, float gravityY, float slow,
			const std::shared_ptr<Emitter>& parent, int type, const std::shared_ptr<Spritemap>& spritemap, int spritemapAnim,
			int spritemapType);
		void OnUpdate();
		void OnDraw();
		uint8_t getFade();
		virtual ~Particle();
	protected:
	private:
};
class EmitterType{
	public:
		EmitterType();
		virtual ~EmitterType();
		//Group custom;
		//Group collide;
		Image graphic;
		bool use_graphic;
		//JE::MASK::HitBox hitbox;
		std::shared_ptr<Spritemap> spritemap;
		bool use_spritemap;
		int spritemapType;
		int spritemapAnim;
		float angle;
		float randAngle;
		float speed;
		float randSpeed;
		float life;
		float randLife;
		float bounce;
		float randBounce;
		float spawnX;
		float spawnY;
		float spawnXrand;
		float spawnYrand;
		float gravityX;
		float gravityY;
		float gravityXrand;
		float gravityYrand;
		float slow;
		float randSlow;
		int fade;
		float fadeAt;
};
class Emitter: public Graphic, public std::enable_shared_from_this<Emitter>{
	public:
		World world;
		//Camera camera;
		std::vector<EmitterType> types;
		void newType(int ID);
		void setGravity(int type, float x, float y, float randX = 0, float randY = 0);
		void setPos(float x, float y);
		void setSpawn(int type, float x, float y, float randX = 0, float randY = 0);
		void draw(float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& entity = NULL);
		void setSpeed(int type, float angle, float speed, float rangle = 0, float rspeed = 0);
		void setLife(int type, float life, float rlife = 0);
		void setBounce(int type, float bounce, float rbounce = 0);
		void setImage(int type, const std::shared_ptr<Image>& graphic);
		void setSpritemap(int type, const std::shared_ptr<Spritemap>& spritemap, int anim, int spritemapType);
		//void setCamera(Camera* camera);
		//void setCollide(int type, int group);
		//void setCollide(int type, Group* group);
		void setSlow(int type, float slow, float rslow = 0);
		void emit(int type, float x = 0, float y = 0, int count = 1);
		void emit(int type, float x1, float x2, float y1, float y2, int count = 1);
		//void setHitbox(int type, JE::MASK::HitBox* hitbox);
		void setFadeType(int type, int fadeType, float start);
		void update(float dt);
		//void setWorld(int type, Group* group);
		//void setWorld(int type, int group);
		Emitter(float x = 0, float y = 0);
		virtual ~Emitter();
	protected:
	private:
};
};};
