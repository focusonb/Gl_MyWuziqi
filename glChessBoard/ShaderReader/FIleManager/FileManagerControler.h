#pragma once
class FileTextManager;
enum class FIleTextManager { Windows };

class FileManagerControler
{
public:
	FileManagerControler(const char* filePath ,FIleTextManager type = FIleTextManager::Windows);
	FileTextManager* getFileManager();
	~FileManagerControler();
private:
	FileTextManager* m_ptr_fileManager;
};

