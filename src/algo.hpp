#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>

class WeightedPreferenceBiddingAlgorithm {
private:
    std::vector<std::string> platforms;
    std::vector<std::string> restaurants;

    // Preference weights (higher = more preferred)
    std::map<std::string, std::map<std::string, int>> platform_weights;
    std::map<std::string, std::map<std::string, int>> restaurant_weights;

    // Platform budgets for bidding (simulates market competition)
    std::map<std::string, double> platform_budgets;

    // Restaurant capacities (can handle multiple partnerships with weight limits)
    std::map<std::string, int> restaurant_capacities;

    // Current partnerships and satisfaction scores
    std::map<std::string, std::string> final_matches;
    std::map<std::string, double> satisfaction_scores;

    void initializeWeights();

public:
    WeightedPreferenceBiddingAlgorithm() {
        initializeData();
    }

    void initializeData();

    // Core Algorithm functions (contain internal printing)
    double calculateBiddingScore(const std::string& platform, const std::string& restaurant);
    void runWeightedPreferenceBiddingAlgorithm();
    void analyzeStability();

    // === PUBLIC SETTERS/GETTERS FOR TEST_F MANIPULATION ===
    size_t getPlatformCount() const { return platforms.size(); }
    size_t getRestaurantCount() const { return restaurants.size(); }
    std::map<std::string, std::string> getFinalMatches() const { return final_matches; }
    std::map<std::string, double> getSatisfactionScores() const { return satisfaction_scores; }
    std::map<std::string, double> getPlatformBudgets() const { return platform_budgets; }
    std::vector<std::string> getPlatforms() const { return platforms; }
    std::vector<std::string> getRestaurants() const { return restaurants; }

    // Setters for scenario creation
    void setPlatformBudget(const std::string& platform, double budget) {
        platform_budgets[platform] = budget;
    }
    void setRestaurantCapacity(const std::string& restaurant, int capacity) {
        restaurant_capacities[restaurant] = capacity;
    }
    void setPlatformWeight(const std::string& platform, const std::string& restaurant, int weight) {
        platform_weights[platform][restaurant] = weight;
    }
    void setRestaurantWeight(const std::string& restaurant, const std::string& platform, int weight) {
        restaurant_weights[restaurant][platform] = weight;
    }
    // ==========================================================
};