#include <gtest/gtest.h>
#include "dragon.hpp"
#include "npc.hpp"
#include "knight.hpp"
#include "princess.hpp"
#include "visitor.hpp"

TEST(npc_test, accept_test) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>("Draco", 0, 30);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>("Lancelot", 10, 20);
    std::shared_ptr<NPC> princess = std::make_shared<Princess>("Aurora", 50, 1);

    ASSERT_TRUE(dragon->opportunity(knight));
    ASSERT_FALSE(knight->opportunity(princess));
    ASSERT_FALSE(princess->opportunity(dragon));
}

TEST(npc_test, is_close_test) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>("Draco", 0, 30);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>("Lancelot", 10, 20);
    std::shared_ptr<NPC> princess = std::make_shared<Princess>("Aurora", 50, 1);

    ASSERT_TRUE(dragon->space_check(knight));
    ASSERT_FALSE(knight->space_check(princess));
    ASSERT_FALSE(princess->space_check(dragon));
}

TEST(visitor_test, visit_test) {
    std::shared_ptr<NPC> dragon = std::make_shared<Dragon>("Draco", 0, 30);
    std::shared_ptr<NPC> knight = std::make_shared<Knight>("Lancelot", 10, 20);
    std::shared_ptr<NPC> princess = std::make_shared<Princess>("Aurora", 50, 1);

    std::shared_ptr<Visitor> dragon_visitor = std::make_shared<DragonV>();
    std::shared_ptr<Visitor> knight_visitor = std::make_shared<KnightV>();
    std::shared_ptr<Visitor> princess_visitor = std::make_shared<PrincessV>();

    ASSERT_FALSE(dragon_visitor->visit(std::static_pointer_cast<Dragon>(dragon)));
    ASSERT_FALSE(knight_visitor->visit(std::static_pointer_cast<Princess>(princess)));
    ASSERT_FALSE(princess_visitor->visit(std::static_pointer_cast<Knight>(knight)));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
