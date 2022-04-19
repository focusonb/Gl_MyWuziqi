#include "FileManagerControler.h"
#include "WFIleTextManager.h"

FileManagerControler::FileManagerControler(const char* filePath, FIleTextManager type)
{
	switch (type)
	{
	case FIleTextManager::Windows:
		m_ptr_fileManager = new WFIleTextManager(filePath);
	}
}

FileTextManager * FileManagerControler::getFileManager()
{
	return m_ptr_fileManager;
}

FileManagerControler::~FileManagerControler()
{
	delete m_ptr_fileManager;
}

