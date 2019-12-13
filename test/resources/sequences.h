#ifndef STEPIKALGORITHMSSTRUCTURES_SEQUENCES_H
#define STEPIKALGORITHMSSTRUCTURES_SEQUENCES_H

#include <vector>

namespace sequences {

    std::vector<std::vector<int>> const sequence {
            {1},
            {1,  1},
            {1,  1,  1},
            {1,  2,  3,  4,  5,  6},
            {6,  5,  4,  3,  2,  1},
            {1,  2,  3,  4,  5,  6,  7},
            {7,  6,  5,  4,  4,  2,  1},
            {-2, 0,  -1, -1, 0,  -2, 1,  2, 1, 2},
            {-3, -2, -1, 0,  0,  1,  2,  3},
            {3,  2,  1,  0,  0,  -1, -2, -3},
            {6,  6,  0,  3,  1,  3,  2,  3, 3, 4, 3,  5,  3, 6},
            {-2, 3,  0,  3,  -1, 0,  -1, 3, 0, 1, -2, -1, 1, 3, 2, 3, 1, 2, 2, 3, -3, -1, 0, 2, 3}};
}
#endif //STEPIKALGORITHMSSTRUCTURES_SEQUENCES_H
