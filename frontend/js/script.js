async function apiRequest(endpoint, data = null) {
    const options = {};

    if (data !== null) {
        options.method = "POST";
        options.headers = {
            "Content-Type": "application/json"
        };
        options.body = JSON.stringify(data);
    }

    const response = await fetch(endpoint, options);
    const result = await response.json();

    if (!response.ok) {
        throw new Error(result.error || "Request failed");
    }

    return result;
}

function showResult(elementId, data) {
    const element = document.getElementById(elementId);
    const box = document.createElement("div");
    box.className = "result";
    const pre = document.createElement("pre");
    pre.textContent = JSON.stringify(data, null, 2);
    box.appendChild(pre);
    element.replaceChildren(box);
}

async function checkServer() {
    try {
        const result = await apiRequest("/api/health");
        document.getElementById("status").textContent =
            "Server " + result.status;
    } catch (error) {
        document.getElementById("status").textContent =
            "Server connection failed";
    }
}

async function loadAreas() {
    try {
        const data = await apiRequest("/api/areas");
        showResult("areas", data);
    } catch (error) {
        showResult("areas", { error: error.message });
    }
}

async function loadPriority() {
    try {
        const areas = await apiRequest("/api/areas");

        const result = await apiRequest("/api/priority", {
            areas: areas
        });

        showResult("priority", result);
    } catch (error) {
        showResult("priority", { error: error.message });
    }
}

async function findRoute() {
    try {
        const roads = await apiRequest("/api/roads");
        const source = Number(document.getElementById("source").value);

        const result = await apiRequest("/api/route", {
            vertices: roads.vertices,
            roads: roads.roads,
            source: source
        });

        showResult("routes", result);
    } catch (error) {
        showResult("routes", { error: error.message });
    }
}

async function selectReliefActivities() {
    const activities = [
        { name: "Food Distribution", startTime: 1, endTime: 3 },
        { name: "Medical Support", startTime: 2, endTime: 5 },
        { name: "Rescue Coordination", startTime: 4, endTime: 6 },
        { name: "Water Distribution", startTime: 6, endTime: 8 }
    ];

    try {
        const result = await apiRequest("/api/activities", {
            activities: activities
        });

        showResult("activities", result);
    } catch (error) {
        showResult("activities", { error: error.message });
    }
}

async function calculateFractional() {
    const items = [
        { name: "Rice", weight: 10, value: 500 },
        { name: "Water", weight: 5, value: 300 },
        { name: "Medicine", weight: 2, value: 800 },
        { name: "Dry Food", weight: 4, value: 400 }
    ];

    try {
        const result = await apiRequest("/api/fractional", {
            capacity: 15,
            items: items
        });

        showResult("fractional", result);
    } catch (error) {
        showResult("fractional", { error: error.message });
    }
}

async function calculateKnapsack() {
    const items = [
        { name: "Rice", weight: 10, value: 500 },
        { name: "Water", weight: 5, value: 300 },
        { name: "Medicine", weight: 2, value: 800 },
        { name: "Dry Food", weight: 4, value: 400 }
    ];

    try {
        const result = await apiRequest("/api/knapsack", {
            capacity: 15,
            items: items
        });

        showResult("knapsack", result);
    } catch (error) {
        showResult("knapsack", { error: error.message });
    }
}

async function calculateCoins() {
    try {
        const result = await apiRequest("/api/coin-change", {
            amount: 87,
            denominations: [1, 5, 10, 20, 50]
        });

        showResult("coins", result);
    } catch (error) {
        showResult("coins", { error: error.message });
    }
}

checkServer();
