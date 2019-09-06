#pragma once

namespace Radiance
{
	class Shader;
	class ResourceLibrary;

	class ShaderLoader
	{
	public:
		ShaderLoader(ResourceLibrary& _resourceLibrary);
		~ShaderLoader();

		void Process();
	private:
		void ReloadShaders();
		void ScanShaders();

		using ShaderTime = std::pair<Shader*, long long>;
		using ShaderTimeMap = std::unordered_map<std::string, ShaderTime>;
		ShaderTimeMap m_ShaderTimeMap;
		std::vector<Shader*> m_DirtyShaders;

		ResourceLibrary& m_ResourceLibrary;
		bool m_RequestScan = true;

		std::thread m_ScanThread;
		std::mutex m_Mutex;
	};
}
