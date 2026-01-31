#include "midi_parser.h"
#include <string.h>
#include <stdio.h>

// Midi Note variables
static uint8_t last_status_byte = 0;
static uint8_t last_data_byte_note = 0;

// Midi Pitch variables
static uint8_t last_data_byte_pitch = 0;

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

MidiNoteEvent_t read_note(uint8_t byte)
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
		last_data_byte_note = 0;
		return event;
	}

	if (last_data_byte_note == 0)
	{
		// Note byte
		last_data_byte_note = byte;
		return event;
	}

	// Velocity byte
	if (IS_NOTE_ON(last_status_byte))
	{
		get_note_name(last_data_byte_note, event.note, sizeof(event.note));
		event.velocity = byte;
		event.valid = true;

		if (byte > 0)
		{
			event.type = NOTE_ON;
		}
		else
		{
			// Note OFF via velocity = 0
			event.type = NOTE_OFF;
		}
	}
	else if (IS_NOTE_OFF(last_status_byte))
	{
		get_note_name(last_data_byte_note, event.note, sizeof(event.note));
		event.velocity = 0;
		event.valid = true;
		event.type = NOTE_OFF;
	}

	last_data_byte_note = 0;
	return event;
}

MidiPitchEvent_t read_pitch(uint8_t byte)
{
	MidiPitchEvent_t event = {0};
	event.valid = false;

	if (IS_REALTIME(byte))
	{
		return event;
	}

	if (IS_STATUS_BYTE(byte))
	{
		if (IS_PITCH_BEND(byte))
		{
			last_status_byte = byte;
			last_data_byte_pitch = 0;
			return event;
		}
	}

	if (last_data_byte_pitch == 0)
	{
		last_data_byte_pitch = byte;
		return event;
	}

	if (IS_PITCH_BEND(last_status_byte))
	{
		event.lsb = last_data_byte_pitch;
		event.msb = byte;

		int16_t raw = ((event.msb << 7) | event.lsb);
		if (raw > 16383)
		{
			raw = 16383;
		}
		event.value = raw - 8192; // normalize
		event.valid = true;
		event.type = PITCH_BEND;
	}

	last_data_byte_pitch = 0;
	return event;
}

MidiControllerEvent_t read_controllers(uint8_t byte)
{
	;
}

// Function to handle midi event after event is determined
void handle_midi_event_note (MidiNoteEvent_t event)
{
	switch (event.type)
	{
		case NOTE_ON:
		case NOTE_OFF:
			//handle_note(event);
			break;
	}
}
