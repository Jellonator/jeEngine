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
		
		if (texc.x < 0 || texc.y < 0) continue;
		
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
TileLayer(tileset, 0, 0, width, height){}

TileLayer::TileLayer(std::shared_ptr<Tileset>& tileset, int x, int y, int width, int height) : 
		Graphic(x, y),
		width(width),
		height(height),
		tileset(tileset),
		model() {
	
	this->model.getPointAttribute().setShaderReference("in_Position");
	this->model.addAttribute("texcoord", "in_Texcoord");
	this->model.getAttribute("texcoord").setSize(2);
	this->model.useShader(getTilemapShader());
	this->model.setDrawMode(GL_POINTS);
	
	this->need_update_transform = true;
	this->need_update_texcoord_transform = true;
	
	this->prev_x = this->x;
	this->prev_y = this->y;
	this->prev_image_w = 1;
	this->prev_image_h = 1;
	
	this->transform_cache = glm::mat4();
	this->texcoord_transform_cache = glm::mat4();
	
	JE::GL::BufferObject<GLuint>&  element_buf  = this->model.getElementBuffer();
	JE::GL::BufferObject<GLfloat>& texcoord_buf = this->model.getAttribute("texcoord").getBuffer();
	JE::GL::BufferObject<GLfloat>& point_buf    = this->model.getPointAttribute().getBuffer();
	
	std::vector<GLuint>  element_vec;
	std::vector<GLfloat> point_vec;
	std::vector<GLfloat> texcoord_vec;
	
	GLuint element_num = 0;
	
	for (int iy = 0; iy < height; ++iy){
		for (int ix = 0; ix < width; ++ix) {
			element_vec.push_back(element_num);
			++element_num;
			
			point_vec.push_back(ix);
			point_vec.push_back(iy);
			point_vec.push_back(0.0);
			
			texcoord_vec.push_back(-1);
			texcoord_vec.push_back(-1);
		}
	}
	
	element_buf.setData(element_vec);
	point_buf.setData(point_vec);
	texcoord_buf.setData(texcoord_vec);
	
	element_buf.pushLocal();
	point_buf.pushLocal();
	texcoord_buf.pushLocal();
}

TileLayer::~TileLayer() {
	
}

void TileLayer::update(float dt) {
	
}

void TileLayer::drawMatrix(const glm::mat4& camera, float x, float y) const {
	if (this->tileset->getTexture() == nullptr) return;
	JE::GL::Shader& shader = getTilemapShader();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera;
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform *= this->getTransform();
	
	// Send transformations
	shader.setUniformMat("in_Transform", transform);
	shader.setUniformMat("in_TexcoordTransform", this->getTexcoordTransform());
	shader.setUniform("in_Width", this->tileset->getTileWidth());
	shader.setUniform("in_Height", this->tileset->getTileHeight());
	
	// Actual draw call
	this->tileset->getTexture()->use();
	this->model.draw();
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
		tile_x < this->tileset->getWidthInTiles() && 
		tile_y < this->tileset->getHeightInTiles()
	);
}

void TileLayer::setTile(int x, int y, int tile_x, int tile_y) {
	if (!this->isInBounds(x, y)) return;
	if (!this->isTileInBounds(tile_x, tile_y)) return;
	
	JE::GL::BufferObject<GLfloat>& texcoord_buf = this->model.getAttribute("texcoord").getBuffer();
	
	GLfloat data[] = {(GLfloat)tile_x, (GLfloat)tile_y};
	int pos = 2*(x + y*this->width);
	texcoord_buf.setElements(pos, 2, data);
}

void TileLayer::setTileID(int x, int y, int id){
	SDL_Point tile_pos = this->tileset->getTileId(id);
	this->setTile(x, y, tile_pos.x, tile_pos.y);
}

void TileLayer::emptyTile(int x, int y) {
	if (!this->isInBounds(x, y)) return;
	
	JE::GL::BufferObject<GLfloat>& texcoord_buf = this->model.getAttribute("texcoord").getBuffer();
	
	GLfloat data[] = {-1.0f, -1.0f};
	int pos = 2*(x + y*this->width);
	texcoord_buf.setElements(pos, 2, data);
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
		
		this->need_update_texcoord_transform = false;
		
		this->prev_image_w = tex_w;
		this->prev_image_h = tex_h;
	}
	
	return this->texcoord_transform_cache;
}

int TileLayer::getWidth() const {
	return this->width;
}

int TileLayer::getHeight() const {
	return this->height;
}

};};
