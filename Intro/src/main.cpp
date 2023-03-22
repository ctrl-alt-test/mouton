// custom build and feature flags
#ifdef DEBUG
	#define OPENGL_DEBUG        1
	#define FULLSCREEN          0
	#define DESPERATE           0
	#define BREAK_COMPATIBILITY 0
#else
	#define OPENGL_DEBUG        0
	#define FULLSCREEN          1
	#define DESPERATE           0
	#define BREAK_COMPATIBILITY 0
#endif
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>

#include "definitions.h"

// Global defines
#define SOUND_ON 
#define USE_FXAA
#define USE_CREATE_SHADER_PROGRAM // Save almost 40 bytes, require OpenGL 4.1 (Anat : doesn't work on my emulated windows)


#include "glext.h"
#pragma data_seg(".shader")
#include "shaders/shaders.inl"

#pragma data_seg(".pids")

// Shaders
static int shaderMain;
#ifdef USE_FXAA
static int shaderFXAA;
#endif

// Sound 
#ifdef SOUND_ON
#include "4klang.h"
static SAMPLE_TYPE	lpSoundBuffer[MAX_SAMPLES * 2];
static HWAVEOUT	hWaveOut;
#pragma data_seg(".wavefmt")
WAVEFORMATEX WaveFMT =
{
#ifdef FLOAT_32BIT	
	WAVE_FORMAT_IEEE_FLOAT,
#else
	WAVE_FORMAT_PCM,
#endif		
	2, // channels
	SAMPLE_RATE, // samples per sec
	SAMPLE_RATE * sizeof(SAMPLE_TYPE) * 2, // bytes per sec
	sizeof(SAMPLE_TYPE) * 2, // block alignment;
	sizeof(SAMPLE_TYPE) * 8, // bits per sample
	0 // extension not needed
};
#pragma data_seg(".wavehdr")
WAVEHDR WaveHDR =
{
	(LPSTR)lpSoundBuffer,
	MAX_SAMPLES * sizeof(SAMPLE_TYPE) * 2,			// MAX_SAMPLES*sizeof(float)*2(stereo)
	0,
	0,
	0,
	0,
	0,
	0
};
MMTIME MMTime =
{
	TIME_SAMPLES,
	0
};
#endif

#pragma code_seg(".main")
void entrypoint(void)
{
	// initialize window
	#if FULLSCREEN
		ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN);
		ShowCursor(0);
		const HDC hDC = GetDC(CreateWindow((LPCSTR)0xC018, 0, WS_POPUP | WS_VISIBLE | WS_MAXIMIZE, 0, 0, 0, 0, 0, 0, 0, 0));
	#else
		HDC hDC = GetDC(CreateWindow((LPCSTR)0xC018, 0, WS_POPUP | WS_VISIBLE, 0, 0, XRES, YRES, 0, 0, 0, 0));
	#endif

	// initalize opengl context
	SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
	wglMakeCurrent(hDC, wglCreateContext(hDC));
	
	// create and compile shader programs
	// Main shader
	int v = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_VERTEX_SHADER);
	((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(v, 1, &mouton_vert, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(v);
	int f = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);
	((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(f, 1, &mouton_frag, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(f);

	shaderMain = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderMain, v);
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderMain, f);
	((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(shaderMain);

	// FXAA
#ifdef USE_FXAA
	#ifdef USE_CREATE_SHADER_PROGRAM
		shaderFXAA = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_FRAGMENT_SHADER, 1, &fxaa_frag);
	#else
		f = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);
		((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(f, 1, &fxaa_frag, 0);
		((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(f);

		shaderFXAA = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
		((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderFXAA, f);
		((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(shaderFXAA);
	#endif
#endif

	// init sound
#ifdef SOUND_ON
	#if 1 // 4 more bytes
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_4klang_render, lpSoundBuffer, 0, 0);
	#else
		_4klang_render(lpSoundBuffer);
	#endif
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &WaveFMT, NULL, 0, CALLBACK_NULL);
	waveOutPrepareHeader(hWaveOut, &WaveHDR, sizeof(WaveHDR));
	waveOutWrite(hWaveOut, &WaveHDR, sizeof(WaveHDR));
#else
	long startTime = timeGetTime();
#endif

	// because all render passes need exactly the same input, we can do it once for all
#ifdef USE_FXAA
	((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif

	// main loop
	do
	{
#ifdef SOUND_ON
		waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
		float time = ((float)MMTime.u.sample) / 44100.0f;
#else
		long currentTime = timeGetTime();
		float time = (float)(currentTime - startTime) * 0.001f;
#endif

		#if !(DESPERATE)
			// do minimal message handling so windows doesn't kill your application
			// not always strictly necessary but increases compatibility and reliability a lot
			// normally you'd pass an msg struct as the first argument but it's just an
			// output parameter and the implementation presumably does a NULL check
			PeekMessage(0, 0, 0, 0, PM_REMOVE);
		#endif

		// main renderer
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(shaderMain);
		((PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f"))(0, time);
		glRects(-1, -1, 1, 1);

		// two pass FXAA
#ifdef USE_FXAA
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(shaderFXAA);
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, 0);
		glRects(-1, -1, 1, 1);

		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		glRects(-1, -1, 1, 1);
#endif
		SwapBuffers(hDC);

#ifdef SOUND_ON
	} while(MMTime.u.sample < MAX_SAMPLES && !GetAsyncKeyState(VK_ESCAPE));
#else
	} while (!GetAsyncKeyState(VK_ESCAPE));
#endif

	ExitProcess(0);
}
