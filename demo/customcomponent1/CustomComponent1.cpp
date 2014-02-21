#include "CustomComponent1.h"
#include <iostream>

CustomComponent1::CustomComponent1()
{

}

CustomComponent1::~CustomComponent1()
{

}

void CustomComponent1::Update(float dt)
{
	std::cout << "Updating CustomComponent1: " << dt << std::endl;
}
