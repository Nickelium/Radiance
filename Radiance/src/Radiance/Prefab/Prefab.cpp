#include "pch.h"
#include "Prefab.h"

#include "Radiance/Renderer/Mesh.h"

namespace Radiance
{
	Mesh* CreateCube()
	{
		Mesh* mesh = new Mesh;
		std::vector<glm::vec3> positions =
		{
			{ -0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ -0.5f, +0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f, -0.5f, +0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, -0.5f, +0.5f },

			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },

			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },

			{ -0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, -0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ +0.5f, -0.5f, +0.5f },
			{ -0.5f, -0.5f, +0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, -0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ +0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, +0.5f },
			{ -0.5f, +0.5f, -0.5f }
		};
		mesh->SetPositions(positions);	
		std::vector<uint32_t> indices =
		{
			0, 2, 1,
			3, 5, 4, 

			6, 7, 8,
			9, 10, 11,

			12, 13, 14,
			15, 16, 17,

			18, 20, 19,
			21, 23, 22,

			24, 25, 26,
			27, 28, 29,

			30, 32, 31,
			33, 35, 34
		};
		mesh->SetIndices(indices);

		return mesh;
	}

	Mesh* CreateTriangle()
	{
		Mesh* mesh = new Mesh;
		std::vector<glm::vec3> positions =
		{
			{-0.5f, -0.5f, 0.0f},
			{+0.5f, -0.5f, 0.0f},
			{+0.0f, +0.5f, 0.0f}
		};
		mesh->SetPositions(positions);
		std::vector<glm::vec3> normals = 
		{
			{0.0f, 0.0f, 1.0f}
		};
		mesh->SetNormals(normals);
		std::vector<glm::vec2> texCoords =
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{0.0f, 1.0f}
		};
		mesh->SetTexCoords(texCoords);
		std::vector<unsigned int> indices =
		{
			0, 1, 2
		};
		mesh->SetIndices(indices);

		return mesh;
	}

	Mesh* CreateSphere(SphereDescriptor _descriptor)
	{
		Mesh* mesh = new Mesh;

		float radius = _descriptor.radius;
		int nbHorizontalLines = _descriptor.nbHorizontalSlices;
		int nbVerticalLines = _descriptor.nbVerticalSlices;

		//Number of horizontal lines excluding top and bottom
		int nbHorizontalVertices = nbHorizontalLines - 2;
		int nbVerticalVertices = 2 * (nbVerticalLines  - 2) + 2;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<uint32_t> indices;
		positions.reserve(static_cast<size_t>(2 + nbHorizontalVertices * nbVerticalVertices));
		normals.reserve(static_cast<size_t>(2 + nbHorizontalVertices * nbVerticalVertices));
		texCoords.reserve(static_cast<size_t>(2 + nbHorizontalVertices * nbVerticalVertices));
		indices.reserve(static_cast<size_t>((nbHorizontalVertices - 1) * nbVerticalVertices * 6 + 2 * 3 * nbVerticalVertices));

		//Generate sphere as spherical coordinates
		if (nbHorizontalLines > 0)
		{
			positions.push_back(glm::vec3(0.0f, radius, 0.0f));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords.push_back(glm::vec2(0.0f, 0.0f));
		}

		if (nbHorizontalLines > 2)
		{
			float deltaTheta = Constants::PI / (nbHorizontalVertices + 1);
			float deltaPhi = Constants::TwoPI / nbVerticalVertices;
			for (int i = 0; i < nbHorizontalVertices; ++i)
				for (int j = 0; j < nbVerticalVertices; ++j)
				{
					float theta = (i + 1) * deltaTheta;
					float phi = j * deltaPhi;
					float x = radius * sin(theta) * cos(phi);
					float y = radius * cos(theta);
					float z = radius * sin(theta) * sin(phi);
					positions.push_back(glm::vec3(x, y, z));
					normals.push_back(glm::normalize(glm::vec3(x, y, z)));
					texCoords.push_back(glm::vec2(theta / Constants::PI, phi / Constants::TwoPI));
				}
		}

		if (nbHorizontalLines > 1)
		{
			positions.push_back(glm::vec3(0.0f, -radius, 0.0f));
			normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords.push_back(glm::vec2(0.0f, 1.0f));
		}

		mesh->SetPositions(positions);
		mesh->SetNormals(normals);
		mesh->SetTexCoords(texCoords);


		uint32_t northPoleIndex = 0u;
		uint32_t baseIndex = 1;
		for (int i = 0; i < nbVerticalVertices; ++i)
		{
			indices.push_back(northPoleIndex);
			indices.push_back(baseIndex + (i + 0) % nbVerticalVertices);
			indices.push_back(baseIndex + (i + 1) % nbVerticalVertices);
		}

		for(int i = 0; i < nbHorizontalVertices - 1; ++i)
			for (int j = 0; j < nbVerticalVertices; ++j)
			{
				indices.push_back(baseIndex + 
					i * nbVerticalVertices + (j + 0) % nbVerticalVertices);
				indices.push_back(baseIndex + 
					(i + 1) * nbVerticalVertices + (j + 0) % nbVerticalVertices);
				indices.push_back(baseIndex + 
					i * nbVerticalVertices + (j + 1) % nbVerticalVertices);
								  
				indices.push_back(baseIndex + 
					(i + 1) * nbVerticalVertices + (j + 0) % nbVerticalVertices);
				indices.push_back(baseIndex + 
					(i + 1) * nbVerticalVertices + (j + 1) % nbVerticalVertices);
				indices.push_back(baseIndex + 
					i * nbVerticalVertices + (j + 1) % nbVerticalVertices);
			}

		uint32_t southPoleIndex = static_cast<int32_t>(positions.size()) - 1;

		baseIndex = southPoleIndex - nbVerticalVertices;

		for (int i = 0; i < nbVerticalVertices; ++i)
		{
			indices.push_back(southPoleIndex);
			indices.push_back(baseIndex + (i + 1) % nbVerticalVertices);
			indices.push_back(baseIndex + (i + 0) % nbVerticalVertices);
		}
		
		mesh->SetIndices(indices);

		return mesh;
	}
}