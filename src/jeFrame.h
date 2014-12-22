#pragma once
#include "jeEntity.h"
#include "jeCanvas.h"
#include "jeCamera.h"
#include <vector>
#include <map>
#include <string>
namespace JE{namespace GUI{
struct Style {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	bool visible;
	bool smooth;
	int space;
	int dragspace;
	int border;
	int minlength;
	Style(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void drawRect(float x, float y, float w, float h, GRAPHICS::Camera* camera = NULL);
};
class Frame : public JE::Entity
{
	public:
		Style style;
		JE::GRAPHICS::Canvas* canvas;
		Frame(int x = 0, int y = 0, int width = 0, int height = 0);
		virtual ~Frame();
		virtual void OnUpdate();
		virtual void OnDraw();
		virtual void draw();
		virtual void update();
		virtual void setSize(int width, int height);
		void redraw();
	protected:
		int width;
		int height;
	private:
		bool needs_redraw;
};
}}
