#include <array>
#include <fstream>
#include <iostream>

#include <exio/binary_reader.h>
#include <exio/binary_writer.h>
#include <exio/error.h>
#include <exio/types.h>
#include <exio/util/magic_utils.h>
#include <nonstd/span.h>

constexpr auto BarsMagic = exio::util::MakeMagic("BARS");

struct BarsHeader {
  std::array<char, 4> magic;
  u32 file_size;
  u16 bom;
  u16 version;
  u32 asset_count;
  EXIO_DEFINE_FIELDS(BarsHeader, magic, file_size, bom, version, asset_count);
};

int main(int argc, char** argv) {
  // Parse the first argument as a file
  std::vector<u8> file;
  std::ifstream stream{argv[1], std::ios::binary | std::ios::ate};
  file.resize(stream.tellg());
  stream.seekg(0, std::ios::beg);
  stream.read(reinterpret_cast<char*>(file.data()), file.size());

  // Create a binary reader
  tcb::span<const u8> data{file.data(), file.size()};
  exio::BinaryReader reader{data, exio::Endianness::Big};

  // Set the BOM (without seeking)
  reader = {data, exio::ByteOrderMarkToEndianness(reader.Read<BarsHeader>().value().bom)};

  // Read and verify the header
  const auto header = *reader.Read<BarsHeader>();
  if (header.magic != BarsMagic) {
    throw exio::InvalidDataError("Invalid BARS magic");
  }
  if (header.version != 0x0101) {
    throw exio::InvalidDataError("Unknwon BARS version");
  }

  // Print the asset count
  std::cout << "Asset Count: " << header.asset_count << std::endl;
}