#pragma once
#include "../jeCanvas.h"
#include "../../jeMain.h"
#include "../../jeUtil.h"
#include "../../GL/jeModel.h"
#include <memory>
#include <map>
#include <vector>

namespace JE{namespace GRAPHICS{

struct TilemapTile {
	int x;
	int y;
	TilemapTile(int x, int y);
};

};};
