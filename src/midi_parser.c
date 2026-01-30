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

void read_note_velocity (uint8_t byte, char buf[], size_t len)
{
	if (len == 0) return;

	if (byte != MIDI_CLOCK)
	{
	        if (IS_STATUS_BYTE(byte))
	        {
	                last_status_byte = byte;
	                last_data_byte = 0;
	        }
	        else
	        {
	                if (last_data_byte == 0)
	                {
	                        //Note byte
	                        last_data_byte = byte;
	                }
	                else
	                {
	                        // Velocity byte
	                        if (IS_NOTE_ON(last_status_byte) && byte > 0)
	                        {
	                                char temp_buf[32] = {0};
	                                get_note_name(last_data_byte, temp_buf, sizeof(temp_buf));
	                                snprintf(buf, len, "Note: %s, Velocity %u", temp_buf, byte);
	                        }
	                        last_data_byte = 0;
	                }

	        }
	}
}
