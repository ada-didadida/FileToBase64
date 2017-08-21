// FileToBase64.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

size_t FileToStream(const char* file_name, unsigned char* buffer, size_t size)
{
	FILE* file;
	if (fopen_s(&file, file_name, "rb") != 0)
	{
		std::cout << "cannot open file" << std::endl;
		return 0;
	}

	memset(buffer, 0, size);
	auto read_size = fread(buffer, sizeof(char), size, file);
	fclose(file);

	return read_size;
}

size_t GetFileSize(const char* file_name)
{
	FILE* file;
	if (fopen_s(&file, file_name, "rb") != 0)
	{
		std::cout << "cannot open file" << std::endl;
		return 0;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fclose(file);

	return file_size;
}

void StreamToFile(unsigned char* buffer, const char* new_file_name, size_t size)
{
	FILE* file;
	if (fopen_s(&file, new_file_name, "wb+") != 0)
	{
		std::cout << "cannot open file" << std::endl;
		return;
	}

	fwrite(buffer, 1, size, file);
	fclose(file);
}

#include <cctype>

class Base64 {
private:
	static const char base64_pad = '=';

public:
	unsigned char * Encode(const unsigned char *str, int length, int &ret_length);
	unsigned char * Decode(const unsigned char *str, int length, int &ret_length);
};

unsigned char * Base64::Encode(const unsigned char *str, int length, int &ret_length) /* {{{ */
{
	/* {{{ base64 tables */
	const char base64_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
	};
	const unsigned char *current = str;
	unsigned char *p;
	unsigned char * result = new unsigned char[(length + 2) / 3 * 4];
	p = result;

	if (length < 0) {
		ret_length = 0;
		return NULL;
	}

	while (length > 2) { /* keep going until we have less than 24 bits */
		*p++ = base64_table[current[0] >> 2];
		*p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
		*p++ = base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
		*p++ = base64_table[current[2] & 0x3f];

		current += 3;
		length -= 3; /* we just handle 3 octets of data */
	}

	/* now deal with the tail end of things */
	if (length != 0) {
		*p++ = base64_table[current[0] >> 2];
		if (length > 1) {
			*p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			*p++ = base64_table[(current[1] & 0x0f) << 2];
			*p++ = base64_pad;
		}
		else {
			*p++ = base64_table[(current[0] & 0x03) << 4];
			*p++ = base64_pad;
			*p++ = base64_pad;
		}
	}
	ret_length = (int)(p - result);
	*p = '\0';
	return result;
}

unsigned char * Base64::Decode(const unsigned char *str, int length, int &ret_length) /* {{{ */
{
	const short base64_reverse_table[256] = {
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
		-2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
		-2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
	};
	const unsigned char *current = str;
	int ch, i = 0, j = 0, k;
	/* this sucks for threaded environments */

	unsigned char * result;

	result = new unsigned char[length];

	/* run through the whole string, converting as we go */
	while ((ch = *current++) != '\0' && length-- > 0) {
		if (ch == base64_pad) {
			if (*current != '=' && (i % 4) == 1) {
				return NULL;
			}
			continue;
		}
		ch = base64_reverse_table[ch];
		if (ch < 0 || ch == -1) { /* a space or some other separator character, we simply skip over */
			continue;
		}
		else if (ch == -2) {
			return NULL;
		}

		switch (i % 4) {
		case 0:
			result[j] = ch << 2;
			break;
		case 1:
			result[j++] |= ch >> 4;
			result[j] = (ch & 0x0f) << 4;
			break;
		case 2:
			result[j++] |= ch >> 2;
			result[j] = (ch & 0x03) << 6;
			break;
		case 3:
			result[j++] |= ch;
			break;
		}
		i++;
	}

	k = j;
	/* mop things up if we ended on a boundary */
	if (ch == base64_pad) {
		switch (i % 4) {
		case 1:
			return NULL;
		case 2:
			k++;
		case 3:
			result[k] = 0;
		}
	}
	if (ret_length) {
		ret_length = j;
	}
	result[j] = '\0';
	return result;
}


int main()
{
	const char* file = "E:\\GitHub\\ARTableEditor\\res\\XBuilderRes\\banner.png";
	size_t file_size = GetFileSize(file/*"ReadMe.txt"*/);

	unsigned char* buffer = new unsigned char[file_size];

	size_t read_size = FileToStream(/*"ReadMe.txt"*/file, buffer, file_size);

	std::cout << file_size << std::endl;

	std::cout << read_size << std::endl;


	/*for (auto i = 0; i < read_size; ++i)
	{
		std::cout << buffer[i] << std::endl;
	}*/

	char* new_file_name = "C:\\new_banner.png";//"C:\\new_read_me.txt";

	StreamToFile(buffer, new_file_name, read_size);

	Base64* base64 = new Base64();

	int length = 0;

	auto encode_file = base64->Encode(buffer, read_size, length);

	new_file_name = "C:\\base64_test.png";

	int decode_length = 0;

	StreamToFile(base64->Decode(encode_file, length, decode_length), new_file_name, read_size);

	std::cout << decode_length << std::endl;


	system("PAUSE");
    return 0;
}

