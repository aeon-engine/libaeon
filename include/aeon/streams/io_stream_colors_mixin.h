#ifndef aeon_streams_io_stream_colors_mixin_h__
#define aeon_streams_io_stream_colors_mixin_h__

namespace aeon
{
namespace streams
{

enum class color
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

enum class weight
{
    normal,
    bold
};

class io_stream_colors_mixin
{
public:
    void set_color(color c, weight w = weight::normal);
    void reset_color();
};

} // namespace streams
} // namespace aeon

#endif // aeon_streams_io_stream_colors_mixin_h__
