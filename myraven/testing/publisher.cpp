#include "publisher.hpp"

std::unordered_map<std::uint64_t, Equity_Data> equity_dataMap;
std::unordered_map<std::uint64_t, Bond_Data> bond_dataMap;

void EquityPublisher::update_data(std::uint64_t instrumentId, double lastTradedPrice, double lastDayVolume)
{
    equity_dataMap[instrumentId] = { lastTradedPrice, static_cast<std::uint64_t>(lastDayVolume) };
}

void EquityPublisher::subscribe(std::uint64_t subscriberId)
{
    subscribers_.insert(subscriberId);
}

std::string EquityPublisher::get_data(std::uint64_t instrumentId)
{
    if (equity_dataMap.find(instrumentId) == equity_dataMap.end())
    {
        return "invalid_request";
    }
    return std::to_string(equity_dataMap[instrumentId].lastTradedPrice) + ", " + std::to_string(equity_dataMap[instrumentId].lastDayVolume);
}

void BondPublisher::update_data(std::uint64_t instrumentId, double lastTradedPrice, double bondYield)
{
    bond_dataMap[instrumentId] = { lastTradedPrice, bondYield };
}

void BondPublisher::subscribe(std::uint64_t subscriberId)
{
    subscribers_.insert(subscriberId);
}

std::string BondPublisher::get_data(std::uint64_t instrumentId)
{
    if (bond_dataMap.find(instrumentId) == bond_dataMap.end())
    {
        return "invalid_request";
    }
    return std::to_string(bond_dataMap[instrumentId].lastTradedPrice) + ", " + std::to_string(bond_dataMap[instrumentId].bondYield);
}