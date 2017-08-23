#include "StdAfx.h"
#include "FBConverter.h"


FBConverter::FBConverter()
{
}


FBConverter::~FBConverter()
{
}

bool FBConverter::IsFileExist(const std::string& file_name)
{
	FILE* file;
	if (fopen_s(&file, file_name.c_str(), "rb") != 0)
	{
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}

size_t FBConverter::GetFileSize(const std::string& file_name)
{
	FILE* file;
	if (fopen_s(&file, file_name.c_str(), "rb") != 0)
	{
		return 0;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fclose(file);

	return file_size;
}

size_t FBConverter::FileToStream(const std::string& file_name, STREAM_BUFFER output_buffer, size_t file_size)
{
	FILE* file;
	if (fopen_s(&file, file_name.c_str(), "rb") != 0)
	{
		return 0;
	}

	memset(output_buffer, 0, file_size);
	auto read_size = fread(output_buffer, sizeof(char), file_size, file);
	fclose(file);
	return read_size;
}

void FBConverter::StreamToFile(STREAM_BUFFER buffer, const std::string& output_file_name, size_t buffer_size)
{
	FILE* file;
	if (fopen_s(&file, output_file_name.c_str(), "wb+") != 0)
	{
		return;
	}

	fwrite(buffer, 1, buffer_size, file);
	fclose(file);
}

STREAM_BUFFER FBConverter::StreamToBase64(const STREAM_BUFFER buffer, size_t buffer_size, size_t& output_size)
{
	const unsigned char* current = buffer;
	STREAM_BUFFER result = new unsigned char[(buffer_size + 2) / 3 * 4];
	STREAM_BUFFER p = result;

	if (buffer_size < 0) {
		output_size = 0;
		return nullptr;
	}

	while (buffer_size > 2) { /* keep going until we have less than 24 bits */
		*p++ = base64_encode_table[current[0] >> 2];
		*p++ = base64_encode_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
		*p++ = base64_encode_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
		*p++ = base64_encode_table[current[2] & 0x3f];

		current += 3;
		buffer_size -= 3; /* we just handle 3 octets of data */
	}

	/* now deal with the tail end of things */
	if (buffer_size != 0) {
		*p++ = base64_encode_table[current[0] >> 2];
		if (buffer_size > 1) {
			*p++ = base64_encode_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			*p++ = base64_encode_table[(current[1] & 0x0f) << 2];
			*p++ = BASE64_PAD;
		}
		else {
			*p++ = base64_encode_table[(current[0] & 0x03) << 4];
			*p++ = BASE64_PAD;
			*p++ = BASE64_PAD;
		}
	}
	output_size = static_cast<size_t>(p - result);
	*p = '\0';
	return result;
}

STREAM_BUFFER FBConverter::Base64ToStream(const STREAM_BUFFER base64, size_t base64_size, size_t& output_size)
{
	const unsigned char* current = base64;
	int ch, i = 0, j = 0;

	STREAM_BUFFER result = new unsigned char[base64_size];

	/* run through the whole string, converting as we go */
	while ((ch = *current++) != '\0' && base64_size-- > 0) {
		if (ch == BASE64_PAD) {
			if (*current != '=' && (i % 4) == 1) {
				return nullptr;
			}
			continue;
		}
		ch = base64_decode_table[ch];
		if (ch < 0 || ch == -1) { /* a space or some other separator character, we simply skip over */
			continue;
		}
		if (ch == -2) {
			return nullptr;
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
		default: 
			break;
		}
		i++;
	}

	int k = j;
	/* mop things up if we ended on a boundary */
	if (ch == BASE64_PAD) {
		switch (i % 4) {
		case 1:
			return nullptr;
		case 2:
			k++;
		case 3:
			result[k] = 0;
		default: 
			break;
		}
	}
	
	output_size = j;

	result[j] = '\0';
	return result;
}

void FBConverter::FileToBase64(std::string& file_name, STREAM_BUFFER output_base64)
{
	size_t file_size = GetFileSize(file_name);
	STREAM_BUFFER output_buffer = new unsigned char[file_size];
	size_t read_size = FileToStream(file_name, output_buffer, file_size);

	if(read_size)
	{
		size_t base64_size;
		output_base64 = StreamToBase64(output_buffer, read_size, base64_size);
	}
}

void FBConverter::Base64ToFile(STREAM_BUFFER base64, std::string& output_file_name)
{
}
