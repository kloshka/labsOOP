#pragma once
#include "npc.hpp"
#include "visitor.hpp"

struct Princess : public NPC {
    Princess(const std::string&, int, int);
    Princess(std::istream&);

    void print() override;

    virtual bool opportunity(const std::shared_ptr<NPC>&) const override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream&, Princess&);
};