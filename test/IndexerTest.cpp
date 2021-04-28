//
// Created by Quentin Novinger on 4/11/21.
//

#include <memory>

#include <gtest/gtest.h>

#include "HandIndex.hpp"

class IndexerTest : public ::testing::Test {
public:
    IndexerTest() {
        preflopIndexer = std::make_unique<HandIndexer>(std::vector<uint8_t>({2}));
        flopIndexer = std::make_unique<HandIndexer>(std::vector<uint8_t>({2, 3}));
        turnIndexer = std::make_unique<HandIndexer>(std::vector<uint8_t>({2, 3, 1}));
        riverIndexer = std::make_unique<HandIndexer>(std::vector<uint8_t>({2, 3, 1, 1}));
    }

    std::unique_ptr<HandIndexer> preflopIndexer = nullptr;
    std::unique_ptr<HandIndexer> flopIndexer = nullptr;
    std::unique_ptr<HandIndexer> turnIndexer = nullptr;
    std::unique_ptr<HandIndexer> riverIndexer = nullptr;
};

TEST_F(IndexerTest, AssertProperSizes) {
    ASSERT_EQ(preflopIndexer->size(0), 169);
    ASSERT_EQ(flopIndexer->size(1), 1286792);
    ASSERT_EQ(turnIndexer->size(2), 55190538);
    ASSERT_EQ(riverIndexer->size(3), 2428287420);
}

TEST_F(IndexerTest, AssertProperIndices) {
    ASSERT_EQ(
            preflopIndexer->getIndex(std::vector<uint8_t>({0, 1})),
            0
    );
    ASSERT_EQ(
            preflopIndexer->getIndex(std::vector<uint8_t>({50, 51})),
            90
    );

    ASSERT_EQ(
            flopIndexer->getIndex(std::vector<uint8_t>({50, 51, 0, 4, 8})),
            flopIndexer->getIndex(std::vector<uint8_t>({50, 49, 0, 4, 8}))
    );
}

