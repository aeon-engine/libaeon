// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/perlin_noise.h>

namespace aeon::math
{

perlin_noise::perlin_noise()
    : persistence_{0}
    , frequency_{0}
    , amplitude_{0}
    , octaves_{0}
    , randomseed_{0}
{
}

perlin_noise::perlin_noise(const double persistence, const double frequency, const double amplitude, const int octaves,
                           const int randomseed)
    : persistence_{persistence}
    , frequency_{frequency}
    , amplitude_{amplitude}
    , octaves_{octaves}
    , randomseed_{2 + randomseed * randomseed}
{
}

void perlin_noise::set(const double persistence, const double frequency, const double amplitude, const int octaves,
                       const int randomseed) noexcept
{
    persistence_ = persistence;
    frequency_ = frequency;
    amplitude_ = amplitude;
    octaves_ = octaves;
    randomseed_ = 2 + randomseed * randomseed;
}

[[nodiscard]] auto perlin_noise::get_height(const double x, const double y) const noexcept -> double
{
    return amplitude_ * total(x, y);
}

[[nodiscard]] auto perlin_noise::total(const double i, const double j) const noexcept -> double
{
    // properties of one octave (changing each loop)
    auto t = 0.0;
    auto amplitude = 1.0;
    auto freq = frequency_;

    for (int k = 0; k < octaves_; ++k)
    {
        t += get_value(j * freq + randomseed_, i * freq + randomseed_) * amplitude;
        amplitude *= persistence_;
        freq *= 2;
    }

    return t;
}

[[nodiscard]] auto perlin_noise::get_value(const double x, const double y) const noexcept -> double
{
    const auto xint = static_cast<int>(x);
    const auto yint = static_cast<int>(y);
    const auto xfrac = x - xint;
    const auto yfrac = y - yint;

    // noise values
    const auto n01 = noise(xint - 1, yint - 1);
    const auto n02 = noise(xint + 1, yint - 1);
    const auto n03 = noise(xint - 1, yint + 1);
    const auto n04 = noise(xint + 1, yint + 1);
    const auto n05 = noise(xint - 1, yint);
    const auto n06 = noise(xint + 1, yint);
    const auto n07 = noise(xint, yint - 1);
    const auto n08 = noise(xint, yint + 1);
    const auto n09 = noise(xint, yint);

    const auto n12 = noise(xint + 2, yint - 1);
    const auto n14 = noise(xint + 2, yint + 1);
    const auto n16 = noise(xint + 2, yint);

    const auto n23 = noise(xint - 1, yint + 2);
    const auto n24 = noise(xint + 1, yint + 2);
    const auto n28 = noise(xint, yint + 2);

    const auto n34 = noise(xint + 2, yint + 2);

    // find the noise values of the four corners
    const auto x0y0 = 0.0625 * (n01 + n02 + n03 + n04) + 0.125 * (n05 + n06 + n07 + n08) + 0.25 * (n09);
    const auto x1y0 = 0.0625 * (n07 + n12 + n08 + n14) + 0.125 * (n09 + n16 + n02 + n04) + 0.25 * (n06);
    const auto x0y1 = 0.0625 * (n05 + n06 + n23 + n24) + 0.125 * (n03 + n04 + n09 + n28) + 0.25 * (n08);
    const auto x1y1 = 0.0625 * (n09 + n16 + n28 + n34) + 0.125 * (n08 + n14 + n06 + n24) + 0.25 * (n04);

    // interpolate between those values according to the x and y fractions
    const auto v1 = interpolate(x0y0, x1y0, xfrac); // interpolate in x direction (y)
    const auto v2 = interpolate(x0y1, x1y1, xfrac); // interpolate in x direction (y+1)
    const auto fin = interpolate(v1, v2, yfrac);    // interpolate in y direction

    return fin;
}

[[nodiscard]] auto perlin_noise::interpolate(const double x, const double y, const double a) const noexcept -> double
{
    const auto neg_a = 1.0 - a;
    const auto neg_a_sqr = neg_a * neg_a;
    const auto fac1 = 3.0 * (neg_a_sqr)-2.0 * (neg_a_sqr * neg_a);
    const auto a_sqr = a * a;
    const auto fac2 = 3.0 * a_sqr - 2.0 * (a_sqr * a);

    return x * fac1 + y * fac2; // add the weighted factors
}

[[nodiscard]] auto perlin_noise::noise(const int x, const int y) const noexcept -> double
{
    auto n = x + y * 57;
    n = (n << 13) ^ n;
    const auto t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - static_cast<double>(t) * 0.931322574615478515625e-9;
}

} // namespace aeon::math
