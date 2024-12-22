#include "factory.hpp"

std::shared_ptr<Publisher> Factory::create_instrument(std::uint64_t instrumentId)
{
    if (instrumentId < 1000)
    {
        return std::make_shared<EquityPublisher>();
    }
    else
    {
        return std::make_shared<BondPublisher>();
    }
    // Add more types as needed
    return nullptr;
}

std::unique_ptr<Subscriber> Factory::create_subscriber(char type)
{
    if (type == 'P')
    {
        return std::make_unique<PaidSubscriber>();
    }
    else if (type == 'F')
    {
        return std::make_unique<FreeSubscriber>();
    }
    // Add more types as needed
    return nullptr;
}