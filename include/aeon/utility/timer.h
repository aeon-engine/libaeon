#ifndef aeon_utility_timer_h__
#define aeon_utility_timer_h__

namespace aeon
{
namespace utility
{

class timer
{
public:
    timer();
    ~timer();

    void reset();

    double get_time_difference();

private:
    std::chrono::time_point<std::chrono::system_clock> start_time_;
};

} // namespace utility
} // namespace aeon

#endif // aeon_utility_timer_h__
