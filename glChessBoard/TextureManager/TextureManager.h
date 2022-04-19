#pragma once
#include <glad/glad.h>
class TextureManager
{
public:
	TextureManager(int type);
	bool loadImage(const char* path, unsigned int& textureId) const;
	void setChannelType(int type);
private:
	int m_imageChannelType;
};

