#pragma once
#include "jeFrame.h"
namespace JE{namespace GUI{
class Divider : public Frame
{
	public:
		Divider(int x, int y, int width, int height, bool vertical = false, bool isStatic = false);
		virtual ~Divider();
		void addFrame(Frame* frame, std::string name, int position = -1);
		virtual void OnUpdate();
		virtual void OnDraw();
		virtual void draw();
		virtual void update();
		float getPositionLeft(std::string name);
		float getPositionRight(std::string name);
		inline float getPositionTop(std::string name){return getPositionLeft(name);}
		inline float getPositionBottom(std::string name){return getPositionRight(name);}
		float getPositionLeftF(std::string name);
		float getPositionRightF(std::string name);
		inline float getPositionTopF(std::string name){return getPositionLeftF(name);}
		inline float getPositionBottomF(std::string name){return getPositionRightF(name);}

		bool setPositionLeft(std::string name, float value);
		bool setPositionRight(std::string name, float value);
		inline bool setPositionTop(std::string name, float value){return setPositionLeft(name, value);}
		inline bool setPositionBottom(std::string name, float value){return setPositionRight(name, value);}
		bool setPositionLeftF(std::string name, float value);
		bool setPositionRightF(std::string name, float value);
		inline bool setPositionTopF(std::string name, float value){return setPositionLeftF(name, value);}
		inline bool setPositionBottomF(std::string name, float value){return setPositionRightF(name, value);}

		void setVertical(bool vertical);
		void setStatic(bool isStatic);
		Frame* getFrame(std::string name);
		float getPositionF(int position);
		float getPosition(int position);
		bool setPosition(int position, float value);
		bool setPositionF(int position, float value);

		void setSize(int width, int height);
	protected:
	private:
		void updateFrames();
		float getPositionStart(int position);
		float getPositionEnd(int position);
		float getLogicalSize();
		int getID(std::string name);
		bool isStatic;
		bool vertical;
		int dragging;
		bool mouse_down;
		std::vector<Frame*> frames;
		std::map<std::string, Frame*> frames_named;
		std::vector<float> positions;
};
}}
