#pragma once
#include <cstring>
#include <iostream>
#include <cmath>
#include <set>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <shared_mutex>

class NPC;
class Princess;
class Knight;
class Dragon;

using npc_set = std::set<std::shared_ptr<NPC>>; //using -- псевдони, чтобы не тазить эту целую махину через весь код shared_ptr- уничтожим, когда не останется указателей, сам слежит за жизнью
enum NPCtype {Somebody, PrincessT, KnightT, DragonT, Max }; //enum - тип перечисления

struct FightObserver {
public:
    virtual void res_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC>, bool) =0;
};

class NPC : public std::enable_shared_from_this<NPC>{// похволяем передавать на себя ссылку
protected:
    std::mutex mtx;

    NPCtype type;
    std::string name{""};
    int x{0};
    int y{0};
    bool alive{true};
    int move_distance{0};
    int kill_distance{0};
    std::vector<std::shared_ptr<FightObserver>> observers;// вектор с объуктами слкдящими за боями, это суть Observer. указатаели гарантируют что когда будет не нужно удалится

public:

    NPC(NPCtype, const std::string&, int _x, int _y);
    NPC(NPCtype, std::istream&);

    NPCtype get_type();

    virtual bool opportunity(const std::shared_ptr<NPC>&) const = 0;
    void subscribe(const std::shared_ptr<FightObserver>&);
    void fight_notify_result(const std::shared_ptr<NPC>, bool ) const;
    virtual bool space_check(const std::shared_ptr<NPC>&) ;
    virtual void print() = 0;
    virtual void save(std::ostream&);
    std::pair <int, int> position();
    friend std::ostream &operator<<(std::ostream&, NPC&);

    int get_move_distance();
    void move(int, int, int, int);
    bool is_alive();
    void must_die();
    int throw_cost() const noexcept;
};