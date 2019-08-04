#include "pch.h"
#include "Material.h"

#include "API/Texture2D.h"

namespace Radiance
{

	Material::Material(Shader* _shader)
		: m_Shader(_shader)
	{
	}

	Material::~Material()
	{
		delete m_Shader;
	}

	void Material::Bind() const
	{
		m_Shader->Bind();
		for (auto& uniform : m_UniformMap)
		{
			switch (uniform.second.Type)
			{
			case TYPE_BOOL:
				m_Shader->SetUniform(uniform.first, uniform.second.Bool);
				break;
			case TYPE_INT:
				m_Shader->SetUniform(uniform.first, uniform.second.Int);
				break;
			case TYPE_FLOAT:
				m_Shader->SetUniform(uniform.first, uniform.second.Float);
				break;
			case TYPE_VEC2:
				m_Shader->SetUniform(uniform.first, uniform.second.Vec2);
				break;
			case TYPE_VEC3:
				m_Shader->SetUniform(uniform.first, uniform.second.Vec3);
				break;
			case TYPE_VEC4:
				m_Shader->SetUniform(uniform.first, uniform.second.Vec4);
				break;
			case TYPE_MAT4:
				m_Shader->SetUniform(uniform.first, uniform.second.Mat4);
				break;
			default:
				break;
			}
		}

		for (auto& uniformSampler : m_UniformSamplerMap)
		{
			switch (uniformSampler.second.Type)
			{
			case TYPE_SAMPLER2D:
			{
				int slot = uniformSampler.second.Slot;
				uniformSampler.second.Sampler2D->Bind(slot);
				m_Shader->SetUniform(uniformSampler.first, slot);
				break;
			}
			default:
				break;
		
			}
		}
	}

	void Material::UnBind() const
	{
		m_Shader->UnBind();
	}

	void Material::SetUniform(const std::string& _name, bool _val)
	{
		m_UniformMap[_name].Type = TYPE_BOOL;
		m_UniformMap[_name].Bool = _val;
	}

	void Material::SetUniform(const std::string& _name, float _val)
	{
		m_UniformMap[_name].Type = TYPE_FLOAT;
		m_UniformMap[_name].Float = _val;
	}

	void Material::SetUniform(const std::string& _name, int _val)
	{
		m_UniformMap[_name].Type = TYPE_INT;
		m_UniformMap[_name].Int = _val;
	}

	void Material::SetUniform(const std::string& _name, const glm::vec2& _val)
	{
		m_UniformMap[_name].Type = TYPE_VEC2;
		m_UniformMap[_name].Vec2 = _val;
	}

	void Material::SetUniform(const std::string& _name, const glm::vec3& _val)
	{
		m_UniformMap[_name].Type = TYPE_VEC3;
		m_UniformMap[_name].Vec3 = _val;
	}

	void Material::SetUniform(const std::string& _name, const glm::vec4& _val)
	{
		m_UniformMap[_name].Type = TYPE_VEC4;
		m_UniformMap[_name].Vec4 = _val;
	}

	void Material::SetUniform(const std::string& _name, const glm::mat4& _val)
	{
		m_UniformMap[_name].Type = TYPE_MAT4;
		m_UniformMap[_name].Mat4 = _val;
	}

	void Material::SetUniform(const std::string& _name, Texture2D* _texture, int _slot)
	{
		m_UniformSamplerMap[_name].Type = TYPE_SAMPLER2D;
		m_UniformSamplerMap[_name].Slot = _slot;
		m_UniformSamplerMap[_name].Sampler2D = _texture;
	}

}