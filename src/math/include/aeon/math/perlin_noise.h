// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

class perlin_noise
{
public:
    perlin_noise();
    perlin_noise(const double persistence, const double frequency, const double amplitude, const int octaves,
                 const int randomseed);

    auto get_height(const double x, const double y) const noexcept -> double;

    [[nodiscard]] auto get_persistance() const noexcept
    {
        return persistence_;
    }

    [[nodiscard]] auto get_frequency() const noexcept
    {
        return frequency_;
    }

    [[nodiscard]] auto get_amplitude() const noexcept
    {
        return amplitude_;
    }

    [[nodiscard]] auto get_octaves() const noexcept
    {
        return octaves_;
    }

    [[nodiscard]] auto get_randomseed() const noexcept
    {
        return randomseed_;
    }

    void set(const double persistence, const double frequency, const double amplitude, const int octaves,
             const int randomseed) noexcept;

    void set_persistance(const double persistence) noexcept
    {
        persistence_ = persistence;
    }

    void set_frequency(const double frequency) noexcept
    {
        frequency_ = frequency;
    }

    void set_amplitude(const double amplitude) noexcept
    {
        amplitude_ = amplitude;
    }

    void set_octaves(const int octaves) noexcept
    {
        octaves_ = octaves;
    }

    void set_random_seed(const int randomseed) noexcept
    {
        randomseed_ = randomseed;
    }

private:
    [[nodiscard]] auto total(double i, double j) const noexcept -> double;
    [[nodiscard]] auto get_value(double x, double y) const noexcept -> double;
    [[nodiscard]] auto interpolate(double x, double y, double a) const noexcept -> double;
    [[nodiscard]] auto noise(int x, int y) const noexcept -> double;

    double persistence_;
    double frequency_;
    double amplitude_;
    int octaves_;
    int randomseed_;
};

} // namespace aeon::math
