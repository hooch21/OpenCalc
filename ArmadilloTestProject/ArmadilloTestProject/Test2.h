#pragma once
#include "TestBaseClass.h"
ref class Test2 : public TestBaseClass
{
public:
	Test2();

	virtual void CreateTestMatrix() override;
};

