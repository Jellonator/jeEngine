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
	Tmx::TileLayer* tilelayer;
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
				if (tile.gid < 0 || tile.id < 0) continue;
				
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

Tmx::Map& Loader::getMap() {
	return this->map;
}

}}