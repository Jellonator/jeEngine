#pragma once
#include "../jeCanvas.h"
#include "../../jeMain.h"
#include "../../jeUtil.h"
#include "../../GL/jeModel.h"
#include "jeTileset.h"
#include "jeTileLayer.h"
#include <memory>
#include <map>
#include <string>

namespace JE{namespace GRAPHICS{

class Tilemap : public JE::GRAPHICS::Graphic{
public:
	Tilemap(float x, float y, int width, int height);
	Tilemap(int width, int height);
	
	TileLayer& createLayer(const std::string& name, std::shared_ptr<Tileset>& tileset);
	TileLayer* getLayer(const std::string& name);
	
	virtual void update(float dt);
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
private:
	std::map<std::string, std::unique_ptr<TileLayer> > layers;
	int width;
	int height;
};

};};
