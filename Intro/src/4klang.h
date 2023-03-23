// some useful song defines for 4klang
#define SAMPLE_RATE 44100
#define BPM 130.011795
#define MAX_INSTRUMENTS 16
#define MAX_PATTERNS 82
#define PATTERN_SIZE_SHIFT 4
#define PATTERN_SIZE (1 << PATTERN_SIZE_SHIFT)
#define MAX_TICKS (MAX_PATTERNS*PATTERN_SIZE)
#define SAMPLES_PER_TICK 5087
#define MAX_SAMPLES (SAMPLES_PER_TICK*MAX_TICKS)
#define POLYPHONY 2
#define FLOAT_32BIT
#define SAMPLE_TYPE float

#define WINDOWS_OBJECT

// declaration of the external synth render function, you'll always need that
extern "C" void  __stdcall	_4klang_render(void*);
// declaration of the external envelope buffer. access only if you're song was exported with that option
extern "C" float _4klang_envelope_buffer;
// declaration of the external note buffer. access only if you're song was exported with that option
extern "C" int   _4klang_note_buffer;
