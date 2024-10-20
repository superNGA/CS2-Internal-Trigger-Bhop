#pragma once
#include<Windows.h>
#include<thread>
#include"Offsets.h"
#include"Client.h"

class Bhop
{
public:
	Bhop(INPUT& mousedown, INPUT& mouseup, uintptr_t baseModule);
	void execute();
private:
	INPUT& mousedown;
	INPUT& mouseup;
	uintptr_t baseModule;
};

