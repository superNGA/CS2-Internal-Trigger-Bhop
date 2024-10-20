#include "Trigger.h"

Trigger::Trigger(INPUT& Attack, uintptr_t BaseModule)
	:attack(Attack), baseModule(BaseModule)
{

}

void Trigger::execute()
{
	uintptr_t LocalPlayer = *(reinterpret_cast<uintptr_t*>(baseModule + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn));

	BYTE team = *(reinterpret_cast<BYTE*>(LocalPlayer + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum));

	uintptr_t EntityList = *(reinterpret_cast<uintptr_t*>(baseModule + cs2_dumper::offsets::client_dll::dwEntityList));

	int CrosshairEntityIndex = *(reinterpret_cast<int*>(LocalPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex));

	if (CrosshairEntityIndex < 0) return;

	uintptr_t ListEntry = *(reinterpret_cast<uintptr_t*>(EntityList + 0x8 * (CrosshairEntityIndex >> 9) + 0x10));
	uintptr_t Entity = *(reinterpret_cast<uintptr_t*>(ListEntry + 120 * (CrosshairEntityIndex & 0x1ff)));

	if (!Entity) return;

	//return if same team
	if (team == *(reinterpret_cast<BYTE*>(Entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum))) return;

	//if dead the return
	if (*(reinterpret_cast<int*>(Entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth)) <= 0) return;

	//Simulating click
	attack.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &attack, sizeof(INPUT));
	attack.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &attack, sizeof(INPUT));

	return;
}