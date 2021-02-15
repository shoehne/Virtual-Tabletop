#pragma once
#ifndef TIMER_H
#define TIMER_H

namespace Virtual_Tt_Api {

	class Timer {

	public:
		Timer();
		Timer(int ms);
		~Timer();

		int GetInterval();
		void SetInterval(int ms);
		template<typename Function>
		void Start(Function function);
		template<typename Function>
		void Start(Function function, int ms);
		void Stop();

	private:
		int interval = 0;
		bool running = false;
	};
}

#endif // !TIMER_H
