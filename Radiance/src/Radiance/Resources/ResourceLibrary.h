#pragma once

#include "Radiance/Core/Locator.h"

#define RESOURCELIB ResourceLibrary

namespace Radiance
{
	class Shader;
	class Texture2D;

	//TODO Hashing string to int for better performance
	class ResourceLibrary : public Service
	{
	public:
		virtual ~ResourceLibrary();

		Shader* LoadShader(const std::string& _name,
			const std::string& _vertexSource, const std::string& _fragmentSource);

		Texture2D* LoadTexture2D(const std::string& _name, const std::string& _filePath);

		SERVICE_CLASS(ResourceLibrary);
	private:
		using ShaderMap = std::unordered_map<std::string, Shader*>;
		using TextureMap = std::unordered_map<std::string, Texture2D*>;

		ShaderMap m_ShaderMap;
		TextureMap m_TextureMap;

	};
}
