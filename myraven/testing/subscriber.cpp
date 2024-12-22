#include "subscriber.hpp"

void PaidSubscriber::subscribe(std::shared_ptr<Publisher> publisher)
{
    publisher_ = publisher;
    publisher->subscribe(subscriberId_);
}

void FreeSubscriber::subscribe(std::shared_ptr<Publisher> publisher)
{
    publisher_ = publisher;
    publisher->subscribe(subscriberId_);
}

std::string FreeSubscriber::get_data(std::uint64_t instrumentId)
{
    if (requestCount_ >= maxRequests_)
    {
        return "Pay to make more requests";
    }
    ++requestCount_;
    return publisher_->get_data(instrumentId);
}

std::string PaidSubscriber::get_data(std::uint64_t instrumentId)
{
    return publisher_->get_data(instrumentId);
}
