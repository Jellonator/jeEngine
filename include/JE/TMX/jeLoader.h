#include <Tmx.h>
#include <string>
#include <functional>
#include <vector>
#include "../GRAPHIC/TILEMAP/jeTilemap.h"

namespace JE{namespace TMX{

class Loader {
public:
	Loader(const std::string& filename);
	
	//tilemap
	JE::GRAPHICS::Tilemap createTilemap() const;
	JE::GRAPHICS::Tilemap createTilemap(std::function<bool(Tmx::TileLayer*)> layer_filter) const;
	
	//foreach tile
	void foreachTile(
		std::function<bool(Tmx::TileLayer*)> layer_filter, 
		std::function<void(Tmx::TileLayer*,const Tmx::MapTile*,int,int)> tile_func,
		bool skip_empty
	) const;
	
	void foreachTileInLayer(
		std::function<void(Tmx::TileLayer*,const Tmx::MapTile*,int,int)> tile_func,
		Tmx::TileLayer* layer, bool skip_empty
	) const;
	
	//foreach object
	void foreachObject(
		std::function<bool(Tmx::ObjectGroup*)> group_filter, 
		const std::vector<std::string>& object_types,
		std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func
	) const;
	
	void foreachObjectInGroup(
		std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func,
		Tmx::ObjectGroup* group
	) const;
	
	void foreachObject(std::function<void(Tmx::ObjectGroup*,Tmx::Object*)>func)const;
	
	//get vectors
	const std::vector<Tmx::TileLayer*>& getTileLayers() const;
	const std::vector<Tmx::ObjectGroup*>& getObjectGroups() const;
	
	//get map
	Tmx::Map& getMap();
	
	//get other
	const Tmx::Tileset* getTileset(int index) const;
	const Tmx::Tile* getTileData(int tileset, int index) const;
	
	//get properties
	int getWidth() const;
	int getHeight() const;
	int getTileWidth() const;
	int getTileHeight() const;

private:
	Tmx::Map map;
};

}}