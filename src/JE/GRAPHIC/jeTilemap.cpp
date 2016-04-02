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

SDL_Rect Tileset::getRectId(int id) const{
	int width = this->getWidthInTiles();
	
	int ix = id % width;
	int iy = id / width;
	return this->getRect(ix, iy);
}

SDL_Point Tileset::getTileId(int id) const{
	int width = this->getWidthInTiles();
	
	SDL_Point ret = {
		id % width, // x
		id / width  // y
	};
	
	return ret;
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

int Tileset::getTileHeight() const{
	return this->tile_height;
}

int Tileset::getWidthInTiles() const {
	return this->getWidth() / (this->tile_width+this->space_x);
}

int Tileset::getHeightInTiles() const{
	return this->getHeight() / (this->tile_height+this->space_y);
}

int Tileset::getNumTiles() const{
	return this->getWidthInTiles() * this->getHeightInTiles();
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
		
		float w_scale = 1;
		float x_pos = 0;
		if (in_Width > 1){
			x_pos = 1 / in_Width;
			w_scale = (in_Width - 1) / in_Width;
		}
		
		float h_scale = 1;
		float y_pos = 0;
		if (in_Height > 1){
			y_pos = 1 / in_Height;
			h_scale = (in_Height - 1) / in_Height;
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

//Tilemap Layer
TileLayer::TileLayer(std::shared_ptr<Tileset>& tileset, int width, int height) : 
	TileLayer(tileset, width, height, tileset->getTileWidth(), tileset->getTileHeight()){}

TileLayer::TileLayer(std::shared_ptr<Tileset>& tileset, int width, int height, int tile_width, int tile_height) : 
		Graphic(),
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
	this->need_update_transform = true;
	this->need_update_texcoord_transform = true;
	
	this->prev_x = this->x;
	this->prev_y = this->y;
	this->prev_image_w = 1;
	this->prev_image_h = 1;
	
	this->transform_cache = glm::mat4();
	this->texcoord_transform_cache = glm::mat4();
}

TileLayer::~TileLayer() {
	
}

void TileLayer::update(float dt) {
	
}

void TileLayer::drawMatrix(const glm::mat4& camera, float x, float y) const {
	if (this->need_update_model){
		this->updateModel();
	}
	
	JE::GL::Shader& shader = getTilemapShader();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform *= this->getTransform();
	
//	const glm::mat4x4& texcoord_transform = this->getTexcoordTransform();
	
	// Send transformations
	shader.setUniformMat("in_Transform", transform);
	shader.setUniformMat("in_TexcoordTransform", this->getTexcoordTransform());
	shader.setUniform("in_Width", this->tileset->getTileWidth());
	shader.setUniform("in_Height", this->tileset->getTileHeight());
	
	// Actual draw call
	this->tileset->getTexture()->use();
	this->model.draw();
	this->tileset->getTexture()->disable();
}

void TileLayer::updateModel() const {
	JE::GL::ModelAttribute& texcoord_attr     = this->model.getAttribute("texcoord");
	JE::GL::ModelAttribute& point_attr        = this->model.getPointAttribute();
	
	JE::GL::BufferObject<GLuint>&  element_buf  = this->model.getElementBuffer();
	JE::GL::BufferObject<GLfloat>& texcoord_buf = texcoord_attr.getBuffer();
	JE::GL::BufferObject<GLfloat>& point_buf    = point_attr.getBuffer();
	
	std::vector<GLuint>  element_vec;
	std::vector<GLfloat> point_vec;
	std::vector<GLfloat> texcoord_vec;
	
	GLuint element_num = 0;
	
	int ix = 0;
	int iy = 0;
	for (const std::vector<TilemapTile>& vec : this->tiles) {
		for (const TilemapTile& tile : vec){
			if (!tile.empty){
				std::cout << "Adding point: " << ix << ", " << iy << std::endl;
				element_vec.push_back(element_num);
				++element_num;
				
				point_vec.push_back(ix);
				point_vec.push_back(iy);
				point_vec.push_back(0.0);
				
				texcoord_vec.push_back(tile.x);
				texcoord_vec.push_back(tile.y);
				
			}
			iy ++;
		}
		iy = 0;
		ix ++;
	}
	
	element_buf.setData(element_vec);
	point_buf.setData(point_vec);
	texcoord_buf.setData(texcoord_vec);
	
	element_buf.pushLocal();
	point_buf.pushLocal();
	texcoord_buf.pushLocal();
	
	this->need_update_model = false;
}

bool TileLayer::isInBounds(int x, int y) const {
	return (
		x >= 0 && 
		y >= 0 && 
		x < this->width && 
		y < this->height
	);
}

bool TileLayer::isTileInBounds(int tile_x, int tile_y) const {
	return (
		tile_x >= 0 && 
		tile_y >= 0 && 
		tile_x < this->tileset->getWidth() && 
		tile_y < this->tileset->getHeight()
	);
}

void TileLayer::setTile(int x, int y, int tile_x, int tile_y) {
	if (!this->isInBounds(x, y)) return;
	if (!this->isTileInBounds(tile_x, tile_y)) return;
	
	TilemapTile& t = this->tiles[x][y];
	t.x = tile_x;
	t.y = tile_y;
	t.empty = false;
	
	this->need_update_model = true;
}

void TileLayer::emptyTile(int x, int y) {
	if (!this->isInBounds(x, y)) return;
	
	TilemapTile& t = this->tiles[x][y];
	t.empty = true;
	
	this->need_update_model = true;
}

const glm::mat4& TileLayer::getTransform() const{
	float tex_w = 1;
	float tex_h = 1;
	float tile_w = 1;
	float tile_h = 1;
	if (this->tileset && this->tileset->getTexture()){
		tex_w = this->tileset->getWidth();
		tex_h = this->tileset->getHeight();
		tile_w = this->tileset->getTileWidth();
		tile_h = this->tileset->getTileHeight();
	}
	if (this->prev_x != this->x || this->prev_y != this->y
	 || this->prev_image_w != tex_w || this->prev_image_h != tex_h) {
		this->need_update_texcoord_transform = true;
		this->need_update_transform = true;
		this->prev_x = this->x;
		this->prev_y = this->y;
		this->prev_image_w = tex_w;
		this->prev_image_h = tex_h;
	}
	
	if (this->need_update_transform){
		this->transform_cache = glm::mat4();
		this->transform_cache = glm::scale(this->transform_cache, glm::vec3(tile_w, tile_h, 1.0f));
		this->transform_cache = glm::translate(this->transform_cache, glm::vec3(this->getX(), this->getY(), 0.0));
		this->need_update_transform = false;
	}
	
	return this->transform_cache;
}

const glm::mat4& TileLayer::getTexcoordTransform() const{
	float tex_w = 1;
	float tex_h = 1;
	float tile_w = 1;
	float tile_h = 1;
	if (this->tileset && this->tileset->getTexture()){
		tex_w = this->tileset->getWidth();
		tex_h = this->tileset->getHeight();
		tile_w = this->tileset->getTileWidth();
		tile_h = this->tileset->getTileHeight();
	}
	
	if (this->prev_image_w != tex_w || this->prev_image_h != tex_h) {
		this->need_update_texcoord_transform = true;
		this->need_update_transform = true;
	}
		
	if (this->need_update_texcoord_transform){
		this->texcoord_transform_cache = glm::mat4();
		float scale_x = (tile_w) / tex_w;
		float scale_y = (tile_h) / tex_h;
		this->texcoord_transform_cache = glm::scale(this->texcoord_transform_cache, glm::vec3(scale_x, scale_y, 1.0f));
//		this->texcoord_transform_cache = glm::translate(this->texcoord_transform_cache, glm::vec3(0.5f/tex_w, 0.5f/tex_h, 0.0f));
//		this->texcoord_transform_cache = glm::translate(this->texcoord_transform_cache, glm::vec3(0.5f/tile_w, 0.5f/tile_h, 1.0));
//		this->texcoord_transform_cache = glm::scale(this->texcoord_transform_cache, glm::vec3((tile_w-1)/tile_w, (tile_h-1)/tile_h, 1.0f));
//		this->texcoord_transform_cache = glm::scale(this->texcoord_transform_cache, glm::vec3((tile_w-1) / tex_w, (tile_h-1) / tex_h, 1.0f));
//		this->texcoord_transform_cache = glm::scale(this->texcoord_transform_cache, glm::vec3((tile_w-1)/tile_w, (tile_h-1)/tile_h, 1.0f));
		
		this->need_update_texcoord_transform = false;
		
		this->prev_image_w = tex_w;
		this->prev_image_h = tex_h;
	}
	
	return this->texcoord_transform_cache;
}

};};
