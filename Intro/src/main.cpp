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

#include "definitions.h"

#include "glext.h"
#pragma data_seg(".shader")
#include "shaders/shaders.inl"

#pragma data_seg(".pids")

// static allocation saves a few bytes
static int shaderMain;
static int shaderFXAA;
static int shaderPostProcess;
// static HDC hDC;

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
	f = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);
	((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(f, 1, &fxaa_frag, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(f);

	shaderFXAA = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderFXAA, f);
	((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(shaderFXAA);


	// Post process
	f = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(GL_FRAGMENT_SHADER);
	((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(f, 1, &postprocess_frag, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(f);

	shaderPostProcess = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderPostProcess, f);
	((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(shaderPostProcess);



	// main loop
	long startTime = timeGetTime();
	do
	{
		long currentTime = timeGetTime();
		float time = (float)(currentTime - startTime) * 0.001f;

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
		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(shaderFXAA);
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, 0);
		glRects(-1, -1, 1, 1);

		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(shaderFXAA);
		glRects(-1, -1, 1, 1);

		// Post processing

		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(shaderPostProcess);
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, 0);
		int loc = ((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(shaderPostProcess, VAR_iTime);
		((PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f"))(loc, time);
		glRects(-1, -1, 1, 1);

		SwapBuffers(hDC);

	} while(!GetAsyncKeyState(VK_ESCAPE));

	ExitProcess(0);
}
