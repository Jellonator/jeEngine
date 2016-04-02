#include "JE/GRAPHIC/jeTilemap.h"
#include "JE/GL/jeShader.h"
#include <iostream>

//this cool macro brought to you in part by https://open.gl/geometry
#define GLSL(src) "#version 330 core\n" #src

namespace JE{namespace GRAPHICS{

//Tileset
Tileset::Tileset(const std::string& file, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = std::make_shared<JE::GL::Texture>(file);
}
		
Tileset::Tileset(SDL_Surface* surface, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = std::make_shared<JE::GL::Texture>(surface);
}
		
Tileset::Tileset(std::shared_ptr<JE::GL::Texture>& texture, int tile_width, int tile_height,
	int offset_x, int offset_y, int space_x, int space_y)
	: Tileset(tile_width, tile_height, offset_x, offset_y, space_x, space_y){
	this->texture = texture;
}

Tileset::Tileset(int tile_width, int tile_height, int offset_x, int offset_y, int space_x, int space_y) : 
	tile_width(tile_width),
	tile_height(tile_height),
	offset_x(offset_x),
	offset_y(offset_y),
	space_x(space_x),
	space_y(space_y){
}

SDL_Rect Tileset::getRect(int x, int y) const{
	SDL_Rect ret = {
		x * (this->tile_width + this->space_x) + this->offset_x, 
		y * (this->tile_height+ this->space_y) + this->offset_y, 
		this->tile_width, 
		this->tile_height
	};
	
	return ret;
}

SDL_Rect Tileset::getRectId(int id, int width) const{
	int ix = id % width;
	int iy = id / width;
	return this->getRect(ix, iy);
}

int Tileset::getWidth() const{
	return this->texture->getWidth();
}

int Tileset::getHeight() const{
	return this->texture->getHeight();
}

int Tileset::getTileWidth() const{
	return this->tile_width;
}

int Tileset::getTileheight() const{
	return this->tile_height;
}

std::shared_ptr<JE::GL::Texture>& Tileset::getTexture(){
	return this->texture;
}

//Tile
TilemapTile::TilemapTile(int x, int y, bool empty): x(x), y(y), empty(empty){}

// Shaders
JE::GL::Shader* tilemap_shader = nullptr;

std::string tilemap_vertex_shader = GLSL(
in vec3 in_Position;
in vec2 in_Texcoord;
uniform mat4 in_Transform;
uniform mat4 in_TexcoordTransform;
out vec2 vx_Texcoord;
void main(void) {
	gl_Position = in_Transform * vec4(in_Position, 1.0);
	vx_Texcoord = (in_TexcoordTransform * vec4(in_Texcoord.xy, 1.0, 1.0)).xy;
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
layout(points, max_vertices=3) out;
in vec2 vx_Texcoord[];
out vec2 ex_Texcoord;
void main(){
	for(int i = 0; i < gl_in.length(); i++){
		 // copy attributes
		gl_Position = gl_in[i].gl_Position;
		ex_Texcoord = vx_Texcoord[i];
		// done with the vertex
		EmitVertex();
	}
	EndPrimitive();
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
		if (!tilemap_shader->setUniformMat("in_Transform", glm::mat4x4())){
			std::cout << "Failed to set tilemap transform!" << std::endl;
		}
		if (!tilemap_shader->setUniformMat("in_TexcoordTransform", glm::mat4x4())){
			std::cout << "Failed to set tilemap texcoord transform!" << std::endl;
		}
	}
	
	return *tilemap_shader;
}

//Tilemap Layer
TilemapLayer::TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height) : 
	TilemapLayer(tileset, width, height, tileset->getTileWidth(), tileset->getTileheight()){}

TilemapLayer::TilemapLayer(std::shared_ptr<Tileset>& tileset, int width, int height, int tile_width, int tile_height) : 
		tile_width(tile_width),
		tile_height(tile_height),
		width(width),
		height(height),
		tileset(tileset),
		tiles(width, std::vector<TilemapTile>(height, TilemapTile(0, 0, true))),
		model() {
	
	this->model.getPointAttribute().setShaderReference("in_Position");
	this->model.addAttribute("texcoord", "in_Texcoord");
	this->model.getAttribute("texcoord").setSize(2);
	this->model.useShader(getTilemapShader());
	this->model.setDrawMode(GL_POINTS);
	
	this->need_update_model = true;
}

TilemapLayer::~TilemapLayer() {
	
}

void TilemapLayer::update(float dt) {
	
}

void TilemapLayer::drawMatrix(const glm::mat4& camera, float x, float y) const {
	if (this->need_update_model){
		this->updateModel();
	}
	
	JE::GL::Shader& shader = getTilemapShader();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	
	// Send transformations
	shader.setUniformMat("in_Transform", transform);
	
	// Actual draw call
	this->tileset->getTexture()->use();
	this->model.draw();
	this->tileset->getTexture()->disable();
}

void TilemapLayer::updateModel() const {
	
}

bool TilemapLayer::isInBounds(int x, int y) const {
	return (
		x >= 0 && 
		y >= 0 && 
		x < this->width && 
		y < this->height
	);
}

bool TilemapLayer::isTileInBounds(int tile_x, int tile_y) const {
	return (
		tile_x >= 0 && 
		tile_y >= 0 && 
		tile_x < this->tileset->getWidth() && 
		tile_y < this->tileset->getHeight()
	);
}

void TilemapLayer::setTile(int x, int y, int tile_x, int tile_y) {
	if (!this->isInBounds(x, y)) return;
	if (!this->isTileInBounds(tile_x, tile_y)) return;
	
	TilemapTile& t = this->tiles[x][y];
	t.x = tile_x;
	t.y = tile_y;
	t.empty = false;
}

void TilemapLayer::emptyTile(int x, int y) {
	if (!this->isInBounds(x, y)) return;
	
	TilemapTile& t = this->tiles[x][y];
	t.empty = true;
}

};};
