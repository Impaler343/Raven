#pragma once
#include "publisher.hpp"
#include <cstdint>
#include <string>
#include <memory>

class Subscriber
{
protected:
    std::uint64_t subscriberId_;
    std::uint64_t requestCount_ = 0;
    std::shared_ptr<Publisher> publisher_ = nullptr;

public:
    virtual void subscribe(std::shared_ptr<Publisher> publisher) = 0;
    virtual std::string get_data(std::uint64_t instrumentId) = 0;
    std::shared_ptr<Publisher> get_publisher() { return publisher_; }
    virtual ~Subscriber() = default;
};

class PaidSubscriber : public Subscriber
{
public:
    void subscribe(std::shared_ptr<Publisher> publisher) override;
    std::string get_data(std::uint64_t instrumentId) override;
};

class FreeSubscriber : public Subscriber
{
    static constexpr std::uint64_t maxRequests_ = 100;

public:
    void subscribe(std::shared_ptr<Publisher> publisher) override;
    std::string get_data(std::uint64_t instrumentId) override;
};