#include "Utilities\FileSystem.h"

#include "Utilities\Utilities.h"

namespace Core
{
	FileSystem *FileSystem::m_StaticClass = nullptr;

	std::unique_ptr<GrumpyZip::FileInZip> FileSystem::GetFile(std::string a_FilePath)
	{
		if (m_ZipFile)
		{
			auto result = std::make_unique<GrumpyZip::FileInZip>();
			auto file = m_ZipFile->GetFile(a_FilePath);
			
			if (file == nullptr)
			{
				LogErr("File not found [%s]", a_FilePath.c_str());
				return nullptr;
			}

			result->Data = file->Data;
			result->FileSize = file->FileSize;

			return result;
		}
		else
		{
			auto result = std::make_unique<GrumpyZip::FileInZip>();
			
			std::ifstream file(a_FilePath, std::ios::ate | std::ifstream::binary);
			
			if (!file)
			{
				LogErr("File not found [%s]", a_FilePath.c_str());
				return nullptr;
			}
			
			// Get the file size
			result->FileSize = file.tellg();
			result->FileSize++;

			if (result->FileSize <= 0)
			{
				LogErr("File size is zero or smaller");
				return nullptr;
			}

			// Reset the pointer
			file.seekg(0);

			// Resize the vector
			result->Data.resize(result->FileSize);

			// Copy the data
			file.read((char*)result->Data.data(), result->FileSize);

			return std::move(result);
		}

		return nullptr;
	}

	void FileSystem::InitializeZipFile(std::string a_FilePath)
	{
		m_ZipFile = std::make_unique<GrumpyZip::ZipFile>();
		m_ZipFile->LoadZipFile(a_FilePath);
	}

	void FileSystem::Shutdown()
	{
		if (m_ZipFile != nullptr)
			m_ZipFile.reset();
	}

	FileSystem *FileSystem::StaticClass()
	{	
		if (m_StaticClass == nullptr)
		{
			m_StaticClass = new FileSystem();
		}

		return m_StaticClass;	
	}
}