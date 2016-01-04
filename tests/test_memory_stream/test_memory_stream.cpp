#define BOOST_TEST_MODULE test_memory_stream
#include <boost/test/unit_test.hpp>
#include <aeon/streams.h>

struct test_fixture_memory_stream_default_data
{
    test_fixture_memory_stream_default_data()
        : fixture_data({{'A', 'B', 'C', 'D', 'E'}})
        , fixture_data_written(0)
    {
        fixture_data_written = stream.write(&fixture_data[0], fixture_data.size());

        BOOST_REQUIRE_EQUAL(fixture_data.size(), fixture_data_written);
        BOOST_REQUIRE_EQUAL(stream.tell(), fixture_data_written);
        BOOST_REQUIRE_LE(fixture_data_written, stream.size());
    }

    ~test_fixture_memory_stream_default_data()
    {
    }

    aeon::streams::memory_stream stream;
    std::array<std::uint8_t, 5> fixture_data;
    std::size_t fixture_data_written;
};

BOOST_FIXTURE_TEST_SUITE(test_fixture_memory_stream_default_data_suite, test_fixture_memory_stream_default_data)

BOOST_AUTO_TEST_CASE(test_memory_stream_default_access_mode)
{
    int access_mode = stream.get_access_mode();

    BOOST_REQUIRE_EQUAL(access_mode, aeon::streams::access_mode::read_write);
    BOOST_REQUIRE_EQUAL(stream.is_readable(), true);
    BOOST_REQUIRE_EQUAL(stream.is_writable(), true);
}

BOOST_AUTO_TEST_CASE(test_memory_stream_write)
{
    std::uint8_t data[] = {'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    std::size_t data_written = stream.write(data, sizeof(data));

    BOOST_REQUIRE_EQUAL(data_written, sizeof(data));
    BOOST_REQUIRE_EQUAL(stream.tell(), fixture_data_written + sizeof(data));
    BOOST_REQUIRE_LE(fixture_data_written + sizeof(data), stream.size());
}

BOOST_AUTO_TEST_CASE(test_memory_stream_write_read)
{
    std::vector<std::uint8_t> readbackdata;
    readbackdata.resize(fixture_data_written);

    BOOST_REQUIRE_EQUAL(stream.seek(0, aeon::streams::stream::seek_direction::begin), true);

    std::size_t data_read = stream.read(&readbackdata[0], readbackdata.size());

    BOOST_REQUIRE_EQUAL(data_read, fixture_data_written);
    BOOST_REQUIRE_EQUAL(stream.tell(), 5);

    BOOST_REQUIRE_EQUAL_COLLECTIONS(std::begin(fixture_data), std::end(fixture_data), std::begin(readbackdata),
                                    std::end(readbackdata));
}

BOOST_AUTO_TEST_CASE(test_memory_stream_peek)
{
    bool result = stream.seek(-1, aeon::streams::stream::seek_direction::current);
    BOOST_REQUIRE_EQUAL(result, true);

    std::uint8_t peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'E');

    result = stream.seek(-1, aeon::streams::stream::seek_direction::current);
    BOOST_REQUIRE_EQUAL(result, true);

    peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'D');
}

BOOST_AUTO_TEST_CASE(test_memory_stream_seek_begin)
{
    bool result = stream.seek(0, aeon::streams::stream::seek_direction::begin);
    BOOST_REQUIRE_EQUAL(result, true);

    std::uint8_t peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'A');

    result = stream.seek(2, aeon::streams::stream::seek_direction::begin);
    BOOST_REQUIRE_EQUAL(result, true);

    peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'C');

    result = stream.seek(fixture_data_written, aeon::streams::stream::seek_direction::begin);

    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(test_memory_stream_seek_current)
{
    bool result = stream.seek(-3, aeon::streams::stream::seek_direction::current);
    BOOST_REQUIRE_EQUAL(result, true);

    std::uint8_t peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'C');

    result = stream.seek(2, aeon::streams::stream::seek_direction::current);
    BOOST_REQUIRE_EQUAL(result, true);

    peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'E');

    result = stream.seek(-10, aeon::streams::stream::seek_direction::current);

    BOOST_REQUIRE_EQUAL(result, false);

    result = stream.seek(10, aeon::streams::stream::seek_direction::current);

    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(test_memory_stream_seek_end)
{
    bool result = stream.seek(0, aeon::streams::stream::seek_direction::end);
    BOOST_REQUIRE_EQUAL(result, true);

    std::uint8_t peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'E');

    result = stream.seek(3, aeon::streams::stream::seek_direction::end);
    BOOST_REQUIRE_EQUAL(result, true);

    peek_data = 0;
    result = stream.peek(peek_data);

    BOOST_REQUIRE_EQUAL(result, true);
    BOOST_REQUIRE_EQUAL(peek_data, 'B');

    result = stream.seek(10, aeon::streams::stream::seek_direction::end);

    BOOST_REQUIRE_EQUAL(result, false);

    result = stream.seek(-10, aeon::streams::stream::seek_direction::current);

    BOOST_REQUIRE_EQUAL(result, false);
}

BOOST_AUTO_TEST_SUITE_END()
