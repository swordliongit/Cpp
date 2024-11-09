#ifndef ESPNOW_ROLE_MANAGER
#define ESPNOW_ROLE_MANAGER
/*
Singleton Class
*/

#include <functional>
#include <array>
#include <vector>

class EspNowRoleManager {
  private:
    std::function<void(bool, bool)> _callback;
    bool _master;
    bool _slave;
    bool _master_subscribed;
    bool _should_update;
    bool _is_action_set;
    bool _first_update_required;
    EspNowRoleManager(std::function<void(bool, bool)>&& callback, bool master, bool slave) {}
    EspNowRoleManager(const EspNowRoleManager& role_manager) = delete;
    EspNowRoleManager& operator=(const EspNowRoleManager& role_manager) = delete;

  public:
    bool is_pattern;
    std::vector<std::array<uint8_t, 6>> broadcast_addresses;
    std::vector<String> display_texts;
    std::vector<String> animation_list;
    std::vector<String> custom_text_list;
    String pattern_animation;
    std::vector<std::vector<int>> pattern;

    static EspNowRoleManager& get_instance()
    {
        static EspNowRoleManager instance(nullptr, false, false);
        return instance;
    }

    static void init(std::function<void(bool, bool)>&& callback, bool master, bool slave)
    {
        EspNowRoleManager& instance = get_instance();
        instance._callback = std::move(callback);
        instance._master = master;
        instance._slave = slave;
    }

    void set_slave()
    {
        if (!is_slave()) {
            _slave = true;
            _master = false;
            _callback(_master, _slave);
            // roleChangeRequested = true;
            // newMasterRole = false;
        }
    }

    void set_master()
    {
        if (!is_master()) {
            _slave = false;
            _master = true;
            _callback(_master, _slave);
            // roleChangeRequested = true;
            // newMasterRole = true;
        }
    }

    bool is_slave()
    {
        return _slave;
    }

    bool is_master()
    {
        return _master;
    }

    void set_cloud_connected()
    {
        _master_subscribed = true;
    }

    bool is_cloud_connected()
    {
        return _master_subscribed;
    }

    void set_update_required(bool state)
    {
        _should_update = state;
    }

    bool is_update_required()
    {
        return _should_update;
    }

    void set_action()
    {
        _is_action_set = true;
    }

    bool is_action_set()
    {
        return _is_action_set;
    }

    bool set_first_update_required(bool required)
    {
        _first_update_required = required;
    }

    bool first_update_required()
    {
        return _first_update_required;
    }
};

#endif