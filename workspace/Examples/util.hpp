#ifndef util_HPP
#define util_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale>
#include <cstdio>
#include <ctime>

#ifdef USE_EMBB
    #define RUN_EMBB(fct) } catch (embb::base::Exception& e) { \
        std::cout << "## " #fct " exception: " << e.What() << std::endl;
#else
    #define RUN_EMBB(fct)
#endif

// #define USE_TIME_MS
#ifdef USE_TIME_MS
    #define measure_time std::chrono::milliseconds
    #define measure_text " ms"
#else
    #define measure_time std::chrono::microseconds
    #define measure_text " µs"
#endif

#define RUN(fct) std::cout << "## " #fct " ##" << std::endl; \
    try { \
        measure_time::rep mt = measure<measure_time>::execute<>(fct); \
        std::clog << "" #fct " " << std::fixed << mt << measure_text << std::endl; \
        std::cout << "# " << std::fixed << mt << measure_text << std::endl; \
        RUN_EMBB(fct) \
    } catch (std::exception& e) { \
        std::cout << "## " #fct " exception: " << e.what() << std::endl; \
    } \
    std::cout << "## " #fct " end ##" << std::endl << std::endl;

// von http://codereview.stackexchange.com/questions/48872/measuring-execution-time-in-c
template<typename TimeT = std::chrono::milliseconds>
struct measure {
	template<typename F, typename ...Args>
	static typename TimeT::rep execute(F func, Args&& ... args) {
		auto start = std::chrono::system_clock::now();

		// Functionsaufruf mit Argumenten
		func(std::forward<Args>(args)...);

		auto duration = std::chrono::duration_cast< TimeT>(std::chrono::system_clock::now() - start);

		return duration.count();
	}
};

void init(const std::string& name = "out", bool use_cout = true) {
    std::freopen((name + ".time").c_str(), "w", stderr);
    if (!use_cout)
        std::freopen((name + ".out").c_str(), "w", stdout);

    std::cout.imbue(std::locale(""));
    std::clog.imbue(std::locale(""));
}

#ifdef USE_OMP
    #include <omp.h>
    void sleep(double seconds = 0.1) {
        double startTime = omp_get_wtime();
        while( (omp_get_wtime() - startTime) < seconds);
    }
#elif defined(USE_EMBB)
    #include <unistd.h>
    void sleep(double seconds = 0.1) {
        if (usleep((unsigned int)(seconds * 1000 * 1000)) != 0)
            throw std::runtime_error("sleep failed");
        /*struct timespec tim = { 0, (long)(seconds * 1000 * 1000 * 1000) };
        nanosleep(&tim, NULL);*/
    }
#else // std-example ohne threads
    #include <thread>
    void sleep(double seconds = 0.1) {
        std::this_thread::sleep_for (std::chrono::milliseconds((int)(seconds * 1000)));
    }
#endif

class SumCustom {
    unsigned int a;
public:
    SumCustom(int value = 0) : a(value) {}

    SumCustom operator+(const SumCustom& other) const {
        return SumCustom(this->a + other.a);
    }

    SumCustom& operator+=(const SumCustom& other) {
        this->a += other.a;
        return *this;
    }

    SumCustom& operator=(int value) {
        this->a = value;
        return *this;
    }

    friend
    std::ostream& operator<<(std::ostream& os, const SumCustom& sum) {
        return os << sum.a;
    }
};

template <typename T>
void initVector(std::vector<T>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i] = i;
	}
}

template <typename T>
void initVector(std::vector<T>& vec, T value) {
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i] = value;
	}
}

#endif // util_HPP

