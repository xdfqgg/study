#include "message.hpp"

#include <fmt/format.h>
#include <spdlog/spdlog.h>

std::string make_message(const std::string &name)
{
    const auto message = fmt::format("Hello, {}!", name);
    spdlog::info("created message for {}", name);
    return message;
}
