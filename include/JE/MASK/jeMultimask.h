#pragma once
#include "jeMaskList.h"
#include <vector>
#include <memory>
#include <tuple>

namespace JE{ namespace MASK{

class Multimask : public MaskList{
public:
	Multimask(int x = 0, int y = 0);
	virtual ~Multimask();
	
	virtual MaskListIterator getMaskList(int left, int top, int right, int bottom);
	virtual MaskListIterator getMaskListAll();
	
	template <class MType, class... ArgTypes>
	MType& addMask(ArgTypes... arguments){
		std::shared_ptr<MType> ptr = std::make_shared<MType>(arguments...);
		this->mask_vec.push_back(ptr);
		
		return *ptr;
	}
	
	virtual int getLeft() const;
	virtual int getRight() const;
	virtual int getTop() const;
	virtual int getBottom() const;
	
	//void generator functions
	void generateFromPoints(const std::vector<std::pair<int,int>>& points);
	
private:
	std::vector<std::shared_ptr<Mask>> mask_vec;
	int stored_left;
	int stored_right;
	int stored_top;
	int stored_bottom;
};

}}