/* Copyright (c) 2007-2012 Eliot Eshelman. Adapted by Robin Degen for libaeon.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <aeon/math/simplex_noise.h>
#include <stdexcept>
#include <limits>
#include <cmath>

namespace aeon::math::simplex_noise
{

// The gradients are the midpoints of the vertices of a cube.
static const int grad3[12][3] = {{1, 1, 0},  {-1, 1, 0},  {1, -1, 0}, {-1, -1, 0}, {1, 0, 1},  {-1, 0, 1},
                                 {1, 0, -1}, {-1, 0, -1}, {0, 1, 1},  {0, -1, 1},  {0, 1, -1}, {0, -1, -1}};

// The gradients are the midpoints of the vertices of a hypercube.
static const int grad4[32][4] = {
    {0, 1, 1, 1},    {0, 1, 1, -1},   {0, 1, -1, 1},   {0, 1, -1, -1}, {0, -1, 1, 1},  {0, -1, 1, -1}, {0, -1, -1, 1},
    {0, -1, -1, -1}, {1, 0, 1, 1},    {1, 0, 1, -1},   {1, 0, -1, 1},  {1, 0, -1, -1}, {-1, 0, 1, 1},  {-1, 0, 1, -1},
    {-1, 0, -1, 1},  {-1, 0, -1, -1}, {1, 1, 0, 1},    {1, 1, 0, -1},  {1, -1, 0, 1},  {1, -1, 0, -1}, {-1, 1, 0, 1},
    {-1, 1, 0, -1},  {-1, -1, 0, 1},  {-1, -1, 0, -1}, {1, 1, 1, 0},   {1, 1, -1, 0},  {1, -1, 1, 0},  {1, -1, -1, 0},
    {-1, 1, 1, 0},   {-1, 1, -1, 0},  {-1, -1, 1, 0},  {-1, -1, -1, 0}};

// Permutation table.  The same list is repeated twice.
static const int perm[512] = {
    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142,
    8,   99,  37,  240, 21,  10,  23,  190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203,
    117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175, 74,  165,
    71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,
    55,  46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,
    18,  169, 200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250,
    124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189,
    28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,
    129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228, 251, 34,
    242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,
    181, 199, 106, 157, 184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,  222, 114,
    67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180,

    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142,
    8,   99,  37,  240, 21,  10,  23,  190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203,
    117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175, 74,  165,
    71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,
    55,  46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,
    18,  169, 200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250,
    124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189,
    28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,
    129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228, 251, 34,
    242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,
    181, 199, 106, 157, 184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,  222, 114,
    67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180};

// A lookup table to traverse the simplex around a given point in 4D.
static const int simplex[64][4] = {
    {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 0, 0, 0}, {0, 2, 3, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 2, 3, 0},
    {0, 2, 1, 3}, {0, 0, 0, 0}, {0, 3, 1, 2}, {0, 3, 2, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 3, 2, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {1, 2, 0, 3}, {0, 0, 0, 0}, {1, 3, 0, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 3, 0, 1}, {2, 3, 1, 0},
    {1, 0, 2, 3}, {1, 0, 3, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 0, 3, 1}, {0, 0, 0, 0}, {2, 1, 3, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {2, 0, 1, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {3, 0, 1, 2}, {3, 0, 2, 1}, {0, 0, 0, 0}, {3, 1, 2, 0},
    {2, 1, 0, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {3, 1, 0, 2}, {0, 0, 0, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};

/*
    2D, 3D and 4D Simplex Noise functions return 'random' values in (-1, 1).
    This algorithm was originally designed by Ken Perlin, but my code has been
    adapted from the implementation written by Stefan Gustavson (stegu@itn.liu.se)

    Raw Simplex noise functions return the value generated by Ken's algorithm.

    Scaled Raw Simplex noise functions adjust the range of values returned from the
    traditional (-1, 1) to whichever bounds are passed to the function.

    Multi-Octave Simplex noise functions combine multiple noise values to create a
    more complex result. Each successive layer of noise is adjusted and scaled.

    Scaled Multi-Octave Simplex noise functions scale the values returned from the
    traditional (-1,1) range to whichever range is passed to the function.

    In many cases, you may think you only need a 1D noise function, but in practice
    2D  is almost always better.  For instance, if you're using the current frame
    number  as the parameter for the noise, all objects will end up with the same
    noise value  at each frame. By adding a second parameter on the second
    dimension, you can ensure that each gets a unique noise value and they don't
    all look identical.
*/

