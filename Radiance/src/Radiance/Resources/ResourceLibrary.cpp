#include "pch.h"
#include "ResourceLibrary.h"

#include "Radiance/Renderer/API/RenderDevice.h"

#include "Radiance/Renderer/API/Shader.h"
#include "Radiance/Renderer/API/Texture2D.h"
#include "Radiance/Renderer/Mesh.h"

namespace Radiance
{

	ResourceLibrary::ResourceLibrary()
		: m_ShaderLoader(*this)
	{
	}

	ResourceLibrary::~ResourceLibrary()
	{
		for (auto& elem : m_ShaderMap)
			delete elem.second;

		for (auto& elem : m_TextureMap)
			delete elem.second;

		//Conflicts with meshrender and meshrender might use from prefab
		/*for (auto& elem : m_MeshMap)
			delete elem.second;*/
	}

	Shader* ResourceLibrary::LoadShader(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource)
	{
		auto res = m_ShaderMap.find(_name);
		if (res != m_ShaderMap.end())
			return m_ShaderMap[_name];

		auto renderDevice = Locator::Get<RenderDevice>();
		return m_ShaderMap[_name] = renderDevice->CreateShader(_vertexSource, _fragmentSource);
	}

	Texture2D* ResourceLibrary::LoadTexture2D(const std::string& _name, const std::string& _filePath)
	{
		auto res = m_TextureMap.find(_name);
		if (res != m_TextureMap.end())
			return m_TextureMap[_name];

		auto renderDevice = Locator::Get<RenderDevice>();
		return m_TextureMap[_name] = renderDevice->CreateTexture2D(_filePath);
	}

	Mesh* ResourceLibrary::LoadMesh(const std::string& _name, const std::string& _filePath)
	{
		auto res = m_MeshMap.find(_name);
		if (res != m_MeshMap.end())
			return m_MeshMap[_name];
		return m_MeshMap[_name] = m_MeshLoader.Load(_filePath);
	}

	void ResourceLibrary::Update()
	{
		m_ShaderLoader.Process();
	}

}