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

		std::vector<int> __GROUPS__;

		virtual void OnCreate();
		virtual void OnAdd();
		virtual void OnUpdate();
		virtual void OnDraw();
		virtual void OnRemove();

		static void setMask(jeEntity* entity, jeMask* mask);
		inline void setMask(jeMask* mask);
	protected:
	private:
};
