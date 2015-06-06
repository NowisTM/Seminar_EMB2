#ifndef scan_HPP
#define scan_HPP

#include <embb/algorithms/algorithms.h>
#include <embb/base/c/internal/unused.h>
#include <vector>

void CheckResults(const std::vector<int>& results) {
	assert(results.size() == 5);
	assert(results[0] == 1);
	assert(results[1] == 3);
	assert(results[2] == 6);
	assert(results[3] == 10);
	assert(results[4] == 15);
	EMBB_UNUSED_IN_RELEASE(results);
}

/**
 * Example using embb::algorithms::Scan.
 *
 *
 */
void RunScan() {
	std::vector<int> input_range(5);
	for (size_t i = 0; i < input_range.size(); i++) {
		input_range[i] = static_cast<int>(i) + 1;
	}

	std::vector<int> output_range(input_range.size());
	output_range[0] = input_range[0];

	embb::algorithms::Scan(input_range.begin(), input_range.end(), output_range.begin(),
		 0, std::plus<int>());

	CheckResults(output_range);
}

#endif // scan_HPP
