#include "manager.hpp"

int main() {
    npc_set array;

    const std::chrono::seconds time = 30s;
    const int MAX_X{100};
    const int MAX_Y{100};

    std::vector<std::string> names = {"Oliver",  "Emma",      "William",   "Ava",       "James",   "Isabella", "Benjamin",  "Sophia",  "Lucas",  "Mia",
                                      "Henry",   "Charlotte", "Alexander", "Amelia",    "Michael", "Harper",   "Elijah",    "Evelyn",  "Daniel", "Abigail",
                                      "Matthew", "Emily",     "Jackson",   "Elizabeth", "David",   "Sofia",    "Joseph",    "Ella",    "Samuel", "Grace",
                                      "John",    "Chloe",     "Andrew",    "Victoria",  "Jack",    "Lily",     "Ryan",      "Hannah",  "Noah",   "Zoe",
                                      "Anthony", "Penelope",  "Jonathan",  "Nora",      "Joshua",  "Scarlett", "Christian", "Addison", "David",  "Charles"};

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i) array.insert(Factory::CreateNPC(NPCtype(std::rand() % 3 + 1), names[i], std::rand() % MAX_X, std::rand() % MAX_Y));

    std::cout << "Starting list:" << std::endl << array;

    std::thread fight_thread(std::ref(FightManager::get()), (void*)&time);

    std::thread move_thread([&array, MAX_X, MAX_Y, time]() {
        auto start = std::chrono::steady_clock::now();
        while (true) {
            for (std::shared_ptr<NPC> npc : array) {
                if (npc->is_alive()) {
                    int shift_x = std::rand() % (npc->get_move_distance() * 2) - npc->get_move_distance();
                    int shift_y = std::rand() % (npc->get_move_distance() * 2) - npc->get_move_distance();
                    npc->move(shift_x, shift_y, MAX_X, MAX_Y);
                }
            }
            // lets fight
            for (std::shared_ptr<NPC> npc : array)
                for (std::shared_ptr<NPC> other : array)
                    if (other != npc && npc->is_alive() && other->is_alive() && npc->space_check(other)) {
                        FightManager::get().add_event({npc, other});
                    }
            std::this_thread::sleep_for(50ms);
            auto end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= time) {
                break;
            }
        }
    });

    auto start = std::chrono::steady_clock::now();
    while (true) {
        const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid};
        std::array<std::array<char, grid>, grid> fields{std::array<char, grid>{0}};
        for (std::shared_ptr<NPC> npc : array) {
            auto [x, y] = npc->position();
            int i = x / step_x;
            int j = y / step_y;
            if (i >= grid) i = grid - 1;
            if (j >= grid) j = grid - 1;

            if (npc->is_alive()) {
                switch (npc->get_type()) {
                    case DragonT:
                        fields[i][j] = 'D';
                        break;
                    case KnightT:
                        fields[i][j] = 'K';
                        break;
                    case PrincessT:
                        fields[i][j] = 'P';
                        break;

                    default:
                        break;
                }
            }
        }
        {
            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i][j];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(1s);
        auto end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= time) {
            break;
        }
    }

    move_thread.join();
    fight_thread.join();

    std::cout << "Survivors: " << std::endl << array;

    return 0;
}