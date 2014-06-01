#pragma once
#include <cstddef>
#include <string>
#include <iostream>
namespace JE{
class Data
{
	public:
		void* owner;
		bool independent;
		bool getKill(void* killer = NULL);
		Data(void* owner);
		virtual ~Data();
	protected:
	private:
};
};
