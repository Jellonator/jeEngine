#pragma once
#include "JE.h"

class jeEntity
{
	public:
		jeEntity();
		virtual ~jeEntity();
		float x, y;
		jeMask* mask;

		int __INDEX__;

		std::vector<unsigned int> __GROUPS__;

		virtual void create();
		virtual void add();
		virtual void update();
		virtual void draw();
		virtual void remove();

		void setMask(jeMask* mask);
	protected:
	private:
};
