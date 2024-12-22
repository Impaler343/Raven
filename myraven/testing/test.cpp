#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "factory.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

int main()
{
    std::unordered_map<std::uint64_t, std::shared_ptr<Publisher>> instruments; //Mapping of all instruments to their respective publisher types
    std::unordered_map<std::uint64_t, std::unique_ptr<Subscriber>> subscribers; //Mapping of all subscribers to their respective subscriber types

    std::string line;
    int numLines;
    std::cin >> numLines;
    std::cin.ignore(); // Ignore the newline after the number of lines

    for (int i = 0; i < numLines; ++i)
    {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        char type;
        iss >> type;

        if (type == 'P')
        {
            std::uint64_t instrumentId;
            double lastTradedPrice, additionalData;
            iss >> instrumentId >> lastTradedPrice >> additionalData;

            if (instruments.find(instrumentId) == instruments.end())
            {
                instruments[instrumentId] = Factory::create_instrument(instrumentId);
            }
            instruments[instrumentId]->update_data(instrumentId, lastTradedPrice, additionalData);
        }
        else if (type == 'S')
        {
            char subscriberType;
            std::uint64_t subscriberId, instrumentId;
            std::string action;
            iss >> subscriberType >> subscriberId >> action >> instrumentId;

            if (subscribers.find(subscriberId) == subscribers.end())
            {
                subscribers[subscriberId] = Factory::create_subscriber(subscriberType);
            }

            if (action == "subscribe")
            {
                if (instruments.find(instrumentId) == instruments.end())
                {
                    std::cout << subscriberType << ", " << subscriberId << ", "
                                << instrumentId << ", invalid_request" << std::endl;
                    continue;
                }
                subscribers[subscriberId]->subscribe(instruments[instrumentId]);
            }
            else if (action == "get_data")
            {
                if (subscribers[subscriberId]->get_publisher() == nullptr)
                {
                    std::cout << subscriberType << ", " << subscriberId << ", "
                                << instrumentId << ", invalid_request" << std::endl;
                    continue;
                }
                std::string data = subscribers[subscriberId]->get_data(instrumentId);
                std::cout << subscriberType << ", " << subscriberId << ", " << instrumentId << ", " << data << std::endl;
            }
        }
    }

    return 0;
}