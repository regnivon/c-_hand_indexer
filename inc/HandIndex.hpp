//
// Created by Quentin Novinger on 4/11/21.
//

#ifndef INDEXER_HANDINDEX_H
#define INDEXER_HANDINDEX_H

#include <array>
#include <cstdint>
#include <vector>

#include "indexer/hand_index.h"

class HandIndexer {
public:
    HandIndexer(std::vector<uint8_t> rounds);

    ~HandIndexer();

    uint64_t size(uint_fast32_t round);

    uint64_t getIndex(const std::vector<uint8_t> &cards);

    void undoIndex(uint_fast32_t round, hand_index_t index, std::vector<uint8_t> &cards);

private:
    hand_indexer_t indexer;
};

#endif // INDEXER_HANDINDEX_H
