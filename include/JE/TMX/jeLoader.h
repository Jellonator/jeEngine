#include <Tmx.h>
#include <string>
#include <functional>
#include "../GRAPHIC/TILEMAP/jeTilemap.h"

namespace JE{namespace TMX{

class Loader {
public:
	Loader(const std::string& filename);
	JE::GRAPHICS::Tilemap createTilemap() const;
	JE::GRAPHICS::Tilemap createTilemap(std::function<bool(Tmx::TileLayer*)> func) const;
	
	Tmx::Map& getMap();

private:
	Tmx::Map map;
};

}}