#include "Database.hpp"
#include "../protocol/RESPSerializer.hpp"

using namespace std;

string Database::execute(const Command& cmd)
{
    string cname;
    for (char c : cmd.name()) cname += toupper(c);

    // --- GET ---
    if (cname == "GET") {
        if (cmd.argc() != 2)
            return RESP::error("ERR wrong number of arguments for GET");

        string key = cmd.arg(1);

        if (isExpired(key)) {
            store_.erase(key);
            expires_.erase(key);
            return RESP::bulkString(""); // nil
        }

        auto it = store_.find(key);
        if (it == store_.end())
            return RESP::bulkString(""); // nil

        return RESP::bulkString(it->second);
    }

    // --- SET key value ---
    if (cname == "SET") {
        if (cmd.argc() != 3)
            return RESP::error("ERR wrong number of arguments for SET");

        string key = cmd.arg(1);
        string value = cmd.arg(2);

        store_[key] = value;
        expires_.erase(key);

        return RESP::simpleString("OK");
    }

    // --- DEL key ---
    if (cname == "DEL") {
        if (cmd.argc() != 2)
            return RESP::error("ERR wrong number of arguments for DEL");

        string key = cmd.arg(1);

        bool removed = (store_.erase(key) > 0);
        expires_.erase(key);

        return RESP::integer(removed ? 1 : 0);
    }

    // --- EXPIRE key seconds ---
    if (cname == "EXPIRE") {
        if (cmd.argc() != 3)
            return RESP::error("ERR wrong number of arguments for EXPIRE");

        string key = cmd.arg(1);
        int seconds = stoi(cmd.arg(2));

        if (store_.find(key) == store_.end())
            return RESP::integer(0);

        long long expireAt = nowMs() + (long long)seconds * 1000;
        expires_[key] = expireAt;

        return RESP::integer(1);
    }

    return RESP::error("ERR unknown command");
}

bool Database::isExpired(const string& key)
{
    auto it = expires_.find(key);
    if (it == expires_.end()) return false;

    return it->second < nowMs();
}

long long Database::nowMs() const
{
    using namespace chrono;
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count();
}
