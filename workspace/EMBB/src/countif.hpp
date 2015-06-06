#ifndef countif_HPP
#define countif_HPP

#include <embb/algorithms/algorithms.h>

#include <iostream>

void RunCountIf() {
    int range[] = { 0, 3, 2, 0, 1, 1, 3, 2};

    std::iterator_traits<int*>::difference_type count;
    using embb::algorithms::Count;
    count = Count(range, range + 8, 1);
    assert(count == 2);

    using embb::algorithms::CountIf;
    count = CountIf(range, range + 8,
                    [](const int& value) -> bool { return value > 0; });
    assert(count == 6);
}

#endif // countif_HPP

