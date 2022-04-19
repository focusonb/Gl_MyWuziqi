#pragma once
#include <memory>
#include "Myshader.h"
#include "FileManager/FileManagerControler.h"
#include "FIleManager/WFIleTextManager.h"

using std::unique_ptr;

class ShaderBuilder {
public:
	ShaderBuilder() = delete;
	ShaderBuilder(const char* vertexPath, const char* fragmentPath)
		:m_vertexPath(vertexPath), m_fragmentPath(fragmentPath){
		FileManagerControler fileManagerControler(vertexPath);
		const char* vertexSource = (fileManagerControler.getFileManager())->outPut();
		FileManagerControler fileManagerControler2(fragmentPath);
		const char* fragmentSource = (fileManagerControler2.getFileManager())->outPut();
		auto unique_shader = std::make_unique<MyShader>(vertexSource, fragmentSource);
		m_shader.swap(unique_shader);
	}
	unique_ptr<MyShader> getMyShader() {
		return std::move(m_shader);
	}

	~ShaderBuilder() {
	}

private:
	unique_ptr<MyShader> m_shader;
	const char* m_vertexPath;
	const char* m_fragmentPath;

};

