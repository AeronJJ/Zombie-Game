#pragma once

#include <chrono>
#include <thread>
//#include <unistd.h>


using namespace std::literals::chrono_literals; // Mucky wucky // This is how Mbed do it maybe
namespace ThisThread = std::this_thread;

void wait_us(int us);
void thread_sleep_for(int delay);

struct Elapsed {
	int time;
	int count();
};

class Timer {
	public:
	Timer();
	void start();
	void stop();
	//Elapsed elapsed_time();
	std::chrono::microseconds elapsed_time();
	void reset();

	private:
	//Elapsed elapsed_;
	std::chrono::microseconds elapsed_;
	std::chrono::steady_clock::time_point begin_;
	std::chrono::steady_clock::time_point end_;
	bool running_ = false;
};
