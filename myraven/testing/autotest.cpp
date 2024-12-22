#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

auto generate_publisher_update_message = [] {
  std::string msg = "P ";
  std::uint64_t instrumentId = rand() % 2000;
  msg += std::to_string(instrumentId) + " ";
  msg += std::to_string(rand()) + " ";
  if (instrumentId >= 1000)
    // Bond update
    // bond yield is percentage (< 100)
    msg += std::to_string(static_cast<double>(rand() % 10000) / 100);
  else
    // Equity update
    // last day volume
    msg += std::to_string(rand());

  msg += "\n";
  return msg;
};

auto generate_subscribe_message = [] {
  std::string msg = "S ";
  if(rand() % 2)
      msg += "F ";
  else
      msg += "P ";
  std::uint64_t subscriberId = rand();
  msg += std::to_string(subscriberId) + " ";
  msg += "subscribe ";
  msg += std::to_string(rand() % 2000) + "\n";

  return msg;
};

auto generate_get_data_message = [] {
  std::string msg = "S ";
  if(rand() % 2)
      msg += "F ";
  else
      msg += "P ";
  std::uint64_t subscriberId = rand();
  msg += std::to_string(subscriberId) + " ";
  msg += "get_data ";
  msg += std::to_string(rand() % 2000) + "\n";

  return msg;
};

int main() {
  std::vector<std::string> messages;
  messages.push_back("1000\n");
  for (int i = 0; i < 1000; ++i) {
    if (rand() % 2)
      messages.push_back(generate_publisher_update_message());
    else if (rand() % 2)
      messages.push_back(generate_subscribe_message());
    else
      messages.push_back(generate_get_data_message());
  }

  std::ofstream outfile("../build/input_test.txt");
  if (!outfile)
  {
      std::cerr << "Error opening file for writing" << std::endl;
      return 1;
  }

  for (const auto& msg : messages)
  {
      outfile << msg;
  }

  outfile.close();
  return 0;
}