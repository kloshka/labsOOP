#pragma once
#include "npc.hpp"
#include "visitor.hpp"

struct Dragon final: public NPC {
    Dragon(const std::string&, int, int);
    Dragon(std::istream&);

    void print() override;

    virtual bool opportunity(const std::shared_ptr<NPC>&) const override;

    void save(std::ostream&) override;

    friend std::ostream &operator<<(std::ostream&, Dragon&);
};