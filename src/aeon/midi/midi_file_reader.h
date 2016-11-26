/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{

namespace streams
{
class memory_stream;
}

namespace midi
{

enum class midi_read_mode
{
    normal,      // Keep the midi data as-is
    split_tracks // Split format 0 track data
};

enum class midi_format
{
    format0,
    format1,
    format2
};

enum class midi_tempo_mode
{
    ppqn, // Pulses per quarter note
    smpte // SMPTE time codes
};

class midi_file_reader
{
public:
    explicit midi_file_reader(const std::string &filename);
    virtual ~midi_file_reader();

    auto get_format() const
    {
        return format_;
    }

    auto get_track_count() const
    {
        return tracks_;
    }

    auto get_tempo_mode() const
    {
        return tempo_mode_;
    }

    auto get_divisions() const
    {
        return divisions_;
    }

protected:
    // Ctor for unittesting
    midi_file_reader() = default;

    void read_file(const std::string &filename);

    void read_header(streams::memory_stream &stream);
    void parse_format(const std::uint16_t format);
    void parse_divisions(const std::uint16_t divisions);

    void read_all_track_chunks(streams::memory_stream &stream);
    void read_next_track_chunk(streams::memory_stream &stream);
    std::uint32_t read_track_header(streams::memory_stream &stream) const;
    void parse_track_data(streams::memory_stream &stream);
    std::uint32_t read_vtime(streams::memory_stream &stream);

    void parse_meta_event(streams::memory_stream &stream);
    void parse_sysex_event(streams::memory_stream &stream);
    void parse_midi_event(streams::memory_stream &stream, const std::uint8_t message);

    midi_format format_;
    unsigned int tracks_;

    midi_tempo_mode tempo_mode_;
    unsigned int divisions_;
};

} // namespace midi
} // namespace aeon
