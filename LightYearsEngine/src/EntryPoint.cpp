#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
    ly::Application* application = GetApplication();
    application->Run();
    delete application;
}
