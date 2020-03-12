#include <iostream>
#include <cstdlib>

#define CRC32_MAGIC 0x04C11DB7
#define CRC32_MAGIC_REV 0xEDB88320

uint32_t crc32_table[256];

void make_crc32_table(void)
{
	for (size_t i = 0; i < 256; i++)
	{
		uint32_t c = i;
		for (size_t j = 0; j < 8; j++)
		{
			c = (c & 0x01) ? (CRC32_MAGIC_REV ^ (c >> 1)) : (c >> 1);
		}

		crc32_table[i] = c;
	}
}

uint32_t get_crc32(uint8_t * data, size_t length)
{
	uint32_t c = 0xFFFFFFFF;
	for (size_t i = 0; i < length; i++)
	{
		c = crc32_table[(c ^ data[i]) & 0xFF] ^ (c >> 8);
	}

	return c ^ 0xFFFFFFFF;
}

int main()
{
	make_crc32_table();
    std::cout << "CRC32 Calculation\n";
    std::cout << std::hex << get_crc32(new uint8_t[4]{ 0x01,0x02,0x03,0x04 }, 4) << std::endl;
}


