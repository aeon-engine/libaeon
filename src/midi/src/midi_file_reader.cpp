// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/midi/midi_file_reader.h>
#include <aeon/midi/midi_messages.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/endianness.h>
#include <aeon/common/bitflags.h>
#include <aeon/common/fourcc.h>
#include <stdexcept>

namespace aeon::midi
{

namespace meta_event
{
static const unsigned char sequence_number = 0x00;
static const unsigned char text_event = 0x01;
static const unsigned char copyright_notice = 0x02;
static const unsigned char track_name = 0x03;
static const unsigned char instrument_name = 0x04;
static const unsigned char lyric_text = 0x05;
static const unsigned char marker_text = 0x06;
static const unsigned char cue_point = 0x07;
static const unsigned char channel_prefix_assignment = 0x20;
static const unsigned char end_of_track = 0x2F;
static const unsigned char tempo_setting = 0x51;
static const unsigned char smpte_offset = 0x54;
static const unsigned char time_signature = 0x58;
static const unsigned char key_signature = 0x59;
static const unsigned char sequencer_specific = 0x7F;
} // namespace meta_event

midi_file_reader::midi_file_reader(const std::string &filename)
    : format_(midi_format::format0)
    , tracks_(0)
    , tempo_mode_(midi_tempo_mode::ppqn)
    , divisions_(0)
{
    read_file(filename);
}

midi_file_reader::~midi_file_reader() = default;

void midi_file_reader::read_file(const std::string &filename)
{
    streams::file_source_device stream{filename, streams::file_mode::binary};
    streams::stream_reader reader{stream};

    auto midi_data = reader.read_to_vector<std::uint8_t>();
    streams::memory_device memory_stream{std::move(midi_data)};

    read_header(memory_stream);
    read_all_track_chunks(memory_stream);
}

void midi_file_reader::read_header(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    streams::stream_reader reader(stream);

    std::uint32_t mthd = 0;
    reader >> mthd;

    if (common::endianness::swap32(mthd) != common::fourcc('M', 'T', 'h', 'd'))
        throw std::runtime_error("Invalid or corrupt midi file. MThd not found.");

    std::uint32_t header_length = 0;
    reader >> header_length;
    header_length = common::endianness::swap32(header_length);

    if (header_length != 6)
        throw std::runtime_error("Invalid or corrupt midi file. Header length is expected to be 6.");

    std::uint16_t format = 0;
    reader >> format;
    parse_format(common::endianness::swap16(format));

    std::uint16_t tracks = 0;
    reader >> tracks;
    tracks_ = common::endianness::swap16(tracks);

    std::uint16_t divisions = 0;
    reader >> divisions;
    parse_divisions(common::endianness::swap16(divisions));
}

void midi_file_reader::parse_format(const std::uint16_t format)
{
    switch (format)
    {
        case 0:
            format_ = midi_format::format0;
            return;
        case 1:
            format_ = midi_format::format1;
            return;
        case 2:
            format_ = midi_format::format2;
            throw std::runtime_error("Midi format 2 is untested.");
        default:
            break;
    }

    throw std::runtime_error("Invalid or corrupt midi file. Format must be 0, 1 or 2.");
}

void midi_file_reader::parse_divisions(const std::uint16_t divisions)
{
    // If bit 0x80 is not set, the midi file uses ppqn mode; otherwise smpte.
    if (!common::check_bit_flag<std::uint16_t>(divisions, 0x8000))
    {
        tempo_mode_ = midi_tempo_mode::ppqn;
        divisions_ = divisions;
    }
    else
    {
        tempo_mode_ = midi_tempo_mode::smpte;
        throw std::runtime_error("SMPTE is untested.");
    }
}

void midi_file_reader::read_all_track_chunks(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    for (auto i = 0u; i < tracks_; ++i)
    {
        read_next_track_chunk(stream);
    }
}

void midi_file_reader::read_next_track_chunk(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    streams::stream_reader reader{stream};
    auto track_data = reader.read_to_vector<std::uint8_t>(read_track_header(stream));
    streams::memory_device memory_stream{std::move(track_data)};
    parse_track_data(memory_stream);
}

[[nodiscard]] std::uint32_t
    midi_file_reader::read_track_header(streams::memory_device<std::vector<std::uint8_t>> &stream) const
{
    streams::stream_reader reader{stream};

    std::uint32_t mtrk = 0;
    reader >> mtrk;

    if (common::endianness::swap32(mtrk) != common::fourcc('M', 'T', 'r', 'k'))
        throw std::runtime_error("Invalid or corrupt midi file. MTrk not found.");

    std::uint32_t track_length = 0;
    reader >> track_length;
    return common::endianness::swap32(track_length);
}

void midi_file_reader::parse_track_data(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    streams::stream_reader reader{stream};

    while (!stream.eof())
    {
        auto vtime = read_vtime(stream);
        std::uint8_t event = 0;
        reader >> event;

        (void)vtime;
        if (event == messages::meta)
        {
            parse_meta_event(stream);
        }
        else if (event == messages::system_exclusive || event == messages::end_of_exclusive)
        {
            parse_sysex_event(stream);
        }
        else
        {
            parse_midi_event(stream, event);
        }
    }
}

[[nodiscard]] std::uint32_t midi_file_reader::read_vtime(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    streams::stream_reader reader{stream};

    std::uint8_t value_part;
    reader >> value_part;

    std::uint32_t value = value_part & ~0x80;

    while (common::check_bit_flag<std::uint8_t>(value_part, 0x80))
    {
        reader >> value_part;
        value = (value << 7);
        value += value_part & ~0x80;
    }

    return value;
}

void midi_file_reader::parse_meta_event(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    streams::stream_reader reader{stream};
    std::uint8_t meta_type = 0;
    reader >> meta_type;

    const auto metadata_length = read_vtime(stream);

    if (metadata_length == 0)
        return;

    auto metadata = reader.read_to_vector<std::uint8_t>(metadata_length);
}

void midi_file_reader::parse_sysex_event(streams::memory_device<std::vector<std::uint8_t>> &stream)
{
    std::uint32_t sysex_length = read_vtime(stream);

    if (sysex_length == 0)
        return;

    streams::stream_reader reader{stream};
    auto sysex_data = reader.read_to_vector<std::uint8_t>(sysex_length);
}

void midi_file_reader::parse_midi_event(streams::memory_device<std::vector<std::uint8_t>> &stream,
                                        const std::uint8_t message)
{
    streams::stream_reader reader{stream};

    if ((message & 0xF0) == messages::note_off)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t velocity = 0;
        reader >> velocity;
    }
    else if ((message & 0xF0) == messages::note_on)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t velocity = 0;
        reader >> velocity;
    }
    else if ((message & 0xF0) == messages::polyphonic_key_pressure)
    {
        std::uint8_t key = 0;
        reader >> key;

        std::uint8_t pressure = 0;
        reader >> pressure;
    }
    else if ((message & 0xF0) == messages::controller_change)
    {
        std::uint8_t controller_number = 0;
        reader >> controller_number;

        std::uint8_t controller_value = 0;
        reader >> controller_value;
    }
    else if ((message & 0xF0) == messages::program_change)
    {
        std::uint8_t program_number = 0;
        reader >> program_number;
    }
    else if ((message & 0xF0) == messages::channel_pressure)
    {
        std::uint8_t pressure = 0;
        reader >> pressure;
    }
    else if ((message & 0xF0) == messages::pitch_bend)
    {
        std::uint8_t value_lsb = 0;
        reader >> value_lsb;

        std::uint8_t value_msb = 0;
        reader >> value_msb;
    }
    else
    {
        std::uint8_t message2 = 0;
        reader >> message2;

        std::runtime_error("Invalid or corrupt midi file. Unexpected midi message.");
    }
}

} // namespace aeon::midi
