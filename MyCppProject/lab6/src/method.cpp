#include "method.hpp"

void save(const npc_set &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

npc_set load(const std::string &filename) {
    npc_set result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(Factory::CreateNPC(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

npc_set fight(const npc_set &array, size_t distance) {
    npc_set dead_list;
    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                (attacker->space_check(defender, distance))) {
                bool success = defender->opportunity(attacker);
                if (success)
                    dead_list.insert(defender);
            }
    return dead_list;
}

std::ostream &operator<<(std::ostream &os, const npc_set &array) {
    for (auto &n : array)
        n->print();
    return os;
}