#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream>
#include <thread>

#include "dragon.hpp"
#include "factory.hpp"
#include "npc.hpp"
#include "princess.hpp"
#include "knight.hpp"

using namespace std::chrono_literals;
std::mutex print_mutex;

void save(const npc_set& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& n : array) n->save(fs);
    fs.flush();
    fs.close();
}

npc_set load(const std::string& filename) {
    npc_set result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) result.insert(Factory::CreateNPC(is));
        is.close();
    } else
        throw std::runtime_error("loading from file error");
    return result;
}

std::ostream& operator<<(std::ostream& os, const npc_set& array) {
    for (auto& n : array) n->print();
    return os;
}

struct print : std::stringstream {
    ~print() {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << this->str();
        std::cout.flush();
    }
};

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager final {
private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()(void* args) {
        auto time = (std::chrono::seconds*)args;
        auto start = std::chrono::steady_clock::now();
        while (true) {
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mtx);
                if (!events.empty()) {
                    event = events.back();
                    events.pop();
                }
            }
            if (event) {
                //
                if (event->attacker->is_alive() && event->defender->is_alive() && (event->attacker->throw_cost() > event->defender->throw_cost()) &&
                    event->defender->opportunity(event->attacker)) {
                    event->defender->must_die();
                }

            } else {
                std::this_thread::sleep_for(100ms);
            }
            auto end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= *time) {
                break;
            }
        }
    }
};
