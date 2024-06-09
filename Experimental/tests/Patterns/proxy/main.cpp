#include <iostream>
#include <list>

std::list<int> get_cloud_data() {
    return {1, 5, 10, 20, 35, 50};
}

class Database {

public:
    std::list<int> l;

public:
    void fetch_from_cloud() {
        this->l = get_cloud_data();
    }
};

class DatabaseProxy : public Database {
    Database* db;

public:
    explicit DatabaseProxy(Database* proxy_db) : db(proxy_db) {
    }
    std::list<int>& fetch_from_cloud() {
        if (db->l.empty()) {
            db->fetch_from_cloud();
            std::cout << "DB is fetched from cloud...\n";
        } else {
            std::cout << "DB is already present...\n";
        }
        return db->l;
    }
};


int main(int argc, const char* argv[]) {

    Database og_db;
    DatabaseProxy db(&og_db);
    std::list<int>& l = db.fetch_from_cloud();

    for (auto& el : l) {
        std::cout << el << " ";
    }
    std::cout << "\n";

    std::list<int>& l2 = db.fetch_from_cloud();
    std::list<int>& l3 = db.fetch_from_cloud();


    return 0;
}