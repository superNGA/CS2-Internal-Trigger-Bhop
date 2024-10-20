#include "Bhop.h"

Bhop::Bhop(INPUT& MouseDown, INPUT& MouseUp, uintptr_t BaseModule)
    :mousedown(MouseDown), mouseup(MouseUp), baseModule(BaseModule)
{
}

void Bhop::execute()
{
        uintptr_t LocalPlayer = *(reinterpret_cast<uintptr_t*>(baseModule + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn));

        if (!LocalPlayer) return; //valid local player
        if (*(reinterpret_cast<int32_t*>(baseModule + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth)) <= 0) return; //if not dead

        int32_t Flag = *(reinterpret_cast<int32_t*>(LocalPlayer + cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags));


        if (Flag == 65665 || Flag == 65667)
        {
            SendInput(1, &mousedown, sizeof(INPUT));
        }
        else
        {
            SendInput(1, &mouseup, sizeof(INPUT));
        }
}