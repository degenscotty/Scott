#pragma once
#include <chrono>

namespace Scott
{
	class SCOTT_API GameTime
	{
	public:
		GameTime();
		void Update();
		float GetElapsedSec() const;
		unsigned int GetFPS() const;

		inline static GameTime& get() { return *s_Instance; }

	private:
		std::chrono::high_resolution_clock::time_point m_CurrentTime;
		std::chrono::high_resolution_clock::time_point m_PreviousTime;
		float m_ElapsedSec;

		static GameTime* s_Instance;
	};
}


