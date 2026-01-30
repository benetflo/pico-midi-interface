#include "midi_parser.h"
#include <string.h>
#include <stdio.h>

static uint8_t last_status_byte = 0;
static uint8_t last_data_byte = 0;

// Array of note names
const char * note_names[12] =
{
	"C", "C#", "D", "D#", "E", "F",
	"F#", "G", "G#", "A", "A#", "B"
};

// Returns where note is in octave
int note_to_pitch (int note)
{
	return note % 12;
}

// Returns what octave note is in
int note_to_octave (int note)
{
	return (note / 12) - 1;
}

void get_note_name (int note, char * buf, size_t len)
{
	int pitch = note_to_pitch(note);
	int octave = note_to_octave(note);

	snprintf(buf, len, "%s%d", note_names[pitch], octave);
}

MidiNoteEvent_t read_note_velocity(uint8_t byte)
{
	MidiNoteEvent_t event = {0};
	event.valid = false;

	if (IS_REALTIME(byte))
	{
		 return event;
	}

	if (IS_STATUS_BYTE(byte))
	{
		last_status_byte = byte;
		last_data_byte = 0;
		return event;
	}

	if (last_data_byte == 0)
	{
		// Note byte
		last_data_byte = byte;
		return event;
	}

	// Velocity byte
	if (IS_NOTE_ON(last_status_byte) && byte > 0)
	{
		get_note_name(last_data_byte, event.note, sizeof(event.note));
		event.velocity = byte;
		event.valid = true;
	}

	last_data_byte = 0;
	return event;
}
