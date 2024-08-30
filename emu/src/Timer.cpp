#include "Timer.h"

void wait_us(int us) {
  //usleep(us);
}

int Elapsed::count() {
	return time;
}


Timer::Timer() { }

void Timer::start() {
	begin_ = std::chrono::steady_clock::now();
	running_ = true;
}

void Timer::stop() {
	end_ = std::chrono::steady_clock::now();
	running_ = false;
}

std::chrono::microseconds Timer::elapsed_time() {
	if (running_) {
		end_ = std::chrono::steady_clock::now();
	}
	//elapsed_.time = 1000;
	//elapsed_ = end_ - begin_;
	elapsed_ = std::chrono::duration_cast<std::chrono::microseconds>(end_ - begin_);
	return elapsed_;
}

void Timer::reset() {
	end_ = std::chrono::steady_clock::now();
}
