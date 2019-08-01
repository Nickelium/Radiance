#pragma once

#include "API/Shader.h"

namespace Radiance
{
	class Texture2D;

	enum UniformType
	{
		TYPE_BOOL,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_VEC2,
		TYPE_VEC3,
		TYPE_VEC4,
		TYPE_MAT4,

		TYPE_SAMPLER2D
	};

	struct Uniform
	{
		UniformType Type;
		union
		{
			bool Bool;
			float Float;
			int Int;
			glm::vec2 Vec2;
			glm::vec3 Vec3;
			glm::vec4 Vec4;
			glm::mat4 Mat4;
		};
	};

	struct UniformSampler
	{
		UniformType Type;
		int Slot;
		union
		{
			Texture2D* Sampler2D;
		};
	};

	class Material
	{
	public:
		Material(Shader* _shader);
		//TEMP 
		//TODO
		~Material();

		inline Shader* GetShader() const { return m_Shader; }

		void Bind() const;
		void UnBind() const;

		void SetUniform(const std::string& _name, bool _val);
		void SetUniform(const std::string& _name, float _val);
		void SetUniform(const std::string& _name, int _value);
		void SetUniform(const std::string& _name, const glm::vec2& _val);
		void SetUniform(const std::string& _name, const glm::vec3& _val);
		void SetUniform(const std::string& _name, const glm::vec4& _val);
		void SetUniform(const std::string& _name, const glm::mat4& _val);

		void SetUniform(const std::string& _name, Texture2D* _texture, int _slot);

	private:
		using UniformMap = std::unordered_map<std::string, Uniform>;
		using UniformSamplerMap = std::unordered_map<std::string, UniformSampler>;

		Shader* m_Shader;
		UniformMap m_UniformMap;
		UniformSamplerMap m_UniformSamplerMap;
	};
}
