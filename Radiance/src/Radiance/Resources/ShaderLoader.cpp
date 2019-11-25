#include "pch.h"
#include "ShaderLoader.h"

#include "ResourceLibrary.h"
#include "Radiance/Renderer/API/Shader.h"

namespace Radiance
{

	ShaderLoader::ShaderLoader(ResourceLibrary& _resourceLibrary) 
		: m_ResourceLibrary(_resourceLibrary)
	{
		m_ScanThread = std::thread(&ShaderLoader::ScanShaders, this);
	}

	ShaderLoader::~ShaderLoader()
	{
		//Stop other thread
		m_RequestScan = false;

		if(m_ScanThread.joinable())
			m_ScanThread.join();
	}

	void ShaderLoader::Process()
	{
		ReloadShaders();
	}

	void ShaderLoader::ReloadShaders()
	{
		std::lock_guard<std::mutex> lock_guard(m_Mutex);
		for (Shader* shader : m_DirtyShaders)
			shader->Load();
		m_DirtyShaders.clear();
	}

	void ShaderLoader::ScanShaders()
	{
		using namespace std::chrono_literals;
		namespace fs = std::filesystem;
		const ShaderMap& shaders = m_ResourceLibrary.GetShaders();
		while (m_RequestScan)
		{
			for (const auto& shaderPair : shaders)
			{
				Shader* shader = shaderPair.second;
				const ShaderComponents& shaderComponents = shader->GetShaderComponents();

				long long minTime = 0;
				for (const ShaderComponent& shaderComp : shaderComponents)
				{
					//::last_write_time(fs::path(shader.filename)).time_since_epoch().count();
					long long newTime = last_write_time(fs::path(shaderComp.fileName)).time_since_epoch().count();
					if (newTime > minTime)
						minTime = newTime;
				}
				long long lastTime = m_ShaderTimeMap[shaderPair.first].second;
				if (lastTime != 0 && lastTime < minTime)
				{
					std::lock_guard<std::mutex> lock_guard(m_Mutex);
					m_DirtyShaders.push_back(shaderPair.second);
				}
				m_ShaderTimeMap[shaderPair.first].second = minTime;
				
			}
			// Scan every second
			std::this_thread::sleep_for(1s);
		}
	}

}