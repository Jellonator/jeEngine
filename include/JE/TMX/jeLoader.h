#include <Tmx.h>
#include <string>
#include <functional>
#include "../GRAPHIC/TILEMAP/jeTilemap.h"

namespace JE{namespace TMX{

class Loader {
public:
	Loader(const std::string& filename);
	JE::GRAPHICS::Tilemap createTilemap() const;
	JE::GRAPHICS::Tilemap createTilemap(std::function<bool(Tmx::TileLayer*)> layer_filter) const;
	
	void foreachObject(
		std::function<bool(Tmx::ObjectGroup*)> group_filter, 
		const std::vector<std::string>& object_types,
		std::function<void(Tmx::ObjectGroup*,Tmx::Object*)> func
	) const;
	
	void foreachObject(std::function<void(Tmx::ObjectGroup*,Tmx::Object*)>func)const;
	
	Tmx::Map& getMap();

private:
	Tmx::Map map;
};

}}