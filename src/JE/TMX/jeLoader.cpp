#include "JE/TMX/jeLoader.h"
#include "JE/UTIL/jeString.h"
#include <iostream>
#include <algorithm>

namespace JE{namespace TMX{

Loader::Loader(const std::string& filename) : map() {
	this->map.ParseFile(filename);
	
	if (this->map.HasError()) {
		std::cout << "An error occured loading " << filename << ": " << std::endl;
		std::cerr << this->map.GetErrorText() << std::endl;
	}
}

JE::GRAPHICS::Tilemap Loader::createTilemap() const {
	return this->createTilemap(
		[] (Tmx::TileLayer* tile_layer) -> bool{
			return true;
		}
	);
}

JE::GRAPHICS::Tilemap Loader::createTilemap(std::function<bool(Tmx::TileLayer*)> func) const {
	JE::GRAPHICS::Tilemap tilemap(this->map.GetWidth(), this->map.GetHeight(), this->map.GetTileWidth(), this->map.GetTileHeight());
	
	for (Tmx::TileLayer* tilelayer : this->map.GetTileLayers()) {
		if (tilelayer == nullptr) continue;
		
		if (func(tilelayer)){
			JE::GRAPHICS::TileLayer& map_layer = tilemap.createLayer(
				tilelayer->GetName(), 
				tilelayer->GetZOrder(),
				tilelayer->GetX(),
				tilelayer->GetY()
			);
			
			std::cout << tilelayer->GetX() << ", " << tilelayer->GetY() << std::endl;
			
			//iterate each x,y pair
			for (int ix = 0; ix < tilelayer->GetWidth(); ix ++){
			for (int iy = 0; iy < tilelayer->GetHeight(); iy ++){
				const Tmx::MapTile& tile = tilelayer->GetTile(ix, iy);
				
				//skip tile if it's empty
				if (tile.gid <= 0 || tile.id < 0) continue;
				
				//Make sure tileset exists
				if (tile.tilesetId < 0 || tile.tilesetId >= this->map.GetNumTilesets()) continue;
				const Tmx::Tileset* tileset = this->map.GetTileset(tile.tilesetId);
				if (tileset == nullptr) continue;
				
				//Load tileset if it does not exist
				if (!map_layer.hasTileset(tileset->GetName())) {
					const Tmx::Image* image = tileset->GetImage();
					if (image == nullptr) {
						//if no image, then it is an image collection
						//std::string new_name = tileset->GetName() + "-!TILE@{" + JE::STRING::toString(tile.id, false) + "}";
						//if (!map_layer.hasTileset(new_name)) {
						//
						//}
						
						//map_layer.setTileID(ix, iy, new_name, 0);
						continue;
						
					} else {
						//create and add tileset
						map_layer.addTileset(
							tileset->GetName(), 
							std::make_shared<JE::GRAPHICS::Tileset>(
								image->GetSource(), 
								tileset->GetTileWidth(), tileset->GetTileHeight(),
								tileset->GetMargin(),    tileset->GetMargin(),
								tileset->GetSpacing(),   tileset->GetSpacing()
							)
						);
					}
				}
				
				//Actually set tile
				map_layer.setTileID(ix, iy, tileset->GetName(), tile.id);
			}
			}
		}
	}
	
	return tilemap;
}

void Loader::foreachTile(
	std::function<bool(Tmx::TileLayer*)> layer_filter, 
	std::function<void(Tmx::TileLayer*,const Tmx::MapTile*,int,int)> tile_func,
	bool skip_empty
) const {
	for (Tmx::TileLayer* layer : this->map.GetTileLayers()){
		if (layer == nullptr) continue;
		if (!layer_filter(layer)) continue;
		
		this->foreachTileInLayer(tile_func, layer, skip_empty);
	}
}

void Loader::foreachTileInLayer(
	std::function<void(Tmx::TileLayer*,const Tmx::MapTile*,int,int)> tile_func,
	Tmx::TileLayer* layer, bool skip_empty
) const {
	if (layer == nullptr) return;
	
	for (int ix = 0; ix < layer->GetWidth(); ++ix){
	for (int iy = 0; iy < layer->GetHeight(); ++iy){
		const Tmx::MapTile& tile = layer->GetTile(ix, iy);
		if (skip_empty && tile.gid <= 0) continue;
		
		tile_func(layer, &tile, ix, iy);
	}
	}
}

void Loader::foreachObject(std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func) const {
	this->foreachObject(
		[](Tmx::ObjectGroup*_)->bool{return true;},
		{},
		func
	);
}

void Loader::foreachObject(
	std::function<bool(Tmx::ObjectGroup*)> group_filter, 
	const std::vector<std::string>& object_types,
	std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func
) const {
	for (Tmx::ObjectGroup* group : this->map.GetObjectGroups()) {
		if (group == nullptr) continue;
		if (!group_filter(group)) continue;
		
		for (Tmx::Object* object : group->GetObjects()) {
			if (object_types.size() > 0){
				if (std::find(object_types.begin(), object_types.end(), object->GetType()) == object_types.end()){
					continue;
				}
			}
			
			func(group, object);
		}
	}
}

void Loader::foreachObjectInGroup(
	std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func,
	Tmx::ObjectGroup* group
) const {
	if (group == nullptr) return;
	
	for (Tmx::Object* object : group->GetObjects()) {
		func(group, object);
	}
}

Tmx::Map& Loader::getMap() {
	return this->map;
}

int Loader::getWidth() const{
	return this->map.GetWidth();
}

int Loader::getHeight() const{
	return this->map.GetHeight();
}

int Loader::getTileWidth() const{
	return this->map.GetTileWidth();
}

int Loader::getTileHeight() const{
	return this->map.GetTileHeight();
}

const std::vector<Tmx::TileLayer*>& Loader::getTileLayers() const{
	return this->map.GetTileLayers();
}

const std::vector<Tmx::ObjectGroup*>& Loader::getObjectGroups() const{
	return this->map.GetObjectGroups();
}

const Tmx::Tileset* Loader::getTileset(int index) const{
	if (index < 0 || index >= this->map.GetNumTilesets()) return nullptr;
	return this->map.GetTileset(index);
}

const Tmx::Tile* Loader::getTileData(int tileset, int index) const{
	const Tmx::Tileset* set = this->getTileset(tileset);
	if (set == nullptr) return nullptr;
	if (index < 0 || index >= (int)set->GetTiles().size());
	return set->GetTile(index);
}

}}