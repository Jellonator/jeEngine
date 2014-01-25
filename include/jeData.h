#pragma once
#include <cstddef>
#include <string>
#include <iostream>
class jeData
{
	public:
		void* owner;
		bool independent;
		bool getKill(void* killer = NULL);
		jeData(void* owner);
		virtual ~jeData();
	protected:
	private:
};
