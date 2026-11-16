#include "crow.h"
#include "nlohmann/json.hpp"

#include "../include/common.h"
#include "../algorithms/priority.h"
#include "../algorithms/graph.h"
#include "../algorithms/activity.h"
#include "../algorithms/fractional.h"
#include "../algorithms/knapsack01.h"
#include "../algorithms/coin_change.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using json = nlohmann::json;

std::string readFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

json readJson(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return json::array();
    }

    json data;
    file >> data;

    return data;
}

crow::response jsonResponse(const json& data, int status = 200) {
    crow::response response(status, data.dump());
    response.set_header("Content-Type", "application/json");
    return response;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([] {
        std::string page =
            readFile(std::string(PROJECT_FRONTEND_DIR) + "/index.html");

        if (page.empty()) {
            return crow::response(404, "index.html not found");
        }

        crow::response response(page);
        response.set_header("Content-Type", "text/html");
        return response;
    });

    CROW_ROUTE(app, "/style.css")([] {
        std::string css =
            readFile(std::string(PROJECT_FRONTEND_DIR) + "/css/style.css");

        crow::response response(css);
        response.set_header("Content-Type", "text/css");
        return response;
    });

    CROW_ROUTE(app, "/script.js")([] {
        std::string js =
            readFile(std::string(PROJECT_FRONTEND_DIR) + "/js/script.js");

        crow::response response(js);
        response.set_header("Content-Type", "application/javascript");
        return response;
    });

    CROW_ROUTE(app, "/api/health")([] {
        return jsonResponse({{"status", "running"}});
    });

    CROW_ROUTE(app, "/api/areas")([] {
        return jsonResponse(
            readJson(std::string(PROJECT_DATA_DIR) + "/areas.json")
        );
    });

    CROW_ROUTE(app, "/api/roads")([] {
        return jsonResponse(
            readJson(std::string(PROJECT_DATA_DIR) + "/roads.json")
        );
    });

    CROW_ROUTE(app, "/api/supplies")([] {
        return jsonResponse(
            readJson(std::string(PROJECT_DATA_DIR) + "/supplies.json")
        );
    });

    CROW_ROUTE(app, "/api/priority")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);
            std::vector<Area> areas;

            for (const auto& item : input.at("areas")) {
                areas.push_back({
                    item.at("id").get<int>(),
                    item.at("name").get<std::string>(),
                    item.at("affectedPeople").get<int>(),
                    item.at("urgency").get<int>()
                });
            }

            auto result = prioritizeAreas(areas);
            json output = json::array();

            for (const auto& area : result) {
                output.push_back({
                    {"id", area.id},
                    {"name", area.name},
                    {"affectedPeople", area.affectedPeople},
                    {"urgency", area.urgency}
                });
            }

            return jsonResponse(output);
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid priority input"}}, 400);
        }
    });

    CROW_ROUTE(app, "/api/route")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);

            int vertices = input.at("vertices").get<int>();
            int source = input.at("source").get<int>();

            if (vertices <= 0 || vertices > 1000) {
                return jsonResponse({{"error", "Invalid vertex count"}}, 400);
            }

            Graph graph(vertices);

            for (const auto& road : input.at("roads")) {
                bool added = graph.addRoad(
                    road.at("from").get<int>(),
                    road.at("to").get<int>(),
                    road.at("distance").get<int>()
                );

                if (!added) {
                    return jsonResponse({{"error", "Invalid road"}}, 400);
                }
            }

            auto distances = graph.dijkstra(source);
            json output = json::array();

            for (int i = 0; i < vertices; i++) {
                output.push_back({
                    {"areaId", i},
                    {"distance",
                     distances[i] == std::numeric_limits<int>::max()
                         ? -1 : distances[i]}
                });
            }

            return jsonResponse(output);
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid route input"}}, 400);
        }
    });

    CROW_ROUTE(app, "/api/activities")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);
            std::vector<Activity> activities;

            for (const auto& item : input.at("activities")) {
                activities.push_back({
                    item.at("name").get<std::string>(),
                    item.at("startTime").get<int>(),
                    item.at("endTime").get<int>()
                });
            }

            auto result = selectActivities(activities);
            json output = json::array();

            for (const auto& activity : result) {
                output.push_back({
                    {"name", activity.name},
                    {"startTime", activity.startTime},
                    {"endTime", activity.endTime}
                });
            }

            return jsonResponse(output);
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid activity input"}}, 400);
        }
    });

    CROW_ROUTE(app, "/api/fractional")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);
            std::vector<FractionalItem> items;

            for (const auto& item : input.at("items")) {
                items.push_back({
                    item.at("name").get<std::string>(),
                    item.at("weight").get<double>(),
                    item.at("value").get<double>()
                });
            }

            auto result = fractionalKnapsack(
                input.at("capacity").get<double>(),
                items
            );

            return jsonResponse({
                {"totalValue", result.totalValue},
                {"usedWeight", result.usedWeight}
            });
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid fractional input"}}, 400);
        }
    });

    CROW_ROUTE(app, "/api/knapsack")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);
            std::vector<KnapsackItem> items;

            for (const auto& item : input.at("items")) {
                items.push_back({
                    item.at("name").get<std::string>(),
                    item.at("weight").get<int>(),
                    item.at("value").get<int>()
                });
            }

            auto result = knapsack01(
                input.at("capacity").get<int>(),
                items
            );

            return jsonResponse({
                {"totalValue", result.totalValue},
                {"totalWeight", result.totalWeight},
                {"selectedItems", result.selectedItems}
            });
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid knapsack input"}}, 400);
        }
    });

    CROW_ROUTE(app, "/api/coin-change")
        .methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        try {
            json input = json::parse(req.body);

            auto result = coinChange(
                input.at("amount").get<int>(),
                input.at("denominations").get<std::vector<int>>()
            );

            return jsonResponse({
                {"possible", result.possible},
                {"minimumCoins", result.minimumCoins},
                {"coinsUsed", result.coinsUsed}
            });
        }
        catch (...) {
            return jsonResponse({{"error", "Invalid coin change input"}}, 400);
        }
    });

    app.port(18080).multithreaded().run();
}