// 2D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
[[nodiscard]] auto octave_noise_2d(const float octaves, const float persistence, const float scale, const float x,
                                   const float y) -> float
{
    auto total = 0.0f;
    auto frequency = scale;
    auto amplitude = 1.0f;

    // We have to keep track of the largest possible amplitude,
    // because each octave adds more, and we need a value in [-1, 1].
    auto maxAmplitude = 0.0f;

    for (auto i = 0; i < octaves; ++i)
    {
        total += raw_noise_2d(x * frequency, y * frequency) * amplitude;

        frequency *= 2.0f;
        maxAmplitude += amplitude;
        amplitude *= persistence;
    }

    return total / maxAmplitude;
}

// 3D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
[[nodiscard]] auto octave_noise_3d(const float octaves, const float persistence, const float scale, const float x,
                                   const float y, const float z) -> float
{
    auto total = 0.0f;
    auto frequency = scale;
    auto amplitude = 1.0f;

    // We have to keep track of the largest possible amplitude,
    // because each octave adds more, and we need a value in [-1, 1].
    auto maxAmplitude = 0.0f;

    for (auto i = 0; i < octaves; ++i)
    {
        total += raw_noise_3d(x * frequency, y * frequency, z * frequency) * amplitude;

        frequency *= 2.0f;
        maxAmplitude += amplitude;
        amplitude *= persistence;
    }

    return total / maxAmplitude;
}

// 4D Multi-octave Simplex noise.
//
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
[[nodiscard]] auto octave_noise_4d(const float octaves, const float persistence, const float scale, const float x,
                                   const float y, const float z, const float w) -> float
{
    auto total = 0.0f;
    auto frequency = scale;
    auto amplitude = 1.0f;

    // We have to keep track of the largest possible amplitude,
    // because each octave adds more, and we need a value in [-1, 1].
    float maxAmplitude = 0.0f;

    for (auto i = 0; i < octaves; ++i)
    {
        total += raw_noise_4d(x * frequency, y * frequency, z * frequency, w * frequency) * amplitude;

        frequency *= 2.0f;
        maxAmplitude += amplitude;
        amplitude *= persistence;
    }

    return total / maxAmplitude;
}

// 2D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_octave_noise_2d(const float octaves, const float persistence, const float scale,
                                          const float loBound, const float hiBound, const float x, const float y)
    -> float
{
    return octave_noise_2d(octaves, persistence, scale, x, y) * (hiBound - loBound) / 2.0f + (hiBound + loBound) / 2.0f;
}

// 3D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_octave_noise_3d(const float octaves, const float persistence, const float scale,
                                          const float loBound, const float hiBound, const float x, const float y,
                                          const float z) -> float
{
    return octave_noise_3d(octaves, persistence, scale, x, y, z) * (hiBound - loBound) / 2.0f +
           (hiBound + loBound) / 2.0f;
}

// 4D Scaled Multi-octave Simplex noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_octave_noise_4d(const float octaves, const float persistence, const float scale,
                                          const float loBound, const float hiBound, const float x, const float y,
                                          const float z, const float w) -> float
{
    return octave_noise_4d(octaves, persistence, scale, x, y, z, w) * (hiBound - loBound) / 2.0f +
           (hiBound + loBound) / 2.0f;
}

template <typename T>
struct convert_noise_scale
{
    [[nodiscard]] static auto convert(const float value) -> T
    {
        return static_cast<T>(value * static_cast<float>(std::numeric_limits<T>::max()));
    }
};

