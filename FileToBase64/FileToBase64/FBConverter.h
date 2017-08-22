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
	static void FileToStream(const std::string& file_name, STREAM_BUFFER output_buffer, size_t file_size);

	/*
	 * ����������д���ļ�
	 */
	static void StreamToFile(STREAM_BUFFER buffer, const std::string& output_file_name, size_t buffer_size);

	/*
	 * ����������ת��Base64����
	 * output_size��ת������������Ĵ�С
	 * output_base64��ת�����������
	 */
	static void StreamToBase64(const STREAM_BUFFER buffer, size_t buffer_size, STREAM_BUFFER output_base64, size_t& output_size);

	/*
	 * ��Base64����ת��Ϊ��������
	 * output_buffer��ת����Ķ�������
	 * output_size��ת����Ķ���������С
	 */
	static void Base64ToStream(const STREAM_BUFFER base64, size_t base64_size, STREAM_BUFFER output_buffer, size_t& output_size);

	static void FileToBase64(std::string& file_name, STREAM_BUFFER output_base64);

	static void Base64ToFile(STREAM_BUFFER base64, std::string& output_file_name);
};

