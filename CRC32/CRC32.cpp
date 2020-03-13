#include <iostream>
#include <cstdlib>

#define CRC32_MAGIC 0x04C11DB7
#define CRC32_MAGIC_REV 0xEDB88320

uint32_t crc32_table[256];
uint32_t crc32_table_rev[256];

void make_crc32_table_rev(void)
{
	for (size_t i = 0; i < 256; i++)
	{
		uint32_t c = i;
		for (size_t j = 0; j < 8; j++)
		{
			c = (c & 0x01) ? (CRC32_MAGIC_REV ^ (c >> 1)) : (c >> 1);
		}

		crc32_table_rev[i] = c;
	}
}

void make_crc32_table(void)
{
	for (size_t i = 0; i < 256; i++)
	{
		uint32_t c = i << 24;
		for (size_t j = 0; j < 8; j++)
		{
			c = (c & 0x80000000) ? (CRC32_MAGIC ^ (c << 1)) : (c << 1);
		}

		crc32_table[i] = c;
	}
}

uint32_t get_crc32_rev(uint8_t * data, size_t length)
{
	uint32_t c = 0xFFFFFFFF;
	for (size_t i = 0; i < length; i++)
	{
		c = crc32_table_rev[(c ^ data[i]) & 0xFF] ^ (c >> 8);
	}

	return c ^ 0xFFFFFFFF;
}

uint32_t get_crc32(uint8_t* data, size_t length)
{
	uint32_t c = 0xFFFFFFFF;
	
	for (size_t i = 0; i < length; i++)
	{
		c = crc32_table[((c >> 24) ^ data[i]) & 0xFF] ^ (c << 8);
	}

	return c ^ 0xFFFFFFFF;
}

uint32_t bit_rev(uint32_t data)
{
	uint32_t d = 0x000000000;
	for (size_t i = 0; i < 31; i++)
	{
		d |= (data & 0x80000000);
		d >>= 1;
		data <<= 1;
	}

	d |= (data & 0x80000000);

	return d;
}

int main()
{
	make_crc32_table();
	make_crc32_table_rev();
    std::cout << "CRC32 Calculation\n";
	std::cout << std::hex << bit_rev(get_crc32(new uint8_t[2]{ 0x80, 0x01 }, 2)) << std::endl;
	std::cout << std::hex << get_crc32_rev(new uint8_t[2]{ 0x01, 0x80 }, 2) << std::endl;
}


