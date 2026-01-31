#ifndef MIDI_PARSER_H
#define MIDI_PARSER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


// MIDI STATUS BYTES
#define MIDI_CLOCK						0xF8
#define MIDI_NOTE_ON						0x90
#define MIDI_NOTE_OFF						0x80
#define MIDI_START						0xFA
#define MIDI_STOP						0xFC
#define MIDI_PITCH_BEND						0xE0

#define IS_STATUS_BYTE(byte)					((byte) & MIDI_NOTE_OFF)
#define IS_NOTE_ON(byte)					(((byte) & 0xF0) == MIDI_NOTE_ON)
#define IS_NOTE_OFF(byte)					(((byte) & 0xF0) == MIDI_NOTE_OFF)
#define IS_REALTIME(byte)     					((byte) >= MIDI_CLOCK) // realtime-bytes
#define IS_PITCH_BEND(byte)					(((byte) & 0xF0) == 0xE0)

typedef enum
{
        NOTE_ON,
        NOTE_OFF,
	PITCH_BEND
} EventType_t;

typedef struct
{
	char note[4];
	uint8_t velocity;
	bool valid;
	EventType_t type;
} MidiNoteEvent_t;

typedef struct
{
	uint8_t lsb;
	uint8_t msb;
	int16_t value; // to store full value in range -8192 to +8191
	bool valid;
	EventType_t type;
} MidiPitchEvent_t;

typedef struct
{
	;
} MidiControllerEvent_t;

// Returns where note is in octave
int note_to_pitch (int note);
int note_to_octave (int note);
void get_note_name (int note, char * buf, size_t len);
MidiNoteEvent_t read_note (uint8_t byte);
MidiPitchEvent_t read_pitch(uint8_t byte);
MidiControllerEvent_t read_controller(uint8_t byte);
void handle_midi_event_note (MidiNoteEvent_t event);
void handle_midi_event_pitch (MidiPitchEvent_t event);
void handle_midi_event_controller (MidiControllerEvent_t event);
#endif
