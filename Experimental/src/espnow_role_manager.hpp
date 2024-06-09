#ifndef ESPNOW_ROLE_MANAGER
#define ESPNOW_ROLE_MANAGER

#include <functional>

class EspNowRoleManager {
private:
    std::function<void(bool, bool)> _callback;
    bool _master;
    bool _slave;

    void on_role_change(bool master, bool slave);

public:
    EspNowRoleManager(std::function<void(bool, bool)>&& callback, bool master, bool slave)
        : _callback(std::move(callback))
        , _master(master)
        , _slave(slave) {
    }

    void set_slave() {
        this->_slave = true;
        this->_master = false;
        this->_callback(this->_master, this->_slave);
    }

    void set_master() {
        this->_slave = false;
        this->_master = true;
        this->_callback(this->_master, this->_slave);
    }

    bool is_slave() {
        return this->_slave;
    }

    bool is_master() {
        return this->_master;
    }
};

#endif