#pragma once

namespace JE{
class Data
{
	public:
		void* owner;
		bool independent;
		bool kill(void* killer);
		Data(void* owner = nullptr);
		virtual ~Data();
		void setOwner(void* owner = nullptr);
	protected:
	private:
};
};
