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
	 * �ж��ļ��Ƿ����
	 * file_name���ļ�·��
	 */
	static bool IsFileExist(const std::string& file_name);

	/*
	 * ��ȡ�ļ���С
	 * file_name���ļ�·��
	 */
	static size_t GetFileSize(const std::string& file_name);

	/*
	 * ���ļ�ת��Ϊ��������
	 * file_name���ļ�·��
	 * output_buffer:��������д��ñ���
	 * file_size���ļ���С
	 */
	static size_t FileToStream(const std::string& file_name, STREAM_BUFFER output_buffer, size_t file_size);

	/*
	 * ����������д���ļ�
	 */
	static void StreamToFile(STREAM_BUFFER buffer, const std::string& output_file_name, size_t buffer_size);

	/*
	 * ����������ת��Base64����
	 * output_size��ת������������Ĵ�С
	 * output_base64��ת�����������
	 */
	static STREAM_BUFFER StreamToBase64(const STREAM_BUFFER buffer, size_t buffer_size, size_t& output_size);

	/*
	 * ��Base64����ת��Ϊ��������
	 * output_buffer��ת����Ķ�������
	 * output_size��ת����Ķ���������С
	 */
	static STREAM_BUFFER Base64ToStream(const STREAM_BUFFER base64, size_t base64_size, size_t& output_size);

	static void FileToBase64(std::string& file_name, STREAM_BUFFER output_base64);

	static void Base64ToFile(STREAM_BUFFER base64, std::string& output_file_name);
};

