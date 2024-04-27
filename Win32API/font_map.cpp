#pragma once

#include <fstream>

namespace FontMap {

	typedef unsigned char uchar;
	typedef unsigned long ulong;

	class Font {

		uchar* character_sheet;
		ulong sheet_length_in_bytes;

	public:

		uchar height, width;
		ulong sheet_length;

		Font() :character_sheet(nullptr), sheet_length_in_bytes(0),
			height(0), width(0), sheet_length(0) {}
		
		~Font() { if (character_sheet) delete[] character_sheet; }

		Font(const Font&) = delete;
		Font operator=(const Font&) = delete;

	public:

		const uchar* getCharacterSheet(char character) const {
			if (0x20 <= character && character <= 0x7e)
				return character_sheet + sheet_length_in_bytes * (character - 0x20);
			return character_sheet;
		}

		inline bool isLoaded() const {
			return (bool)character_sheet;
		}

		bool ftmpAssembler(const char* font_file_path) {

			if (character_sheet) delete[] character_sheet;

			std::ifstream file(font_file_path, std::ios::in | std::ios::binary);
			if (!file) {
				file.open("assets/default.ftmp", std::ios::in | std::ios::binary);
				if (!file) return false;
			}

			file.seekg(-6, file.end);
			ulong sizeof_file = (ulong)file.tellg();

			{
				file.seekg(0, file.beg);
				uchar fontmap_info[6] = {};

				file.read((char*)fontmap_info, 6);

				const uchar extension[] = "FTMP";
				for (uchar i = 0; i < sizeof extension - 1; i++) {
					if (extension[i] != fontmap_info[i]) return false;
				}

				height = fontmap_info[4];
				width = fontmap_info[5];
			}

			uchar* file_data = new uchar[sizeof_file];
			file.read((char*)file_data, sizeof_file);
	
			sheet_length = (ulong)height * width;
			sheet_length_in_bytes = ((sheet_length - 1) >> 3) + 1;

			ulong sizeof_full_char_sheet = sheet_length_in_bytes * 95;
			character_sheet = new uchar[sizeof_full_char_sheet];

			uchar* sheet_cursor = character_sheet;
			for (ulong i = 0; i < sizeof_full_char_sheet; i++) *sheet_cursor++ = 0;

			char byte_cursor = 7;
			uchar* file_cursor = file_data;
			sheet_cursor = character_sheet;

			for (ulong i = 0; i < 95; i++) {

				for (ulong j = 0; j < sheet_length; j++) {
					if (byte_cursor == -1) { file_cursor++; byte_cursor = 7; }

					sheet_cursor[j >> 3] |= (((*file_cursor >> byte_cursor)) & 1) << (~j & 0b111);
					byte_cursor--;
				}

				sheet_cursor += sheet_length_in_bytes;
			}

			delete[] file_data;
         file.close();
			return true;
		}
	};
}