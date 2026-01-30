#ifndef MIDI_PARSER_H
#define MIDI_PARSER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MIDI_CLOCK						0xF8
#define MIDI_NOTE_ON						0x90
#define MIDI_NOTE_OFF						0x80
#define MIDI_START						0xFA
#define MIDI_STOP						0xFC

#define IS_STATUS_BYTE(byte)					((byte) & 0x80)
#define IS_NOTE_ON(byte)					(((byte) & 0xF0) == MIDI_NOTE_ON)
#define IS_NOTE_OFF(byte)					(((byte) & 0xF0) == MIDI_NOTE_OFF)
#define IS_REALTIME(byte)     					((byte) >= 0xF8) // realtime-bytes

typedef struct
{
	char note[4];
	uint8_t velocity;
	bool valid;
} MidiNoteEvent_t;


// Returns where note is in octave
int note_to_pitch (int note);
int note_to_octave (int note);
void get_note_name (int note, char * buf, size_t len);
MidiNoteEvent_t read_note_velocity (uint8_t byte);

#endif