template <>
struct convert_noise_scale<float>
{
    [[nodiscard]] static auto convert(const float value) -> float
    {
        return value;
    }
};

template <>
struct convert_noise_scale<double>
{
    [[nodiscard]] static auto convert(const float value) -> double
    {
        return static_cast<double>(value);
    }
};

template <typename T>
void scaled_octave_noise_impl(mat_view &matrix, const float octaves, const float persistence, const float scale)
{
    const auto width = math::width(matrix);
    const auto height = math::height(matrix);
    const auto stride = math::stride(matrix);
    const auto element_type = math::element_type(matrix);

    auto *const data = std::data(matrix);

    for (auto y = 0; y < height; ++y)
    {
        for (auto x = 0; x < width; ++x)
        {
            auto *pixel_data = reinterpret_cast<T *>(data + common::offset_of(element_type, stride, x, y));
            *pixel_data = convert_noise_scale<T>::convert(scaled_octave_noise_2d(
                octaves, persistence, scale, 0.0f, 1.0f, static_cast<float>(x), static_cast<float>(y)));
        }
    }
}

void scaled_octave_noise(mat_view &matrix, const float octaves, const float persistence, const float scale)
{
    switch (math::element_type(matrix).name)
    {
        case common::element_type_name::u8:
            scaled_octave_noise_impl<std::uint8_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::s8:
            scaled_octave_noise_impl<std::int8_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::u16:
            scaled_octave_noise_impl<std::uint16_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::s16:
            scaled_octave_noise_impl<std::int16_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::u32:
            scaled_octave_noise_impl<std::uint32_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::s32:
            scaled_octave_noise_impl<std::int32_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::u64:
            scaled_octave_noise_impl<std::uint64_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::s64:
            scaled_octave_noise_impl<std::int64_t>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::f32:
            scaled_octave_noise_impl<float>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::f64:
            scaled_octave_noise_impl<double>(matrix, octaves, persistence, scale);
            break;
        case common::element_type_name::undefined:
        default:
            throw std::runtime_error{"Given matrix is unsupported."};
    }
}

// 2D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_raw_noise_2d(const float loBound, const float hiBound, const float x, const float y) -> float
{
    return raw_noise_2d(x, y) * (hiBound - loBound) / 2.0f + (hiBound + loBound) / 2.0f;
}

// 3D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_raw_noise_3d(const float loBound, const float hiBound, const float x, const float y,
                                       const float z) -> float
{
    return raw_noise_3d(x, y, z) * (hiBound - loBound) / 2.0f + (hiBound + loBound) / 2.0f;
}

// 4D Scaled Simplex raw noise.
//
// Returned value will be between loBound and hiBound.
[[nodiscard]] auto scaled_raw_noise_4d(const float loBound, const float hiBound, const float x, const float y,
                                       const float z, const float w) -> float
{
    return raw_noise_4d(x, y, z, w) * (hiBound - loBound) / 2.0f + (hiBound + loBound) / 2.0f;
}

