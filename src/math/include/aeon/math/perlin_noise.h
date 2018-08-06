/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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

    auto get_persistance() const noexcept
    {
        return persistence_;
    }

    auto get_frequency() const noexcept
    {
        return frequency_;
    }

    auto get_amplitude() const noexcept
    {
        return amplitude_;
    }

    auto get_octaves() const noexcept
    {
        return octaves_;
    }

    auto get_randomseed() const noexcept
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
    auto total(double i, double j) const noexcept -> double;
    auto get_value(double x, double y) const noexcept -> double;
    auto interpolate(double x, double y, double a) const noexcept -> double;
    auto noise(int x, int y) const noexcept -> double;

    double persistence_;
    double frequency_;
    double amplitude_;
    int octaves_;
    int randomseed_;
};

} // namespace aeon::math
