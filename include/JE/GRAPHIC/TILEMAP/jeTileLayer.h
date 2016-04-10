#pragma once
#include "../jeCanvas.h"
#include "../../jeMain.h"
#include "../../jeUtil.h"
#include "../../GL/jeModel.h"
#include "jeTileset.h"
#include "jeTilemapTile.h"
#include <memory>
#include <map>
#include <vector>

namespace JE{namespace GRAPHICS{

class TileLayer : public Graphic {
public:
	TileLayer(std::shared_ptr<Tileset>& tileset, int width, int height);
	virtual ~TileLayer();
	
	virtual void update(float dt);
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
	bool isInBounds(int x, int y) const;
	bool isTileInBounds(int tile_x, int tile_y) const;
	void setTile(int x, int y, int tile_x, int tile_y);
	void setTileID(int x, int y, int id);
	void emptyTile(int x, int y);
	
	const glm::mat4& getTransform() const;
	const glm::mat4& getTexcoordTransform() const;
	
	int getWidth() const;
	int getHeight() const;
	
private:
	int width;
	int height;
	
	std::shared_ptr<Tileset> tileset;
	
	mutable JE::GL::Model model;
	
	mutable bool need_update_transform;
	mutable bool need_update_texcoord_transform;
	mutable glm::mat4 transform_cache;
	mutable glm::mat4 texcoord_transform_cache;
	mutable float prev_x;
	mutable float prev_y;
	mutable GLfloat prev_image_w;
	mutable GLfloat prev_image_h;
};

};};
