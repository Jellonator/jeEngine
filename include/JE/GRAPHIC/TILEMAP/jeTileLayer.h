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
	TileLayer(int width, int height);
	TileLayer(int x, int y, int width, int height);
	virtual ~TileLayer();
	
	//callbacks
	virtual void update(float dt);
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
	
	//bounds
	bool isInBounds(int x, int y) const;
	bool isTileInBounds(const std::string& tileset, int tile_x, int tile_y) const;
	
	//tile management
	void setTile(int x, int y, const std::string& tileset, int tile_x, int tile_y);
	void setTileID(int x, int y, const std::string& tileset, int id);
	void emptyTile(int x, int y);
	
	//tileset management
	bool hasTileset(const std::string& name) const;
	void addTileset(const std::string& name, std::shared_ptr<Tileset>& tileset);
	std::shared_ptr<Tileset> getTileset(const std::string& name);
	
	glm::mat4 getTransform(const Tileset& tileset) const;
	glm::mat4 getTexcoordTransform(const Tileset& tileset) const;
	
	int getWidth() const;
	int getHeight() const;
	
private:
	struct TilePoint {
		int x;
		int y;
		int tile_x;
		int tile_y;
	};
	struct TileLayerSet{
		std::shared_ptr<Tileset> tileset;
		std::vector<TilePoint> tiles;
		//has to be unique_ptr, Model doesn't like move semantics as of yet. 
		mutable std::unique_ptr<JE::GL::Model> model;
		mutable bool need_remodel;
	};
	struct TileMetaData {
		std::string tile_layer_set;
		int index;
		bool is_owned;
	};
	
	int width;
	int height;
	
	std::map<std::string, TileLayerSet> tileset_map;
	std::vector<std::vector<TileMetaData>> metadata;
	
	void _clearTile(TileMetaData& data);
	void _updateTileset(const TileLayerSet& name) const;
};

};};
