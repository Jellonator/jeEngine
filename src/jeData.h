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
		bool kill(void* killer);
		Data(void* owner = NULL);
		virtual ~Data();
		void setOwner(void* owner = NULL);
	protected:
	private:
};
};
