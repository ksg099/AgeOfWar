#include "pch.h"

int main()
{
    FRAMEWORK.Init(1920, 1080, "Zombie");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}