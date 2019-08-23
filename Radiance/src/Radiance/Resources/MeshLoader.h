#pragma once

struct aiNode;
struct aiMesh;
struct aiScene;

namespace Radiance
{
	class Mesh;
	class MeshLoader
	{
	public:
		Mesh* Load(const std::string& _filePath);
	private:
		void ProcessNode(aiNode* _node, aiScene* _scene);
		void ProcessMesh(aiMesh* _mesh, aiScene* _scene);
	};
}
