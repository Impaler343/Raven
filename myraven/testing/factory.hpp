#pragma once
#include <memory>
#include "publisher.hpp"
#include "subscriber.hpp"

class Factory {
public:
    static std::shared_ptr<Publisher> create_instrument(std::uint64_t instrumentId);
    static std::unique_ptr<Subscriber> create_subscriber(char type);
};