#pragma once
#include <cstring>
#include <iostream>

class FileTextManager
{
public:
	FileTextManager(const char* filePath) :m_filePath(filePath)
	{};
	virtual  char* outPut() = 0;
	virtual ~FileTextManager() {};
protected:
	const char* m_filePath;
};
class WFIleTextManager : public FileTextManager
{
public:
	WFIleTextManager(const char* filePath) :FileTextManager(filePath)
	{};
	virtual ~WFIleTextManager();
	char* outPut() override;
private:
	char* m_shaderContent;
	size_t m_textSize;
};

