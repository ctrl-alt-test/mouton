#include "editor.h"
#include "song.h"

#include "stdio.h"
#include "glext.h"

using namespace Leviathan;

#define USE_MESSAGEBOX 0

Editor::Editor() : lastFrameStart(0), lastFrameStop(0), trackPosition(0.0), trackEnd(0.0), state(Playing)
{
	printf("Editor opened...\n");
}

void Editor::beginFrame(const unsigned long time)
{
	lastFrameStart = time;
}

void Editor::endFrame(const unsigned long time)
{
	lastFrameStop = time;
}

void Editor::printFrameStatistics()
{
	const int frameTime = lastFrameStop - lastFrameStart;

	// calculate average fps over 'windowSize' of frames
	float fps = 0.0f;
	for (int i = 0; i < windowSize - 1; ++i)
	{
		timeHistory[i] = timeHistory[i + 1];
		fps += 1.0f / static_cast<float>(timeHistory[i]);
	}
	timeHistory[windowSize - 1] = frameTime;
	fps += 1.0f / static_cast<float>(frameTime);
	fps *= 1000.0f / static_cast<float>(windowSize);

	printf("%s: %0.2i:%0.2i (%i%%), frame duration: %i ms (running fps average: %2.2f) \r",
		state == Playing ? "Playing" : " Paused",
		// assuming y'all won't be making intros more than an hour long
		int(trackPosition/60.0), int(trackPosition) % 60, int(100.0f*trackPosition/trackEnd),
		frameTime, fps);
}

double Editor::handleEvents(Leviathan::Song* track, double position)
{
	if (GetAsyncKeyState(VK_MENU))
	{
		double seek = 0.0;
		if (GetAsyncKeyState(VK_DOWN))
		{
			state = Paused;
			track->pause();
		}
		if (GetAsyncKeyState(VK_UP))
		{
			state = Playing;
			track->play();
		}
		if (GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_SHIFT)) seek += 1.0;
		if (GetAsyncKeyState(VK_LEFT)  && !GetAsyncKeyState(VK_SHIFT)) seek -= 1.0;
		if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_SHIFT))  seek += 0.1;
		if (GetAsyncKeyState(VK_LEFT)  && GetAsyncKeyState(VK_SHIFT))  seek -= 0.1;
		if (position + seek != position)
		{
			position += seek;
			track->seek(position);
		}
	}

	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('S'))
		shaderUpdatePending = true;

	trackPosition = position;
	trackEnd = track->getLength();

	return position;
}

void Editor::updateShaders(int* mainShaderPID, bool force_update)
{
	if (shaderUpdatePending || force_update)
	{
		// make sure the file has finished writing to disk
		if (timeGetTime() - previousUpdateTime > 200)
		{
			// only way i can think of to clear the line without "status line" residue
			printf("Refreshing shaders...                                                   \n");

			Sleep(100);
			int newPID = reloadShaderSource("src/shaders/mouton.vert", "src/shaders/mouton.frag");
			if (newPID > 0) {
				int oldPID = *mainShaderPID;
				*mainShaderPID = newPID;
				((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))(oldPID);
			}
		}

		previousUpdateTime = timeGetTime();
		shaderUpdatePending = false;
	}
}

int Editor::reloadShaderSource(const char* filenameVS, const char* filenamePS)
{
	char* sourceVS = textFileRead(filenameVS);
	char* sourcePS = textFileRead(filenamePS);
	if (!sourceVS || !sourcePS) return -1;

	int shaderVS = compileShader(sourceVS, GL_VERTEX_SHADER);
	int shaderPS = compileShader(sourcePS, GL_FRAGMENT_SHADER);
	if (!shaderVS || !shaderPS) return -1;

	int shaderMain = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderMain, shaderVS);
	((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(shaderMain, shaderPS);
	((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(shaderMain);

	((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))(shaderVS);
	((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))(shaderPS);

	return shaderMain;
}


int Editor::compileShader(char* source, GLenum shaderType) {
	int pid = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))(shaderType);
	((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(pid, 1, &source, 0);
	((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(pid);

	int result = 0;
	((PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv"))(pid, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		// display compile log on failure
		static char errorBuffer[shaderErrorBufferLength];
		((PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog"))(pid, shaderErrorBufferLength - 1, NULL, static_cast<char*>(errorBuffer));

#if USE_MESSAGEBOX
		MessageBox(NULL, errorBuffer, "", 0x00000000L);
#endif
		printf("Compilation errors in %s\n", errorBuffer);
		return 0;
	}
	return pid;
}
char* Editor::textFileRead(const char* filename)
{
	long inputSize = 0;
	// we're of course opening a text file, but should be opened in binary ('b')
	// longer shaders are known to cause problems by producing garbage input when read
	FILE* file = fopen(filename, "rb");

	if (!file) {
		printf("Input shader file at \"%s\" not found, shader not reloaded\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	inputSize = ftell(file);
	rewind(file);

	char* shaderString = static_cast<char*>(calloc(inputSize + 1, sizeof(char)));
	fread(shaderString, sizeof(char), inputSize, file);
	fclose(file);

	shaderString[inputSize] = '\0';

	return shaderString;
}