#pragma once
#include "Radiance/Core/GPUTimer.h"

namespace Radiance
{
	class GLGPUTimer : public GPUTimer
	{
	public:
		struct GLGPUQuery
		{
			struct Query
			{
				Handle handle;
				uint64_t result;
			};

			struct QueryPair
			{
				Query start;
				Query end;
			};

			QueryPair queryPairFirst;
			QueryPair queryPairSecond;

			QueryCallback callback;

			inline QueryPair& operator[](size_t _index)
			{
				if (_index == 0)
					return queryPairFirst;
				return queryPairSecond;
			}
		};
	public:
		virtual ~GLGPUTimer();
		virtual void Update();

		virtual void Begin(const char* _name, const QueryCallback& _callback);
		virtual void End(const char* _name);
	private:
		static GLGPUQuery CreateQuery(QueryCallback _callback);
		static void DeleteQuery(GLGPUQuery _gpuQuery);

		static const int s_NbBuffers = 2;

		unsigned int m_BackBufferIndex = 0;
		unsigned int m_FrontBufferIndex = 1;

		using MapQuery = std::unordered_map<const char*, GLGPUQuery>;
		MapQuery m_MapQuery;
	};
}