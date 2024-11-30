#pragma once
#include "npc.hpp"
#include "visitor.hpp"

struct Knight : public NPC {
    Knight(const std::string &name, int x, int y);
    Knight(std::istream &is);

    void print() override;

    virtual bool opportunity(const std::shared_ptr<NPC> &attacker) const override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Knight &knight);
};
