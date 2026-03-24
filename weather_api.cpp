#include "weather_api.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto reqLink = "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&hourly=temperature_2m";

void get_weather_data() {
    auto response = cpr::Get(cpr::Url{reqLink});
    auto weather_data = response.text;
    printf(weather_data.c_str());
}

