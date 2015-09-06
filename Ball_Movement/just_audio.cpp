// just_audio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

    #include <iostream>
    #include <windows.h>
    #include <mmsystem.h>
    #pragma comment(lib,"Winmm.lib")
    using namespace std;
    int main()
    {
    	for( int a = 0;a<1;a++)
    	{
    		PlaySound(L"explosion.wav", NULL, SND_FILENAME | SND_SYNC);
    		Sleep(3000);
    	}
    	return 0;
    }
