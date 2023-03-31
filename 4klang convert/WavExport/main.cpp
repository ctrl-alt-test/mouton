
#define _CRT_SECURE_NO_WARNINGS 1
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include "windows.h"
#include "mmsystem.h"
#include "mmreg.h"
#include "stdio.h"


////////////////////////////////////////////////
// sound
////////////////////////////////////////////////

// some song information
#include "4klang.h"

// MAX_SAMPLES gives you the number of samples for the whole song. we always produce stereo samples, so times 2 for the buffer
SAMPLE_TYPE	lpSoundBuffer[MAX_SAMPLES * 2];

/////////////////////////////////////////////////////////////////////////////////
// entry point
/////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	fprintf(stdout, "calculating sound. please wait ...\n");

	// fill the sound buffer
	_4klang_render(lpSoundBuffer);

	fprintf(stdout, "writing wav file ...\n");

	// init wave header
	char WaveHeader[44] =
	{
		'R', 'I', 'F', 'F',
		0, 0, 0, 0,				// filled below
		'W', 'A', 'V', 'E',
		'f', 'm', 't', ' ',
		16, 0, 0, 0,
		1, 0,
		2, 0,
		0x44, 0xac, 0, 0,
		0x10, 0xB1, 0x02, 0,
		4, 0,
		16, 0,
		'd', 'a', 't', 'a',
		0, 0, 0, 0				// filled below
	};
	*((DWORD*)(&WaveHeader[4])) = MAX_SAMPLES * 2 * 2 + 36;	// size of the rest of the file in bytes
	*((DWORD*)(&WaveHeader[40])) = MAX_SAMPLES * 2 * 2;		// size of raw sample data to come

	// write wave file
	FILE* file = fopen("../../Intro/sheep.wav", "wb");
	if (file)
	{
		fwrite(WaveHeader, 1, 44, file);
		for (int i = 0; i < MAX_SAMPLES * 2; i++)
		{
			// convert and clip each sample
#ifdef FLOAT_32BIT				
			int iin = (int)(lpSoundBuffer[i] * 32767);
#else
			int iin = (int)(lpSoundBuffer[i]);
#endif			
			if (iin > 32767) iin = 32767;
			if (iin < -32767) iin = -32767;
			short iout = iin;
			fwrite(&iout, 2, 1, file);
		}
		fclose(file);
	}

	fprintf(stdout, "wav export done!\n");
	Sleep(2000);
}
