#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Equity_Data
{
    double lastTradedPrice;
    std::uint64_t lastDayVolume;
};

struct Bond_Data
{
    double lastTradedPrice;
    double bondYield;
};

extern std::unordered_map<std::uint64_t, Equity_Data> equity_dataMap;
extern std::unordered_map<std::uint64_t, Bond_Data> bond_dataMap;

class Publisher
{
    
public:
    virtual void update_data(std::uint64_t instrumentId, double lastTradedPrice, double additionalData) = 0;
    virtual void subscribe(std::uint64_t subscriberId) = 0;
    virtual std::string get_data(std::uint64_t instrumentId) = 0;
    virtual ~Publisher() = default;
};

class EquityPublisher : public Publisher
{
    std::unordered_set<std::uint64_t> subscribers_; // Holds the set of all its subscribers by ID

public:
    void update_data(std::uint64_t instrumentId, double lastTradedPrice, double lastDayVolume) override;
    void subscribe(std::uint64_t subscriberId) override;
    std::string get_data(std::uint64_t instrumentId) override;
};

class BondPublisher : public Publisher
{
    std::unordered_set<std::uint64_t> subscribers_; // Holds the set of all its subscribers by ID

public:
    void update_data(std::uint64_t instrumentId, double lastTradedPrice, double bondYield) override;
    void subscribe(std::uint64_t subscriberId) override;
    std::string get_data(std::uint64_t instrumentId) override;
};