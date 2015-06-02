#define BOOST_TEST_MODULE test_circular_buffer_stream
#include <boost/test/unit_test.hpp>
#include <aeon/streams.h>

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_read_write_basic)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t data1[] = { 'A', 'B', 'C', 'D', 'E' };
    std::size_t result = buffer.write(data1, sizeof(data1));
    BOOST_CHECK_EQUAL(result, sizeof(data1));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(data1));

    std::uint8_t data1_readback[sizeof(data1)] = { 0 };
    result = buffer.read(data1_readback, sizeof(data1_readback));
    BOOST_CHECK_EQUAL(result, sizeof(data1_readback));
    BOOST_CHECK_EQUAL(buffer.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(data1), std::end(data1),
        std::begin(data1_readback), std::end(data1_readback)
    );

    std::uint8_t data2[] = { 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M' };
    result = buffer.write(data2, sizeof(data2));
    BOOST_CHECK_EQUAL(result, sizeof(data2));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(data2));

    std::uint8_t data2_readback[sizeof(data2)] = { 0 };
    result = buffer.read(data2_readback, sizeof(data2_readback));
    BOOST_CHECK_EQUAL(result, sizeof(data2_readback));
    BOOST_CHECK_EQUAL(buffer.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(data2), std::end(data2),
        std::begin(data2_readback), std::end(data2_readback)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_read_write)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    BOOST_CHECK_EQUAL(result, sizeof(magic_data));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(magic_data));

    std::uint8_t readbackdata[sizeof(magic_data)];
    result = buffer.read(readbackdata, sizeof(readbackdata));

    BOOST_CHECK_EQUAL(result, sizeof(readbackdata));
    BOOST_CHECK_EQUAL(buffer.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(magic_data), std::end(magic_data),
        std::begin(readbackdata), std::end(readbackdata)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_write_too_big)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    BOOST_CHECK_EQUAL(result, sizeof(magic_data));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(magic_data));

    // Write data that is too big.
    std::uint8_t fake_data[101];
    std::memset(fake_data, 'B', sizeof(fake_data));
    result = buffer.write(fake_data, sizeof(fake_data));

    BOOST_CHECK_EQUAL(result, 0);
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(magic_data));

    // Now read back the original data and see if it's untouched
    std::uint8_t readbackdata[sizeof(magic_data)];
    result = buffer.read(readbackdata, sizeof(readbackdata));

    BOOST_CHECK_EQUAL(result, sizeof(readbackdata));
    BOOST_CHECK_EQUAL(buffer.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(magic_data), std::end(magic_data), 
        std::begin(readbackdata), std::end(readbackdata)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_read_too_big)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t data[101];
    std::size_t result = buffer.read(data, sizeof(data));

    // The read should have failed.
    BOOST_CHECK_EQUAL(result, 0);
    BOOST_CHECK_EQUAL(buffer.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_write_wrap_around)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[50];
    std::memset(magic_data, 'A', sizeof(magic_data));

    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    BOOST_REQUIRE_EQUAL(result, sizeof(magic_data));
    BOOST_REQUIRE_EQUAL(buffer.size(), sizeof(magic_data));

    // Now write some more data that would cause an exception
    std::uint8_t magic_data2[60];
    std::memset(magic_data2, 'B', sizeof(magic_data2));

    BOOST_REQUIRE_EXCEPTION(
        buffer.write(magic_data2, sizeof(magic_data2));,
        aeon::streams::circular_buffer_stream_exception,
        [](aeon::streams::circular_buffer_stream_exception const &) { return true; }
    );

    BOOST_REQUIRE_EQUAL(buffer.size(), sizeof(magic_data));

    // Try to read back the 50 bytes we wrote earlier
    std::uint8_t readbackdata2[sizeof(magic_data)];
    result = buffer.read(readbackdata2, sizeof(readbackdata2));

    BOOST_REQUIRE_EQUAL(result, sizeof(readbackdata2));
    BOOST_REQUIRE_EQUAL(buffer.size(), 0);

    BOOST_REQUIRE_EQUAL_COLLECTIONS(
        std::begin(magic_data), std::end(magic_data),
        std::begin(readbackdata2), std::end(readbackdata2)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_read_write_multiple)
{
    aeon::streams::circular_buffer_stream<50> buffer;

    std::uint8_t base_character = 'A';

    for (int i = 0; i < 26; ++i)
    {
        std::uint8_t magic_data[28];
        std::memset(magic_data, base_character + i, sizeof(magic_data));
        std::size_t result = buffer.write(magic_data, sizeof(magic_data));

        BOOST_CHECK_EQUAL(result, sizeof(magic_data));
        BOOST_CHECK_EQUAL(buffer.size(), sizeof(magic_data));

        std::uint8_t readbackdata[sizeof(magic_data)];
        result = buffer.read(readbackdata, sizeof(readbackdata));

        BOOST_CHECK_EQUAL(result, sizeof(readbackdata));
        BOOST_CHECK_EQUAL(buffer.size(), 0);

        BOOST_CHECK_EQUAL_COLLECTIONS(
            std::begin(magic_data), std::end(magic_data),
            std::begin(readbackdata), std::end(readbackdata)
        );
    }
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_overread)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    BOOST_CHECK_EQUAL(buffer.size(), 0);

    std::uint8_t data[5];
    std::size_t result = buffer.read(data, sizeof(data));

    BOOST_CHECK_EQUAL(result, 0);
    BOOST_CHECK_EQUAL(buffer.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_default_size)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    BOOST_CHECK_EQUAL(buffer.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_maximum_size)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    BOOST_CHECK_EQUAL(buffer.max_size(), 10);
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_move_constructor)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[5] = { 'A', 'B', 'C', 'D', 'E' };
    std::size_t result = buffer.write(data, sizeof(data));

    BOOST_CHECK_EQUAL(result, sizeof(data));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(data));
    BOOST_CHECK_EQUAL(buffer.max_size(), 10);

    aeon::streams::circular_buffer_stream<10> buffer2 = std::move(buffer);

    BOOST_CHECK_EQUAL(buffer2.size(), sizeof(data));
    BOOST_CHECK_EQUAL(buffer2.max_size(), 10);

    std::uint8_t readbackdata[sizeof(data)];
    result = buffer2.read(readbackdata, sizeof(readbackdata));

    BOOST_CHECK_EQUAL(result, sizeof(readbackdata));
    BOOST_CHECK_EQUAL(buffer2.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(data), std::end(data),
        std::begin(readbackdata), std::end(readbackdata)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_move_assignment)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[] = { 'A', 'B', 'C', 'D', 'E' };
    std::size_t result = buffer.write(data, sizeof(data));

    BOOST_CHECK_EQUAL(result, sizeof(data));
    BOOST_CHECK_EQUAL(buffer.size(), sizeof(data));
    BOOST_CHECK_EQUAL(buffer.max_size(), 10);

    aeon::streams::circular_buffer_stream<10> buffer2;
    BOOST_CHECK_EQUAL(buffer2.size(), 0);

    buffer2 = std::move(buffer);

    BOOST_CHECK_EQUAL(buffer2.size(), sizeof(data));
    BOOST_CHECK_EQUAL(buffer2.max_size(), 10);

    std::uint8_t readbackdata[sizeof(data)];
    result = buffer2.read(readbackdata, sizeof(readbackdata));

    BOOST_CHECK_EQUAL(result, sizeof(readbackdata));
    BOOST_CHECK_EQUAL(buffer2.size(), 0);

    BOOST_CHECK_EQUAL_COLLECTIONS(
        std::begin(data), std::end(data),
        std::begin(readbackdata), std::end(readbackdata)
    );
}

BOOST_AUTO_TEST_CASE(test_circular_buffer_stream_peek)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[] = { 'A', 'B', 'C', 'D', 'E' };
    std::size_t result = buffer.write(data, sizeof(data));
    BOOST_CHECK_EQUAL(result, sizeof(data));

    std::uint8_t peek_value = 0;
    bool peek_result = buffer.peek(peek_value);
    BOOST_CHECK_EQUAL(peek_result, true);
    BOOST_CHECK_EQUAL(peek_value, 'A');

    std::uint8_t dummy[3];
    result = buffer.read(dummy, sizeof(dummy));
    BOOST_CHECK_EQUAL(result, sizeof(dummy));

    peek_value = 0;
    peek_result = buffer.peek(peek_value);
    BOOST_CHECK_EQUAL(peek_result, true);
    BOOST_CHECK_EQUAL(peek_value, 'D');

    result = buffer.write(data, sizeof(data));
    BOOST_CHECK_EQUAL(result, sizeof(data));

    peek_value = 0;
    peek_result = buffer.peek(peek_value);
    BOOST_CHECK_EQUAL(peek_result, true);
    BOOST_CHECK_EQUAL(peek_value, 'D');
}