// 2D raw Simplex noise
[[nodiscard]] auto raw_noise_2d(const float x, const float y) -> float
{
    // Noise contributions from the three corners
    auto n0 = 0.0f;
    auto n1 = 0.0f;
    auto n2 = 0.0f;

    // Skew the input space to determine which simplex cell we're in
    const auto F2 = 0.5f * (std::sqrt(3.0f) - 1.0f);

    // Hairy factor for 2D
    const auto s = (x + y) * F2;
    const auto i = fastfloor(x + s);
    const auto j = fastfloor(y + s);

    const auto G2 = (3.0f - std::sqrt(3.0f)) / 6.0f;
    const auto t = (i + j) * G2;

    // Unskew the cell origin back to (x,y) space
    const auto X0 = i - t;
    const auto Y0 = j - t;

    // The x,y distances from the cell origin
    const auto x0 = x - X0;
    const auto y0 = y - Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    auto i1 = 0;
    auto j1 = 0; // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0)
    {
        i1 = 1;
        j1 = 0; // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    }
    else
    {
        i1 = 0;
        j1 = 1; // upper triangle, YX order: (0,0)->(0,1)->(1,1)
    }

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6
    const auto x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
    const auto y1 = y0 - j1 + G2;
    const auto x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
    const auto y2 = y0 - 1.0f + 2.0f * G2;

    // Work out the hashed gradient indices of the three simplex corners
    const auto ii = i & 255;
    const auto jj = j & 255;
    const auto gi0 = perm[ii + perm[jj]] % 12;
    const auto gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
    const auto gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

    // Calculate the contribution from the three corners
    auto t0 = 0.5f - x0 * x0 - y0 * y0;

    if (t0 < 0.0f)
    {
        n0 = 0.0f;
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
    }

    auto t1 = 0.5f - x1 * x1 - y1 * y1;
    if (t1 < 0.0f)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
    }

    auto t2 = 0.5f - x2 * x2 - y2 * y2;
    if (t2 < 0.0f)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0f * (n0 + n1 + n2);
}

// 3D raw Simplex noise
[[nodiscard]] auto raw_noise_3d(const float x, const float y, const float z) -> float
{
    // Noise contributions from the four corners
    auto n0 = 0.0f;
    auto n1 = 0.0f;
    auto n2 = 0.0f;
    auto n3 = 0.0f;

    // Skew the input space to determine which simplex cell we're in
    const auto F3 = 1.0f / 3.0f;
    const auto s = (x + y + z) * F3; // Very nice and simple skew factor for 3D
    const auto i = fastfloor(x + s);
    const auto j = fastfloor(y + s);
    const auto k = fastfloor(z + s);

    const auto G3 = 1.0f / 6.0f; // Very nice and simple unskew factor, too
    const auto t = (i + j + k) * G3;
    const auto X0 = i - t; // Unskew the cell origin back to (x,y,z) space
    const auto Y0 = j - t;
    const auto Z0 = k - t;
    const auto x0 = x - X0; // The x,y,z distances from the cell origin
    const auto y0 = y - Y0;
    const auto z0 = z - Z0;

    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    auto i1 = 0;
    auto j1 = 0;
    auto k1 = 0;

    // Offsets for third corner of simplex in (i,j,k) coords
    auto i2 = 0;
    auto j2 = 0;
    auto k2 = 0;

    if (x0 >= y0)
    {
        if (y0 >= z0)
        {
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        } // X Y Z order
        else if (x0 >= z0)
        {
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        } // X Z Y order
        else
        {
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        } // Z X Y order
    }
    else
    { // x0<y0
        if (y0 < z0)
        {
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        } // Z Y X order
        else if (x0 < z0)
        {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        } // Y Z X order
        else
        {
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        } // Y X Z order
    }

    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
    // c = 1/6.
    const auto x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
    const auto y1 = y0 - j1 + G3;
    const auto z1 = z0 - k1 + G3;
    const auto x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
    const auto y2 = y0 - j2 + 2.0f * G3;
    const auto z2 = z0 - k2 + 2.0f * G3;
    const auto x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
    const auto y3 = y0 - 1.0f + 3.0f * G3;
    const auto z3 = z0 - 1.0f + 3.0f * G3;

    // Work out the hashed gradient indices of the four simplex corners
    const auto ii = i & 255;
    const auto jj = j & 255;
    const auto kk = k & 255;
    const auto gi0 = perm[ii + perm[jj + perm[kk]]] % 12;
    const auto gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]] % 12;
    const auto gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]] % 12;
    const auto gi3 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]] % 12;

    // Calculate the contribution from the four corners
    auto t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
    if (t0 < 0.0f)
    {
        n0 = 0.0f;
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
    }

    auto t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
    if (t1 < 0.0f)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
    }

    auto t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
    if (t2 < 0.0f)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
    }

    auto t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
    if (t3 < 0.0f)
    {
        n3 = 0.0f;
    }
    else
    {
        t3 *= t3;
        n3 = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32.0f * (n0 + n1 + n2 + n3);
}

