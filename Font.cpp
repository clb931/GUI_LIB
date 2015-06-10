#include "Font.h"

int be32_to_le32(int num)
{
	unsigned char
		new_num_0 = (num >>  0) & 0xFF,
		new_num_1 = (num >>  8) & 0xFF,
		new_num_2 = (num >> 16) & 0xFF,
		new_num_3 = (num >> 24) & 0xFF;

	return (
		(new_num_0 << 24) |
		(new_num_1 << 16) |
		(new_num_2 <<  8) |
		(new_num_3 <<  0) );
}

short be16_to_le16(short num)
{
	unsigned char
		new_num_0 = (num >>  0) & 0xFF,
		new_num_1 = (num >>  8) & 0xFF;

	return (
		(new_num_0 << 8) |
		(new_num_1 << 0) );
}

Font::Font()
{

}

Font::Font(const char *file_path)
{
	std::cout << "tFont::Font()";

	FILE *pFile = fopen(file_path, "rb");
	short version_major = 0;
	unsigned short version_minor = 0;
	unsigned short num_tables = 0;
	unsigned short search_range = 0;
	unsigned short entry_sel = 0;
	unsigned short range_shift = 0;

	fread(&version_major, sizeof(short), 1, pFile);
	fread(&version_minor, sizeof(short), 1, pFile);
	fread(&num_tables, sizeof(short), 1, pFile);
	fread(&search_range, sizeof(short), 1, pFile);
	fread(&entry_sel, sizeof(short), 1, pFile);
	fread(&range_shift, sizeof(short), 1, pFile);

	version_major = be16_to_le16(version_major);
	version_minor = be16_to_le16(version_minor);
	num_tables = be16_to_le16(num_tables);
	search_range = be16_to_le16(search_range);
	entry_sel = be16_to_le16(entry_sel);
	range_shift = be16_to_le16(range_shift);

	std::cout << "\n\tVersion: " << std::dec << version_major << "." << version_minor
		<< "\n\tTables: " << num_tables
		<< "\n\tRange: " << search_range
		<< "\n\tSelector: " << entry_sel
		<< "\n\tShift: " << range_shift << std::endl;

	char tag[5] = "";
	unsigned int check_sum = 0;
	unsigned int offset = 0;
	unsigned int length = 0;

	for(int i = 0; i < num_tables; ++i) {
		fread(tag, sizeof(char), 4, pFile);
		fread(&check_sum, sizeof(int), 1, pFile);
		fread(&offset, sizeof(int), 1, pFile);
		fread(&length, sizeof(int), 1, pFile);

		check_sum = be32_to_le32(check_sum);
		offset = be32_to_le32(offset);
		length = be32_to_le32(length);

		std::cout << "\n\tTag: " << tag
			<< "\n\tChecksum: " << check_sum
			<< "\n\tOffset: " << offset
			<< "\n\tLength: " << length
			<< "\n" << std::endl;

		if(strcmp(tag, "glyf") == 0) {

		} else if(strcmp(tag, "cmap") == 0) {

		} else if(strcmp(tag, "htmx") == 0) {

		}
	}

}

Font::~Font()
{

}