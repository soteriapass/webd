#pragma once

#include <string>
#include <map>

class conf
{
public:
    conf(const std::string& conf_path);
    conf();

    const std::string get_authentication_address_and_port() const;
    const std::string get_user_mangement_address_and_port() const;
    const std::string get_password_manager_address_and_port() const;
    const std::string get_server_ca_file() const { std::string value; get_key_value("ServerCA", value); return value; }
    const std::string get_base_server_path() const { return "http://10.0.0.150:9090"; }
    const std::string get_log_file() const { return "pswmgr-webd.log"; }

    bool get_key_value(const std::string& key, std::string& value) const
    {
        auto it = m_Values.find(key);
        if(it != m_Values.end())
        {
            value = it->second;
            return true;
        }
        return false;
    }
private:
    std::map<std::string, std::string> m_Values;
};
