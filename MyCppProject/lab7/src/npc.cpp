#include "npc.hpp"
#include <shared_mutex>

NPC::NPC(NPCtype j, const std::string &_name, int _x, int _y) : type(j), name(_name), x(_x), y(_y) {} //инициализации

NPC::NPC(NPCtype j, std::istream &is) : type(j){ // чтение из потока ( можно пото мдописать люой соответсвкюзий файд)
    is >> name;
    is >> x;
    is >> y;
}

void NPC::subscribe (const std::shared_ptr<FightObserver> &observer){
    observers.push_back(observer);
}

void NPC::fight_notify_result(const std::shared_ptr<NPC> defender, bool winner) const{// со стороны нападающего
    for (auto &o : observers)
    o->res_fight(std::const_pointer_cast<NPC>(shared_from_this()), defender, winner);
}

bool NPC::space_check(const std::shared_ptr<NPC>& other){
        auto [other_x, other_y] = other->position();

    std::lock_guard<std::mutex> lck(mtx);
    if ((std::pow(x - other_x, 2) + std::pow(y - other_y, 2)) <= std::pow(kill_distance, 2))
        return true;
    else
        return false;
}


NPCtype NPC::get_type() { 
    std::lock_guard<std::mutex> lck(mtx);
    return type; }

std::pair<int, int> NPC::position() { 
    std::lock_guard<std::mutex> lck(mtx);
    return{x, y};}

void NPC::save(std::ostream &os) {
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc){
    os<<npc.name <<" " << "{x:" << npc.x << ", y:" << npc.y << "}";
    return os;
}

int NPC::get_move_distance() {
    std::lock_guard<std::mutex> lck(mtx);
    return move_distance;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);
    if (shift_x > move_distance || shift_y > move_distance) {
        throw std::runtime_error("Max move distance is " + move_distance);
    }
    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

bool NPC::is_alive() {
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::must_die() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

int NPC::throw_cost() const noexcept {
    return std::rand() % 6 + 1;
}