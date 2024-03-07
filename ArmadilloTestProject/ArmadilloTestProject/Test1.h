#pragma once
#include "TestBaseClass.h"

ref class Test1 : public TestBaseClass
{
public:
	Test1();

	void ArmadilloTest();
	virtual void  CreateTestMatrix() override;
};

