//
// Created by Quentin Novinger on 4/11/21.
//

#include "HandIndex.hpp"

HandIndexer::HandIndexer(std::vector<uint8_t> rounds) {
    int n = rounds.size();
    uint8_t cRounds[n];
    for (int i = 0; i < n; i++) {
        cRounds[i] = rounds[i];
    }
    hand_indexer_init(n, cRounds, &this->indexer);
}

HandIndexer::~HandIndexer() {
    hand_indexer_free(&this->indexer);
}

uint64_t HandIndexer::size(uint_fast32_t round) {
    return hand_indexer_size(&indexer, round);
}

uint64_t HandIndexer::getIndex(const std::vector<uint8_t> &cards) {
    int n = cards.size();
    uint8_t cCards[n];
    for (int i = 0; i < n; i++) {
        cCards[i] = cards[i];
    }
    return hand_index_last(&indexer, cCards);
}

void HandIndexer::undoIndex(uint_fast32_t round, hand_index_t index, std::vector<uint8_t> &cards) {
    auto n = cards.size();
    uint8_t cCards[n];
    hand_unindex(&indexer, round, index, cCards);
    for (int i = 0; i < n; i++) {
         cards[i] = cCards[i];
    }
}


