//-------------------------------------------------------------------------
//------PCH----------------------------------------------------------------
//-------------------------------------------------------------------------
#include "VttApiPch.h"

#include "Core/Timer.h"

namespace Virtual_Tt_Api {

	Timer::Timer() {


	}

	Timer::Timer(int ms) {

		interval = ms;
	}

	Timer::~Timer() {

		Stop();
	}

	int Timer::GetInterval() {

		return interval;
	}

	void Timer::SetInterval(int ms) {

		interval = ms;
	}

	template<typename Function>
	void Timer::Start(Function function) {

		this->running = true;
		std::thread thread([=]() {
			
			if (this->running == false) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (this->running == false) return;
			function();
		});
		thread.detach();
	}

	template<typename Function>
	void Timer::Start(Function function, int ms) {

		this->running = true;
		std::thread thread([=]() {

			if (this->running == false) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			if (this->running == false) return;
			function();
		});
		thread.detach();
	}

	void Timer::Stop() {

		this->running = false;
	}
}