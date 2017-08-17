#pragma once

#include <fstream>
#include <memory>
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "zlib.h"

//GRUMPYZIP 
//----------------------------------------------------------

namespace GrumpyZip
{

	//FILE HEADERS
	//----------------------------------------------------------

	struct HeaderSignature
	{
		unsigned int Signature;
	};

#pragma pack(push, 1)
	struct LocalZipHeader
	{
		unsigned int HeaderSignature; //0x04034b50 litte endian
		unsigned short MadeVersion;
		unsigned short GeneralPurposeBitFlag;
		unsigned short CompressionMethod; // 8 is Deflate (Standard)
		unsigned short FileLastModificationTime;
		unsigned short FileLastModificationDate;
		unsigned int CRC32;
		unsigned int CompressedSize;
		unsigned int UncompressedSize;
		unsigned short FileNameLength;
		unsigned short ExtraFieldLength;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct DataZipHeader
	{
		unsigned int HeaderSignature; //0x08074b50 litte endian
		unsigned int CRC32;
		unsigned int CompressedSize;
		unsigned int UncompressedSize;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct CentralZipHeader
	{
		unsigned int HeaderSignature; //0x02014b50 litte endian

		unsigned short MadeVersion;
		unsigned short VersionNeededToExtract;
		unsigned short GeneralPurposeBitFlag;
		unsigned short CompressionMethod; // 8 is Deflate (Standard)
		unsigned short FileLastModificationTime;
		unsigned short FileLastModificationDate;

		unsigned int CRC32;
		unsigned int CompressedSize;
		unsigned int UncompressedSize;

		unsigned short FileNameLength;
		unsigned short ExtraFieldLength;
		unsigned short FileCommentLength;
		unsigned short DiskNumber;
		unsigned short InternalFileAttributes;

		unsigned int ExternalFileAtrributes;
		unsigned int OffsetOfLocalFileHeader;

	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct EndZipHeader
	{
		unsigned int HeaderSignature; //0x06054b50 litte endian
		unsigned short NumberOfDisk;
		unsigned short DiskWhereCentral;
		unsigned short NumOfCentral;
		unsigned short TotalNumOfCentralRecords;

		unsigned int SizeOfCentral;
		unsigned int StartOfCentralRelToArchive;

		unsigned short CommentLength;
	};
#pragma pack(pop)

	//----------------------------------------------------------
	//FILE HEADERS END

	enum ECompressionMethods
	{
		Deflated = 8
	};
	
	// FILEINZIP 
	//----------------------------------------------------------

	class FileInZip
	{
	public:
		std::vector<unsigned char> Data;
		std::string FileName;
		unsigned int FileSize;

	};

	//----------------------------------------------------------
	// FILEINZIP END

	//MAIN ZIP FILE
	//----------------------------------------------------------

	class ZipFile
	{
	private:
		//Stores the complete zip file in one big buffer
		std::vector<char> m_Bigbuffer;

		std::unordered_map<std::string, std::unique_ptr<FileInZip>> m_FilesInZip;

		//Headers
		LocalZipHeader *m_LocalFileHeader{};
		CentralZipHeader *m_CentralZipHeader{};
		EndZipHeader *m_EndZipHeader{};

		//File informations
		unsigned int m_FileCursorPos = 0;
		unsigned int CompleteFileSize = 0;

		bool LoadLocalFileHeader()
		{
			//Get the header
			m_LocalFileHeader = (LocalZipHeader*)&m_Bigbuffer[m_FileCursorPos];

			if (m_LocalFileHeader->UncompressedSize != 0)
			{
				//Check which method of compressionwas used (we only support 8 which means deflate first)
				if (m_LocalFileHeader->CompressionMethod != 0)
				{
					//Only deflate compression/decompression first
					if (m_LocalFileHeader->CompressionMethod != ECompressionMethods::Deflated)
					{
						printf("Compression method [%i] is not supported\n", m_LocalFileHeader->CompressionMethod);
						return false;
					}
					else
					{
						std::vector<char> tempName;
						tempName.resize(m_LocalFileHeader->FileNameLength + 1);

						//Copy the name..
						memcpy(tempName.data(), &m_Bigbuffer[m_FileCursorPos + 30], m_LocalFileHeader->FileNameLength);

						std::vector<unsigned char> compressedData;
						compressedData.resize(m_LocalFileHeader->CompressedSize);
						memset(compressedData.data(), 0, m_LocalFileHeader->CompressedSize);

						memcpy(compressedData.data(),
							&m_Bigbuffer[m_FileCursorPos + sizeof(LocalZipHeader) + m_LocalFileHeader->ExtraFieldLength + m_LocalFileHeader->FileNameLength],
							m_LocalFileHeader->CompressedSize);

						std::vector<unsigned char> decompressedData;

						decompressedData.resize(m_LocalFileHeader->UncompressedSize + 1);

						z_stream stream;
						stream.zalloc = Z_NULL;
						stream.zfree = Z_NULL;
						stream.opaque = Z_NULL;
						stream.avail_in = 0;
						stream.next_in = Z_NULL;

						if (int err = inflateInit2(&stream, -MAX_WBITS) != Z_OK)
						{
							printf("Error: inflateInit %d\n", err);
							return false;
						}

						// Set the starting point and total data size to be read
						stream.avail_in = (uInt)compressedData.size();
						stream.next_in = (Bytef*)&compressedData[0];

						stream.next_out = (Bytef*)&decompressedData[0];

						int ret = inflate(&stream, Z_NO_FLUSH);

						if (ret != Z_STREAM_END && ret != Z_OK)
						{
							printf("Error: inflate %d\n", ret);
							return false;
						}

						auto tempFile = std::make_unique<FileInZip>();
						tempFile->Data = decompressedData;
						tempFile->FileName = std::string(tempName.data());
						tempFile->FileSize = m_LocalFileHeader->UncompressedSize;

						m_FilesInZip.insert({ std::string(tempName.data()), std::move(tempFile) });
					}
				}
				else
				{
					//No compression was used .. we can just copy the data
					std::vector<char> tempName;
					tempName.resize(m_LocalFileHeader->FileNameLength + 1);

					//Copy the name..
					memcpy(tempName.data(), &m_Bigbuffer[m_FileCursorPos + 30], m_LocalFileHeader->FileNameLength);

					std::vector<unsigned char> data;
					data.resize(m_LocalFileHeader->CompressedSize + 1);
					memset(data.data(), 0, m_LocalFileHeader->CompressedSize);

					memcpy(data.data(),
						&m_Bigbuffer[m_FileCursorPos + sizeof(LocalZipHeader) + m_LocalFileHeader->ExtraFieldLength + m_LocalFileHeader->FileNameLength],
						m_LocalFileHeader->CompressedSize);

					auto tempFile = std::make_unique<FileInZip>();
					tempFile->Data = data;
					tempFile->FileName = std::string(tempName.data());
					tempFile->FileSize = m_LocalFileHeader->UncompressedSize;

					m_FilesInZip.insert({ std::string(tempName.data()), std::move(tempFile) });
				}
			}

			//Moving the file pointer..
			m_FileCursorPos += sizeof(LocalZipHeader) + m_LocalFileHeader->FileNameLength + m_LocalFileHeader->CompressedSize + m_LocalFileHeader->ExtraFieldLength;

			return true;
		}

		bool LoadCentralDirectoryFileHeader()
		{
			m_CentralZipHeader = (CentralZipHeader*)&m_Bigbuffer[m_FileCursorPos];

			std::vector<char> tempName;
			tempName.resize(m_CentralZipHeader->FileNameLength);
			//Copy the name..
			memcpy(tempName.data(), &m_Bigbuffer[m_FileCursorPos + 46], m_CentralZipHeader->FileNameLength);

			//printf("%s\n", tempName.data());

			//Moving the file pointer..
			m_FileCursorPos += sizeof(CentralZipHeader) + m_CentralZipHeader->FileNameLength + m_CentralZipHeader->ExtraFieldLength + m_CentralZipHeader->FileCommentLength;

			return true;
		}

		//Loads the End of file header
		bool LoadEnd()
		{
			m_EndZipHeader = (EndZipHeader*)&m_Bigbuffer[m_FileCursorPos];

			m_FileCursorPos += sizeof(EndZipHeader) + m_EndZipHeader->CommentLength;
			return true;
		}

		public:
		
			//Loads a zip file from the given location
			bool LoadZipFile(std::string a_FileLocation)
			{
				//Open the file
				std::ifstream file(a_FileLocation, std::ios::ate | std::ifstream::binary);
				if (!file)
				{
					printf("Error file not found\n");
					return false;
				}

				//Get the file size
				CompleteFileSize = (int)file.tellg();
				if (CompleteFileSize == 0)
				{
					printf("Error filesize is zero\n");
					return false;
				}

				//Reset the file pointer to 0
				file.seekg(0);

				//Take a big buffer for loading everything
				m_Bigbuffer.resize(CompleteFileSize);
				memset(m_Bigbuffer.data(), 0, CompleteFileSize);

				file.read(m_Bigbuffer.data(), CompleteFileSize);

				while (m_FileCursorPos < CompleteFileSize)
				{
					//TODO find another way than this
					HeaderSignature *signature = (HeaderSignature*)&m_Bigbuffer[m_FileCursorPos];

					switch (signature->Signature)
					{
					case 0x04034b50: //Local file header
					{
						if (!LoadLocalFileHeader())
							return false;
						break;
					}

					case 0x02014b50: //Central directory file header
					{
						if (!LoadCentralDirectoryFileHeader())
							return false;
						break;
					}

					case 0x06054b50: //End of file header
						if (!LoadEnd())
							return false;
						break;

					default:
						return false;
						break;

					}
				}

				return true;
			}
			
			int GetFileCountInZip()
			{
				return (int)m_FilesInZip.size();
			}

			FileInZip* GetFile(std::string a_Name)
			{
				auto temp = m_FilesInZip.find(a_Name);

				if (temp == m_FilesInZip.end())
					return nullptr;

				return temp->second.get();
			}
	};

	//----------------------------------------------------------
	//MAIN ZIP FILE END
}

//----------------------------------------------------------
//GRUMPYZIP END