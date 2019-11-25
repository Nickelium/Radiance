#include "pch.h"

#include "GLGPUTimer.h"

#include <glad/glad.h>

namespace Radiance
{
	GLGPUTimer::~GLGPUTimer()
	{
		for (const auto& pairStringQuery : m_MapQuery)
			DeleteQuery(pairStringQuery.second);
	}

	void GLGPUTimer::Update()
	{
		for (auto& query : m_MapQuery)
		{
			glGetQueryObjectui64v(
				query.second[m_FrontBufferIndex].start.handle, GL_QUERY_RESULT, 
				&query.second[m_FrontBufferIndex].start.result);
			glGetQueryObjectui64v(
				query.second[m_FrontBufferIndex].end.handle, GL_QUERY_RESULT,
				&query.second[m_FrontBufferIndex].end.result);

			uint64_t diffResult = query.second[m_FrontBufferIndex].end.result - query.second[m_FrontBufferIndex].start.result;
			query.second.callback({ query.first, diffResult * 1e-9f });
		}

		//Flip between one and zero
		m_BackBufferIndex = (m_BackBufferIndex + 1) & 1;
		m_FrontBufferIndex = (m_FrontBufferIndex + 1) & 1;
	}

	void GLGPUTimer::Begin(const char* _name, const QueryCallback& _fnc)
	{
		if (m_MapQuery.find(_name) == m_MapQuery.end())
		{
			m_MapQuery[_name] = CreateQuery(_fnc);
			glQueryCounter(m_MapQuery[_name][m_FrontBufferIndex].start.handle, GL_TIMESTAMP);
			glQueryCounter(m_MapQuery[_name][m_FrontBufferIndex].end.handle, GL_TIMESTAMP);
		}
		glQueryCounter(m_MapQuery[_name][m_BackBufferIndex].start.handle, GL_TIMESTAMP);
	}

	void GLGPUTimer::End(const char* _name)
	{
		RAD_CORE_ASSERT(m_MapQuery.find(_name) != m_MapQuery.end(), "Name not stored in query map");
		glQueryCounter(m_MapQuery[_name][m_BackBufferIndex].end.handle, GL_TIMESTAMP);
	}
	
	GLGPUTimer::GLGPUQuery GLGPUTimer::CreateQuery(QueryCallback _callback)
	{
		Handle handlesQuery[GLGPUTimer::s_NbBuffers * 2];
		glGenQueries(s_NbBuffers * 2, handlesQuery);
		GLGPUTimer::GLGPUQuery query;
		query.queryPairFirst.start.handle = handlesQuery[0];
		query.queryPairFirst.end.handle = handlesQuery[1];
		query.queryPairSecond.start.handle = handlesQuery[2];
		query.queryPairSecond.end.handle = handlesQuery[3];
		query.callback = _callback;
		return query;
	}

	void GLGPUTimer::DeleteQuery(GLGPUQuery _gpuQuery)
	{
		constexpr int nbHandles = 4;
		Handle handles[nbHandles];
		handles[0] = _gpuQuery.queryPairFirst.start.handle;
		handles[1] = _gpuQuery.queryPairFirst.end.handle;
		handles[2] = _gpuQuery.queryPairSecond.start.handle;
		handles[3] = _gpuQuery.queryPairSecond.end.handle;
		glDeleteQueries(nbHandles, handles);
	}

}