// 4D raw Simplex noise
[[nodiscard]] auto raw_noise_4d(const float x, const float y, const float z, const float w) -> float
{
    // The skewing and unskewing factors are hairy again for the 4D case
    const auto F4 = (std::sqrt(5.0f) - 1.0f) / 4.0f;
    const auto G4 = (5.0f - std::sqrt(5.0f)) / 20.0f;

    // Noise contributions from the five corners
    auto n0 = 0.0f;
    auto n1 = 0.0f;
    auto n2 = 0.0f;
    auto n3 = 0.0f;
    auto n4 = 0.0f;

    // Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in
    const auto s = (x + y + z + w) * F4; // Factor for 4D skewing
    const auto i = fastfloor(x + s);
    const auto j = fastfloor(y + s);
    const auto k = fastfloor(z + s);
    const auto l = fastfloor(w + s);
    const auto t = (i + j + k + l) * G4; // Factor for 4D unskewing
    const auto X0 = i - t;               // Unskew the cell origin back to (x,y,z,w) space
    const auto Y0 = j - t;
    const auto Z0 = k - t;
    const auto W0 = l - t;

    const auto x0 = x - X0; // The x,y,z,w distances from the cell origin
    const auto y0 = y - Y0;
    const auto z0 = z - Z0;
    const auto w0 = w - W0;

    // For the 4D case, the simplex is a 4D shape I won't even try to describe.
    // To find out which of the 24 possible simplices we're in, we need to
    // determine the magnitude ordering of x0, y0, z0 and w0.
    // The method below is a good way of finding the ordering of x,y,z,w and
    // then find the correct traversal order for the simplex we're in.
    // First, six pair-wise comparisons are performed between each possible pair
    // of the four coordinates, and the results are used to add up binary bits
    // for an integer index.
    const auto c1 = (x0 > y0) ? 32 : 0;
    const auto c2 = (x0 > z0) ? 16 : 0;
    const auto c3 = (y0 > z0) ? 8 : 0;
    const auto c4 = (x0 > w0) ? 4 : 0;
    const auto c5 = (y0 > w0) ? 2 : 0;
    const auto c6 = (z0 > w0) ? 1 : 0;
    const auto c = c1 + c2 + c3 + c4 + c5 + c6;

    // The integer offsets for the second simplex corner
    auto i1 = 0;
    auto j1 = 0;
    auto k1 = 0;
    auto l1 = 0;

    // The integer offsets for the third simplex corner
    auto i2 = 0;
    auto j2 = 0;
    auto k2 = 0;
    auto l2 = 0;

    // The integer offsets for the fourth simplex corner
    auto i3 = 0;
    auto j3 = 0;
    auto k3 = 0;
    auto l3 = 0;

    // simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
    // Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
    // impossible. Only the 24 indices which have non-zero entries make any sense.
    // We use a thresholding to set the coordinates in turn from the largest magnitude.

    // The number 3 in the "simplex" array is at the position of the largest coordinate.
    i1 = simplex[c][0] >= 3 ? 1 : 0;
    j1 = simplex[c][1] >= 3 ? 1 : 0;
    k1 = simplex[c][2] >= 3 ? 1 : 0;
    l1 = simplex[c][3] >= 3 ? 1 : 0;

    // The number 2 in the "simplex" array is at the second largest coordinate.
    i2 = simplex[c][0] >= 2 ? 1 : 0;
    j2 = simplex[c][1] >= 2 ? 1 : 0;
    k2 = simplex[c][2] >= 2 ? 1 : 0;
    l2 = simplex[c][3] >= 2 ? 1 : 0;

    // The number 1 in the "simplex" array is at the second smallest coordinate.
    i3 = simplex[c][0] >= 1 ? 1 : 0;
    j3 = simplex[c][1] >= 1 ? 1 : 0;
    k3 = simplex[c][2] >= 1 ? 1 : 0;
    l3 = simplex[c][3] >= 1 ? 1 : 0;

    // The fifth corner has all coordinate offsets = 1, so no need to look that up.
    const auto x1 = x0 - i1 + G4; // Offsets for second corner in (x,y,z,w) coords
    const auto y1 = y0 - j1 + G4;
    const auto z1 = z0 - k1 + G4;
    const auto w1 = w0 - l1 + G4;
    const auto x2 = x0 - i2 + 2.0f * G4; // Offsets for third corner in (x,y,z,w) coords
    const auto y2 = y0 - j2 + 2.0f * G4;
    const auto z2 = z0 - k2 + 2.0f * G4;
    const auto w2 = w0 - l2 + 2.0f * G4;
    const auto x3 = x0 - i3 + 3.0f * G4; // Offsets for fourth corner in (x,y,z,w) coords
    const auto y3 = y0 - j3 + 3.0f * G4;
    const auto z3 = z0 - k3 + 3.0f * G4;
    const auto w3 = w0 - l3 + 3.0f * G4;
    const auto x4 = x0 - 1.0f + 4.0f * G4; // Offsets for last corner in (x,y,z,w) coords
    const auto y4 = y0 - 1.0f + 4.0f * G4;
    const auto z4 = z0 - 1.0f + 4.0f * G4;
    const auto w4 = w0 - 1.0f + 4.0f * G4;

    // Work out the hashed gradient indices of the five simplex corners
    const auto ii = i & 255;
    const auto jj = j & 255;
    const auto kk = k & 255;
    const auto ll = l & 255;
    const auto gi0 = perm[ii + perm[jj + perm[kk + perm[ll]]]] % 32;
    const auto gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1 + perm[ll + l1]]]] % 32;
    const auto gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2 + perm[ll + l2]]]] % 32;
    const auto gi3 = perm[ii + i3 + perm[jj + j3 + perm[kk + k3 + perm[ll + l3]]]] % 32;
    const auto gi4 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1 + perm[ll + 1]]]] % 32;

    // Calculate the contribution from the five corners
    auto t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
    if (t0 < 0.0f)
    {
        n0 = 0.0;
    }
    else
    {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad4[gi0], x0, y0, z0, w0);
    }

    auto t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
    if (t1 < 0.0f)
    {
        n1 = 0.0f;
    }
    else
    {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad4[gi1], x1, y1, z1, w1);
    }

    auto t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
    if (t2 < 0.0f)
    {
        n2 = 0.0f;
    }
    else
    {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad4[gi2], x2, y2, z2, w2);
    }

    auto t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
    if (t3 < 0.0f)
    {
        n3 = 0.0f;
    }
    else
    {
        t3 *= t3;
        n3 = t3 * t3 * dot(grad4[gi3], x3, y3, z3, w3);
    }

    auto t4 = 0.6f - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
    if (t4 < 0)
    {
        n4 = 0.0f;
    }
    else
    {
        t4 *= t4;
        n4 = t4 * t4 * dot(grad4[gi4], x4, y4, z4, w4);
    }

    // Sum up and scale the result to cover the range [-1,1]
    return 27.0f * (n0 + n1 + n2 + n3 + n4);
}

[[nodiscard]] auto fastfloor(const float x) -> int
{
    return x > 0 ? static_cast<int>(x) : static_cast<int>(x) - 1;
}

[[nodiscard]] auto dot(const int *g, const float x, const float y) -> float
{
    return g[0] * x + g[1] * y;
}

[[nodiscard]] auto dot(const int *g, const float x, const float y, const float z) -> float
{
    return g[0] * x + g[1] * y + g[2] * z;
}

[[nodiscard]] auto dot(const int *g, const float x, const float y, const float z, const float w) -> float
{
    return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}

} // namespace aeon::math::simplex_noise
