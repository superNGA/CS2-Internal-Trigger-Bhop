#define WIN32_LEAN_AND_MEAN
#include<Windows.h>

#include<cstdint>
#include<thread>
#include"Bhop.h"
#include"Trigger.h"

namespace Offsets
{
    uintptr_t dwLocalPlayerPawn = 0x1831AE8;
    uintptr_t jump = 0x182AAF0;

    uintptr_t m_iHealth = 0x344;
    uintptr_t m_fFlags = 0x3EC;

    uint32_t Standing = 65665;
    uint32_t Crouching = 65667;
    int PlusJump = 65537;
    int MinusJump = 256;
}

void HAXMAIN(HINSTANCE Instance) noexcept
{
    //main cheat
    uintptr_t baseModule = (uintptr_t)GetModuleHandle("client.dll");

    //mouse wheel down
    INPUT mousedown;
    mousedown.type = INPUT_MOUSE;
    mousedown.mi.dwFlags = MOUSEEVENTF_WHEEL;
    mousedown.mi.mouseData = -WHEEL_DELTA;

    //mouse wheel up
    INPUT mouseup;
    mouseup.type = INPUT_MOUSE;
    mouseup.mi.dwFlags = MOUSEEVENTF_WHEEL;
    mouseup.mi.mouseData = WHEEL_DELTA;

    //left click
    INPUT Attack;
    Attack.type = INPUT_MOUSE;


    Bhop bhop(mousedown, mouseup, baseModule);
    Trigger triggerbot(Attack, baseModule);

    while (!GetAsyncKeyState(VK_END))
    {
        if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000)
        {
            triggerbot.execute();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            bhop.execute();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    //uninject
    FreeLibraryAndExitThread(Instance, 0);

    return;
}

BOOL WINAPI DllMain(
    HINSTANCE Instance,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    //on attach
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(Instance);

        //creating hack thread
        auto HackThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HAXMAIN), Instance, 0, nullptr);

        if (HackThread) CloseHandle(HackThread);
    }

    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}