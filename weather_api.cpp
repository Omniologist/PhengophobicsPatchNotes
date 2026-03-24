#include "weather_api.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::string reqLink = "https://api.open-meteo.com/v1/forecast?latitude=-34.9287&longitude=138.5986&current=temperature_2m,apparent_temperature&forecast_days=1";

json get_weather_data() {
    auto response = cpr::Get(cpr::Url{reqLink});
    return json::parse(response.text);
}

