#pragma once

#include <vector>
#include <string>

#include <GrumpyZip\ZipFile.h>

#include <memory>

namespace Core
{
	class FileSystem
	{
	private:
		static FileSystem *m_StaticClass;

		std::unique_ptr<GrumpyZip::ZipFile> m_ZipFile;

	public:
		__declspec(dllexport) void InitializeZipFile(std::string a_FilePath);
		__declspec(dllexport) void Shutdown();

		__declspec(dllexport) std::unique_ptr<GrumpyZip::FileInZip> GetFile(std::string a_FilePath);

		__declspec(dllexport) static FileSystem *StaticClass();

	};
}