#ifndef MIDI_PARSER_H
#define MIDI_PARSER_H

#include <stddef.h>
#include <stdint.h>

#define MIDI_CLOCK 			0xF8

#define IS_STATUS_BYTE(byte)		((byte) & 0x80)
#define IS_NOTE_ON(byte)		(((byte) & 0xF0) == 0x90)
#define IS_NOTE_OFF(byte)		(((byte) & 0xF0) == 0x80)

// Returns where note is in octave
int note_to_pitch (int note);
int note_to_octave (int note);
void get_note_name (int note, char * buf, size_t len);
void read_note_velocity (uint8_t byte, char buf[], size_t len);

#endif
