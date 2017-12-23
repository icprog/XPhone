#ifndef KEY_H_INCLUDED
	#define KEY_H_INCLUDED
	
	#include "main.h"
	#include <inttypes.h>
	#include <stdlib.h>
	#define KeyType uint8_t					// this is the data type used to index into the keys (for XPhone, this goes from 0 to 36).
	#define KeyIntensityType uint8_t		// this is the data type used to store the intensity of the key hit. 
	#define KeyStateType uint8_t			// this is the data type used to record the state of a key (boolean: 0 or 1)
	#define KeyTimeType uint32_t			// this is the data type used to record the time at which the key was played (ms)
	#define KeyTimeMax UINT32_MAX			// the is the max key time.

	// key input states
	KeyStateType key_input_states[KEYS];	// the key input states
	// key input cooldown periods
	#define KEY_COOLDOWN ((KeyTimeType)50)	// Once a key is hit, it takes this many milliseconds before the XPhone will recognize another key hit. If you hit they key a bunch of times within this window of time, it will only register the first key hit. This is a way of debouncing the input.
	KeyTimeType KeyCooldownTimes[KEYS];		// this array indicates the times (for each key) at which you can start looking for key hits again.   
	uint8_t KeyCooldownActive[KEYS];		// this array indicates (for each key) whether or not it is in its cooldown period.
	
	#define KEY_TRACK_EMPTY 255	
	/// Note structure
	// the notes to be played
	typedef struct Note {
		// the key to be played
		KeyType key;
		// the time between the start of the track and
		// when the key will be played (in milliseconds)
		KeyTimeType time;
		// how hard the key is going to be hit
		KeyIntensityType intensity;
		// pointer to the next element in the list
		struct Note *next;
	} Note;
	
	
	
	// TODO figure out a way to change uint32_t to SolTimType without having build issues. It is probably due to my shitty .h and .c structure...
	uint32_t keyIntensityMin[KEYS];
	uint32_t keyIntensityMax[KEYS];
	#define KEY_CAL_START	((uint32_t)1000)	// initial solenoid intensity
	#define KEY_CAL_STEP	((uint32_t)100)		// solenoid intensity step size.
	#define KEY_CAL_WAIT	(5)					// wait this many milliseconds after hitting the key to check the key's state.
	
	/// Functions
	Note* init_note(KeyType key, KeyTimeType time, KeyIntensityType intensity);
	void insert_note(Note **song, Note *note);
	void clear_song(Note *song);
	void key_init();
	void key_cal();
	void keys_read();
	
	#if SDL_PROGRAM
		/// SDLKey structure
		// the key to be rendered
		typedef struct {
			// holds a rectangle for the rendering
			// a rectangle or "a key"
			SDL_Rect rect;
			// the color of the rect or "the key"
			int color;
		} SDLKey;
		
		void play_song(Note *song, SDLKey *keys);
		
	#endif // SDL_PROGRAM

#endif // KEY_H_INCLUDED
