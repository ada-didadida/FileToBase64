#pragma once
#include <string>

#define BASE64_PAD '='
typedef unsigned char* STREAM_BUFFER;

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
	static void FileToStream(const std::string& file_name, STREAM_BUFFER output_buffer, size_t file_size);

	/*
	 * 将二进制流写入文件
	 */
	static void StreamToFile(STREAM_BUFFER buffer, const std::string& output_file_name, size_t buffer_size);

	/*
	 * 将二进制流转成Base64编码
	 * output_size：转换后二进制流的大小
	 * output_base64：转换后二进制流
	 */
	static void StreamToBase64(const STREAM_BUFFER buffer, size_t buffer_size, STREAM_BUFFER output_base64, size_t& output_size);

	/*
	 * 将Base64编码转换为二进制流
	 * output_buffer：转换后的二进制流
	 * output_size：转换后的二进制流大小
	 */
	static void Base64ToStream(const STREAM_BUFFER base64, size_t base64_size, STREAM_BUFFER output_buffer, size_t& output_size);

	static void FileToBase64(std::string& file_name, STREAM_BUFFER output_base64);

	static void Base64ToFile(STREAM_BUFFER base64, std::string& output_file_name);
};

