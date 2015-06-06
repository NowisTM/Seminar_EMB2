#ifndef util_HPP
#define util_HPP

#include <chrono>
#include <locale>

#ifdef USE_EMBB
    #define RUN_EMBB(fct) } catch (embb::base::Exception& e) { \
        std::cout << "## " #fct " exception: " << e.What() << std::endl;
#else
    #define RUN_EMBB(fct)
#endif

// #define USE_MS
#ifdef USE_MS
    #define measure_time std::chrono::milliseconds
    #define measure_text " ms"
#else
    #define measure_time std::chrono::microseconds
    #define measure_text " µs"
#endif

#define RUN(fct) std::cout << "## " #fct " ##" << std::endl; \
    try { \
        std::cout.imbue(std::locale("")); \
        std::cout << "# " << std::fixed << measure<measure_time>::execute<>(fct) << measure_text << std::endl; \
        RUN_EMBB(fct) \
    } catch (std::exception& e) { \
        std::cout << "## " #fct " exception: " << e.what() << std::endl; \
    } \
    std::cout << "## " #fct " end ##" << std::endl << std::endl;

// from http://codereview.stackexchange.com/questions/48872/measuring-execution-time-in-c
template<typename TimeT = std::chrono::milliseconds>
struct measure {
	template<typename F, typename ...Args>
	static typename TimeT::rep execute(F func, Args&& ... args) {
		auto start = std::chrono::system_clock::now();

		// Now call the function with all the parameters you need.
		func(std::forward<Args>(args)...);

		auto duration = std::chrono::duration_cast< TimeT>(std::chrono::system_clock::now() - start);

		return duration.count();
	}
};

#ifdef USE_OMP
    #include <omp.h>
    void sleep(double seconds = 1.0) {
        double startTime = omp_get_wtime();
        while( (omp_get_wtime() - startTime) < seconds);
    }
#elifdef USE_EMBB
    #include <unistd.h>
    void sleep(double seconds = 1.0) {
        if (usleep((unsigned int)(seconds * 1000)) != 0)
            throw std::runtime_error("sleep failed");
    }
#else // std-example ohne threads
    #include <thread>
    void sleep(double seconds = 1.0) {
        std::this_thread::sleep_for (std::chrono::milliseconds((int)(seconds * 1000)));
    }
#endif

#endif // util_HPP

