#pragma once

#include "Radiance/Core/Locator.h"

#include "MeshLoader.h"

#define RESOURCELIB ResourceLibrary

namespace Radiance
{
	class Shader;
	class Texture2D;
	class Mesh;

	//TODO Hashing string to int for better performance
	class ResourceLibrary : public Service
	{
	public:
		virtual ~ResourceLibrary();

		Shader* LoadShader(const std::string& _name,
			const std::string& _vertexSource, const std::string& _fragmentSource);

		Texture2D* LoadTexture2D(const std::string& _name, const std::string& _filePath);

		//TODO
		Mesh* LoadMesh(const std::string& _name, const std::string& _filePath);

		SERVICE_CLASS(ResourceLibrary);
	private:
		using ShaderMap = std::unordered_map<std::string, Shader*>;
		using TextureMap = std::unordered_map<std::string, Texture2D*>;
		using MeshMap = std::unordered_map<std::string, Mesh*>;

		ShaderMap m_ShaderMap;
		TextureMap m_TextureMap;
		MeshMap m_MeshMap;

		MeshLoader m_MeshLoader;
	};
}
