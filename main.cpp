

#define DLLEXPORT extern "C" __declspec(dllexport) // Windows only

DLLEXPORT int adder(int arg1, int arg2)
{
    return arg1 + arg2;
}