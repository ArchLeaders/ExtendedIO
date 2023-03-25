/**
 * Copyright (C) 2020 leoetlino
 *
 * This file is part of oead.
 *
 * oead is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * oead is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with oead.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <array>
#include <cstdint>
#include <tuple>

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using size_t = std::size_t;

using f32 = float;
using f64 = double;

namespace exio {
#define EXIO_DEFINE_FIELDS(TYPE, ...)                                                              \
  constexpr auto fields() {                                                                        \
    return std::tie(__VA_ARGS__);                                                                  \
  }                                                                                                \
  constexpr auto fields() const {                                                                  \
    return std::tie(__VA_ARGS__);                                                                  \
  }                                                                                                \
  constexpr friend bool operator==(const TYPE& lhs, const TYPE& rhs) {                             \
    return lhs.fields() == rhs.fields();                                                           \
  }                                                                                                \
  constexpr friend bool operator!=(const TYPE& lhs, const TYPE& rhs) {                             \
    return !(lhs == rhs);                                                                          \
  }                                                                                                \
  template <typename H>                                                                            \
  friend H AbslHashValue(H h, const TYPE& self) {                                                  \
    return H::combine(std::move(h), self.fields());                                                \
  }

enum class Endianness {
  Big,
  Little,
};

/// Unsigned 24-bit integer.
template <bool BigEndian>
struct U24 {
  constexpr U24() = default;
  constexpr U24(u32 v) { Set(v); }
  constexpr operator u32() const { return Get(); }
  constexpr U24& operator=(u32 v) { return Set(v), *this; }

private:
  constexpr u32 Get() const {
    if constexpr (BigEndian)
      return data[0] << 16 | data[1] << 8 | data[2];
    else
      return data[2] << 16 | data[1] << 8 | data[0];
  }

  constexpr void Set(u32 v) {
    if constexpr (BigEndian) {
      data[0] = (v >> 16) & 0xFF;
      data[1] = (v >> 8) & 0xFF;
      data[2] = v & 0xFF;
    } else {
      data[2] = (v >> 16) & 0xFF;
      data[1] = (v >> 8) & 0xFF;
      data[0] = v & 0xFF;
    }
  }

  std::array<u8, 3> data;
};
static_assert(sizeof(U24<false>) == 3);

}  // namespace exio