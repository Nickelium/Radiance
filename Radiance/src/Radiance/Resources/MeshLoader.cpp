#include "pch.h"
#include "MeshLoader.h"

#include "Radiance/Renderer/Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Radiance
{
	Mesh* MeshLoader::Load(const std::string& _filePath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(_filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (scene == nullptr ||
			scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
			scene->mRootNode == nullptr ||
			!scene->HasMeshes())
		{
			RAD_CORE_ERROR("Failed to load mesh {0} with error {1}", _filePath, importer.GetErrorString());
		}

		aiMesh* assimpMesh = scene->mMeshes[0];
		RAD_ASSERT(assimpMesh->HasPositions(), "Mesh requires positions");
		
		Mesh* mesh = new Mesh;

		std::vector<glm::vec3> vertices(assimpMesh->mNumVertices);
		std::vector<glm::vec2> texCoords(assimpMesh->mNumVertices);
		std::vector<glm::vec3> normals(assimpMesh->mNumVertices);
		for (int i = 0, nbVertices = static_cast<int>(assimpMesh->mNumVertices);
			i < nbVertices; ++i)
		{
			vertices[i] = 
			{
				assimpMesh->mVertices[i].x,
				assimpMesh->mVertices[i].y,
				assimpMesh->mVertices[i].z 
			};
			if (assimpMesh->HasTextureCoords(0))
			{
					texCoords[i] =
				{
					assimpMesh->mTextureCoords[0][i].x,
					assimpMesh->mTextureCoords[0][i].y,
				};
			}
			if (assimpMesh->HasNormals())
			{
				normals[i] =
				{
					assimpMesh->mNormals[i].x,
					assimpMesh->mNormals[i].y,
					assimpMesh->mNormals[i].z,
				};
			}
		}
		if(assimpMesh->HasPositions())
			mesh->SetPositions(vertices);
		if(assimpMesh->HasTextureCoords(0))
			mesh->SetTexCoords(texCoords);
		if (assimpMesh->HasNormals())
			mesh->SetNormals(normals);

		std::vector<uint32_t> indices(assimpMesh->mNumFaces * 3u);
		for (int i = 0, nbFaces = assimpMesh->mNumFaces; 
			i < nbFaces; ++i)
		{
			RAD_ASSERT(assimpMesh->mFaces[i].mNumIndices == 3, "Only supports triangulated meshes");
			indices[i * 3u + 0u] = assimpMesh->mFaces[i].mIndices[0];
			indices[i * 3u + 1u] = assimpMesh->mFaces[i].mIndices[1];
			indices[i * 3u + 2u] = assimpMesh->mFaces[i].mIndices[2];
		}
		mesh->SetIndices(indices);

		return mesh;
	}

	void MeshLoader::ProcessNode(aiNode* /*_node*/, aiScene* /*_scene*/)
	{
		
	}

	void MeshLoader::ProcessMesh(aiMesh* /*_mesh*/, aiScene* /*_scene*/)
	{

	}

}