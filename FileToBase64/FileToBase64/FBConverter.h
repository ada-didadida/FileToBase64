#pragma once
#include <string>

#define BASE64_PAD '='
typedef unsigned char* STREAM_BUFFER;

const char base64_encode_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
};

const short base64_decode_table[] = {
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

class FBConverter
{
public:
	FBConverter();
	~FBConverter();

	/*
	 * 判断文件是否存在
	 * file_name：文件路径
	 */
	static bool IsFileExist(const std::string& file_name);

	/*
	 * 获取文件大小
	 * file_name：文件路径
	 */
	static size_t GetFileSize(const std::string& file_name);

	/*
	 * 将文件转换为二进制流
	 * file_name：文件路径
	 * output_buffer:二进制流写入该变量
	 * file_size：文件大小
	 */
	static size_t FileToStream(const std::string& file_name, STREAM_BUFFER output_buffer, size_t file_size);

	/*
	 * 将二进制流写入文件
	 */
	static void StreamToFile(STREAM_BUFFER buffer, const std::string& output_file_name, size_t buffer_size);

	/*
	 * 将二进制流转成Base64编码
	 * output_size：转换后二进制流的大小
	 * output_base64：转换后二进制流
	 */
	static STREAM_BUFFER StreamToBase64(const STREAM_BUFFER buffer, size_t buffer_size, size_t& output_size);

	/*
	 * 将Base64编码转换为二进制流
	 * output_buffer：转换后的二进制流
	 * output_size：转换后的二进制流大小
	 */
	static STREAM_BUFFER Base64ToStream(const STREAM_BUFFER base64, size_t base64_size, size_t& output_size);

	static void FileToBase64(std::string& file_name, STREAM_BUFFER output_base64);

	static void Base64ToFile(STREAM_BUFFER base64, std::string& output_file_name);
};

