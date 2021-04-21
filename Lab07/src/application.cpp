#include "AppWindow.h"

int main()
{
    auto* win = new AppWindow();
    win->Init("ICT397 Lab7 - Bryce Standley", 600, 800);

    win->Run();

    win->Terminate();

}
