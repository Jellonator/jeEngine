#include "JE/GRAPHIC/TILEMAP/jeTileLayer.h"
#include "JE/GL/jeShader.h"
#include <iostream>

//this cool macro brought to you in part by https://open.gl/geometry
#define GLSL(src) "#version 330 core\n" #src

namespace JE{namespace GRAPHICS{

// Shaders
JE::GL::Shader* tilemap_shader = nullptr;
std::string tilemap_vertex_shader = GLSL(
	in vec3 in_Position;
	in vec2 in_Texcoord;
	uniform mat4 in_Transform;
	uniform mat4 in_TexcoordTransform;
	out vec2 vx_Texcoord;
	void main(void) {
		gl_Position = vec4(in_Position, 1.0);
		vx_Texcoord = in_Texcoord;
	}
);

std::string tilemap_fragment_shader = GLSL(
	precision highp float;
	in vec2 ex_Texcoord;
	uniform sampler2D texture;
	uniform vec4 in_Color;
	void main(void) {
		gl_FragColor = in_Color * texture2D(texture, ex_Texcoord);
	}
);

std::string tilemap_geometry_shader = GLSL(
	layout(points) in;
	layout(triangle_strip, max_vertices=6) out;
	in vec2 vx_Texcoord[];
	out vec2 ex_Texcoord;
	uniform mat4 in_Transform;
	uniform mat4 in_TexcoordTransform;
	uniform float in_Width;
	uniform float in_Height;
	void main(){
		for(int i = 0; i < gl_in.length(); i++){
			 // copy attributes
			vec4 pos = gl_in[i].gl_Position;
			vec4 texc = vec4(vx_Texcoord[i].xy, 1.0, 1.0);
			
			float padding = 0.5;
			
			float w_scale = 1;
			float x_pos = 0;
			if (in_Width > 1){
				x_pos = padding / in_Width;
				w_scale = (in_Width - padding) / in_Width;
			}
			
			float h_scale = 1;
			float y_pos = 0;
			if (in_Height > 1){
				y_pos = padding / in_Height;
				h_scale = (in_Height - padding) / in_Height;
			}
			
			gl_Position = in_Transform * (pos + vec4(0.0, 0.0, 0, 0));
			ex_Texcoord = (in_TexcoordTransform * (texc + vec4(  x_pos, y_pos, 0.0, 0.0))).xy;
			EmitVertex();
			
			gl_Position = in_Transform * (pos + vec4(1.0, 0.0, 0, 0));
			ex_Texcoord = (in_TexcoordTransform * (texc + vec4(w_scale, y_pos, 0.0, 0.0))).xy;
			EmitVertex();
			
			gl_Position = in_Transform * (pos + vec4(0.0, 1.0, 0, 0));
			ex_Texcoord = (in_TexcoordTransform * (texc + vec4(  x_pos, h_scale, 0.0, 0.0))).xy;
			EmitVertex();
			
			gl_Position = in_Transform * (pos + vec4(1.0, 1.0, 0, 0));
			ex_Texcoord = (in_TexcoordTransform * (texc + vec4(w_scale, h_scale, 0.0, 0.0))).xy;
			EmitVertex();
			
			EndPrimitive();
		}
	}
);

JE::GL::Shader& getTilemapShader(){
	if (tilemap_shader == nullptr){
		tilemap_shader = new JE::GL::Shader(
			{
				{tilemap_vertex_shader, GL_VERTEX_SHADER},
				{tilemap_fragment_shader, GL_FRAGMENT_SHADER},
				{tilemap_geometry_shader, GL_GEOMETRY_SHADER},
			}, 
			false
		);
		if (!tilemap_shader->linkShaders()){
			std::cout << "Failed to link tilemap shader!" << std::endl;
		}
		if (!tilemap_shader->setUniform("in_Color", 1.0f, 1.0f, 1.0f, 1.0f)){
			std::cout << "Failed to set tilemap color!" << std::endl;
		}
		if (!tilemap_shader->setUniform("in_Width", 1.0f)){
			std::cout << "Failed to set tilemap width!" << std::endl;
		}
		if (!tilemap_shader->setUniform("in_Height", 1.0f)){
			std::cout << "Failed to set tilemap height!" << std::endl;
		}
		if (!tilemap_shader->setUniformMat("in_Transform", glm::mat4x4())){
			std::cout << "Failed to set tilemap transform!" << std::endl;
		}
		if (!tilemap_shader->setUniformMat("in_TexcoordTransform", glm::mat4x4())){
			std::cout << "Failed to set tilemap texcoord transform!" << std::endl;
		}
	}
	
	return *tilemap_shader;
}

//constructor
TileLayer::TileLayer(int width, int height) :
TileLayer(0, 0, width, height){}

TileLayer::TileLayer(int x, int y, int width, int height) : 
	Graphic(x, y),
	width(width),
	height(height),
	metadata(width, std::vector<TileMetaData>(height, {"", 0, false})){
}

//destructor
TileLayer::~TileLayer() {
	
}

//callbacks
void TileLayer::update(float dt) {
	
}

void TileLayer::_updateTileset(const TileLayerSet& set) const{
	if (!set.need_remodel) return;
	set.need_remodel = false;
	JE::GL::BufferObject<GLfloat>& point_buf = set.model->getPointAttribute().getBuffer();
	JE::GL::BufferObject<GLfloat>& tex_buf = set.model->getAttribute("texcoord").getBuffer();
	JE::GL::BufferObject<GLuint>& element_buf = set.model->getElementBuffer();
	
	std::vector<GLfloat> points;
	std::vector<GLfloat> tex;
	std::vector<GLuint> elements;
	
	GLuint num = 0;
	
	for (const TilePoint& point : set.tiles){
		points.push_back(point.x);
		points.push_back(point.y);
		points.push_back(0.0f);
		
		tex.push_back(point.tile_x);
		tex.push_back(point.tile_y);
		
		elements.push_back(num);
		
		num ++;
	}
	
	point_buf.setData(points);
	tex_buf.setData(tex);
	element_buf.setData(elements);
	
	point_buf.pushLocal();
	tex_buf.pushLocal();
	element_buf.pushLocal();
}

void TileLayer::drawMatrix(const glm::mat4& camera, float x, float y) const {
	JE::GL::Shader& shader = getTilemapShader();
	
	for (auto& pair : this->tileset_map){
		const TileLayerSet& set = pair.second;
		
		this->_updateTileset(set);
		if (set.tileset->getTexture() == nullptr) continue;
		
		//transformations
		glm::mat4x4 transform = camera;
		transform *= this->getTransform(*set.tileset);
		transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
		
		//send transformations
		shader.setUniformMat("in_Transform", transform);
		shader.setUniformMat("in_TexcoordTransform", this->getTexcoordTransform(*set.tileset));
		shader.setUniform("in_Width", set.tileset->getTileWidth());
		shader.setUniform("in_Height", set.tileset->getTileHeight());
		
		//draw call
		set.tileset->getTexture()->use();
		set.model->useShader(shader);
		set.model->draw();
	}
}

//bounds
bool TileLayer::isInBounds(int x, int y) const {
	return (
		x >= 0 && 
		y >= 0 && 
		x < this->width && 
		y < this->height
	);
}

bool TileLayer::isTileInBounds(const std::string& tileset, int tile_x, int tile_y) const {
	if (!this->hasTileset(tileset)) return false;
	return (
		tile_x >= 0 && 
		tile_y >= 0 && 
		tile_x < this->tileset_map.at(tileset).tileset->getWidthInTiles() && 
		tile_y < this->tileset_map.at(tileset).tileset->getHeightInTiles()
	);
}

//tile management
void TileLayer::setTile(int x, int y, const std::string& tileset, int tile_x, int tile_y) {
	if (!this->isInBounds(x, y)) return;
	if (!this->isTileInBounds(tileset, tile_x, tile_y)) return;
	
	this->emptyTile(x, y);
	
	if (this->tileset_map.count(tileset) == 0) return;
	TileLayerSet& set = this->tileset_map[tileset];
	
	set.need_remodel = true;
	set.tiles.push_back({x, y, tile_x, tile_y});
	
	//configure metadata
	TileMetaData& meta = this->metadata[x][y];
	meta.index = set.tiles.size() - 1;
	meta.is_owned = true;
	meta.tile_layer_set = tileset;
	
}

void TileLayer::setTileID(int x, int y, const std::string& tileset, int id){
	if (!this->isInBounds(x, y)) return;
	
	SDL_Point tile_pos = this->tileset_map[tileset].tileset->getTileId(id);
	if (!this->isTileInBounds(tileset, tile_pos.x, tile_pos.y)) return;
	this->setTile(x, y, tileset, tile_pos.x, tile_pos.y);
}

void TileLayer::_clearTile(TileMetaData& data){
	if (data.is_owned){
		//no longer owned by tileset
		data.is_owned = false;
		
		//Early return if owned by non-existent tileset
		if (this->tileset_map.count(data.tile_layer_set) == 0) return;
		
		TileLayerSet& set = this->tileset_map[data.tile_layer_set];
		if (set.tiles.size() == 0) return;
		
		//Backmost tile is taking the place of the old tile. It's faster this way.
		TilePoint& back = set.tiles.back();
		this->metadata[back.x][back.y].index = data.index;
		JE::eraseNoOrder(set.tiles, data.index);
		
		set.need_remodel = true;
	}
}

void TileLayer::emptyTile(int x, int y) {
	if (!this->isInBounds(x, y)) return;
	
	if (this->metadata[x][y].is_owned){
		this->_clearTile(this->metadata[x][y]);
	}
}

//transforms
glm::mat4 TileLayer::getTransform(const Tileset& set) const{
	float tile_w = set.getTileWidth();
	float tile_h = set.getTileHeight();
	
	glm::mat4 transform = glm::mat4();
	transform = glm::scale(transform, glm::vec3(tile_w, tile_h, 1.0f));
	transform = glm::translate(transform, glm::vec3(this->getX(), this->getY(), 0.0));
	
	return transform;
}

glm::mat4 TileLayer::getTexcoordTransform(const Tileset& set) const{
	float tex_w = set.getWidth();
	float tex_h = set.getHeight();
	float tile_w = set.getTileWidth();
	float tile_h = set.getTileHeight();
	
	glm::mat4 transform = glm::mat4();
	float scale_x = (tile_w) / tex_w;
	float scale_y = (tile_h) / tex_h;
	transform = glm::scale(transform, glm::vec3(scale_x, scale_y, 1.0f));
	
	return transform;
}

//tileset management
bool TileLayer::hasTileset(const std::string& name) const{
	return (this->tileset_map.count(name) > 0);
}

void TileLayer::addTileset(const std::string& name, std::shared_ptr<Tileset> tileset){
	if (tileset == nullptr) return;//cannot use null tileset
	if (this->hasTileset(name)){
		this->tileset_map[name].tileset = tileset;
		return;
	}
	this->tileset_map[name] = {
		tileset, {}, std::unique_ptr<JE::GL::Model>(new JE::GL::Model()), true
	};
	
	TileLayerSet& set = this->tileset_map[name];
	set.model->getPointAttribute().setShaderReference("in_Position");
	set.model->addAttribute("texcoord", "in_Texcoord");
	set.model->getAttribute("texcoord").setSize(2);
	set.model->useShader(getTilemapShader());
	set.model->setDrawMode(GL_POINTS);
}

std::shared_ptr<Tileset> TileLayer::getTileset(const std::string& name){
	if (this->hasTileset(name)){
		return this->tileset_map[name].tileset;
	}
	return nullptr;
}

//properties
int TileLayer::getWidth() const {
	return this->width;
}

int TileLayer::getHeight() const {
	return this->height;
}

};};
