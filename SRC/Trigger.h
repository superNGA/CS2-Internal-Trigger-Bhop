#pragma once
#include<Windows.h>
#include"Offsets.h"
#include"Client.h"

class Trigger
{
public:
	Trigger(INPUT& Attack, uintptr_t BaseModule);
	void execute();
private:
	INPUT attack;
	uintptr_t baseModule;
};

