#include "algo.hpp"
#include <chrono>

// Re-implementing initializeData with the new 8x10 large dataset
void WeightedPreferenceBiddingAlgorithm::initializeData() {
    // New large dataset: 8 Platforms and 10 Restaurants
    platforms = { "GrabFood", "Foodpanda", "Deliveroo", "WhyQ", "honestbee", "Oddle", "UberEats", "FoodLion" };
    restaurants = { "PastaExpress_Orchard", "ChiliCrab_Marina", "BakKutTeh_Chinatown",
                   "ChickenRice_Bugis", "LaksaKing_Katong", "SatayGrill_Clarke",
                   "DimSum_Tanjong", "NasiLemak_Geylang", "RotiPrata_Little", "ZiChar_Toa" };

    // Initialize platform budgets (simulating market strength)
    platform_budgets["GrabFood"] = 1500.0;
    platform_budgets["Foodpanda"] = 1400.0;
    platform_budgets["Deliveroo"] = 1200.0;
    platform_budgets["UberEats"] = 1100.0;
    platform_budgets["honestbee"] = 900.0;
    platform_budgets["WhyQ"] = 800.0;
    platform_budgets["Oddle"] = 700.0;
    platform_budgets["FoodLion"] = 600.0;

    // Initialize restaurant capacities (simulating popularity/size)
    restaurant_capacities["ChiliCrab_Marina"] = 100;
    restaurant_capacities["PastaExpress_Orchard"] = 95;
    restaurant_capacities["DimSum_Tanjong"] = 90;
    restaurant_capacities["LaksaKing_Katong"] = 85;
    restaurant_capacities["ChickenRice_Bugis"] = 80;
    restaurant_capacities["SatayGrill_Clarke"] = 75;
    restaurant_capacities["NasiLemak_Geylang"] = 70;
    restaurant_capacities["BakKutTeh_Chinatown"] = 65;
    restaurant_capacities["RotiPrata_Little"] = 60;
    restaurant_capacities["ZiChar_Toa"] = 55;

    // Convert preferences to weighted scores
    initializeWeights();
}

void WeightedPreferenceBiddingAlgorithm::initializeWeights() {
    // P-side preferences (10 = most preferred, 1 = least preferred)
    std::map<std::string, std::vector<std::string>> platform_prefs = {
        {"GrabFood", {"ChiliCrab_Marina", "PastaExpress_Orchard", "LaksaKing_Katong", "DimSum_Tanjong", "ChickenRice_Bugis", "SatayGrill_Clarke", "NasiLemak_Geylang", "BakKutTeh_Chinatown", "RotiPrata_Little", "ZiChar_Toa"}},
        {"Foodpanda", {"PastaExpress_Orchard", "ChiliCrab_Marina", "ChickenRice_Bugis", "LaksaKing_Katong", "DimSum_Tanjong", "SatayGrill_Clarke", "NasiLemak_Geylang", "BakKutTeh_Chinatown", "ZiChar_Toa", "RotiPrata_Little"}},
        {"Deliveroo", {"LaksaKing_Katong", "PastaExpress_Orchard", "DimSum_Tanjong", "ChiliCrab_Marina", "SatayGrill_Clarke", "ChickenRice_Bugis", "NasiLemak_Geylang", "RotiPrata_Little", "BakKutTeh_Chinatown", "ZiChar_Toa"}},
        {"WhyQ", {"ChickenRice_Bugis", "BakKutTeh_Chinatown", "RotiPrata_Little", "NasiLemak_Geylang", "LaksaKing_Katong", "DimSum_Tanjong", "ChiliCrab_Marina", "PastaExpress_Orchard", "SatayGrill_Clarke", "ZiChar_Toa"}},
        {"honestbee", {"DimSum_Tanjong", "LaksaKing_Katong", "ChiliCrab_Marina", "PastaExpress_Orchard", "SatayGrill_Clarke", "ChickenRice_Bugis", "NasiLemak_Geylang", "BakKutTeh_Chinatown", "RotiPrata_Little", "ZiChar_Toa"}},
        {"Oddle", {"BakKutTeh_Chinatown", "ZiChar_Toa", "RotiPrata_Little", "NasiLemak_Geylang", "ChickenRice_Bugis", "LaksaKing_Katong", "PastaExpress_Orchard", "ChiliCrab_Marina", "DimSum_Tanjong", "SatayGrill_Clarke"}},
        {"UberEats", {"ChiliCrab_Marina", "DimSum_Tanjong", "SatayGrill_Clarke", "PastaExpress_Orchard", "LaksaKing_Katong", "ChickenRice_Bugis", "NasiLemak_Geylang", "RotiPrata_Little", "BakKutTeh_Chinatown", "ZiChar_Toa"}},
        {"FoodLion", {"SatayGrill_Clarke", "NasiLemak_Geylang", "RotiPrata_Little", "ZiChar_Toa", "BakKutTeh_Chinatown", "ChickenRice_Bugis", "LaksaKing_Katong", "PastaExpress_Orchard", "ChiliCrab_Marina", "DimSum_Tanjong"}}
    };

    // Convert P-prefs to weights (10-1)
    for (const auto& platform : platforms) {
        for (int i = 0; i < platform_prefs[platform].size(); ++i) {
            platform_weights[platform][platform_prefs[platform][i]] = restaurants.size() - i;
        }
    }

    // R-side preferences (8 = most preferred, 1 = least preferred)
    std::map<std::string, std::vector<std::string>> restaurant_prefs = {
        {"PastaExpress_Orchard", {"Deliveroo", "GrabFood", "Foodpanda", "UberEats", "honestbee", "Oddle", "WhyQ", "FoodLion"}},
        {"ChiliCrab_Marina", {"GrabFood", "Foodpanda", "UberEats", "honestbee", "Deliveroo", "Oddle", "WhyQ", "FoodLion"}},
        {"BakKutTeh_Chinatown", {"Oddle", "WhyQ", "GrabFood", "Foodpanda", "Deliveroo", "UberEats", "honestbee", "FoodLion"}},
        {"ChickenRice_Bugis", {"Foodpanda", "GrabFood", "WhyQ", "honestbee", "Deliveroo", "UberEats", "Oddle", "FoodLion"}},
        {"LaksaKing_Katong", {"GrabFood", "Deliveroo", "honestbee", "Foodpanda", "WhyQ", "UberEats", "Oddle", "FoodLion"}},
        {"SatayGrill_Clarke", {"FoodLion", "UberEats", "honestbee", "Deliveroo", "GrabFood", "Foodpanda", "WhyQ", "Oddle"}},
        {"DimSum_Tanjong", {"honestbee", "UberEats", "Deliveroo", "Foodpanda", "GrabFood", "WhyQ", "Oddle", "FoodLion"}},
        {"NasiLemak_Geylang", {"WhyQ", "FoodLion", "Oddle", "honestbee", "Deliveroo", "Foodpanda", "GrabFood", "UberEats"}},
        {"RotiPrata_Little", {"Oddle", "FoodLion", "WhyQ", "Deliveroo", "honestbee", "Foodpanda", "GrabFood", "UberEats"}},
        {"ZiChar_Toa", {"Oddle", "FoodLion", "WhyQ", "honestbee", "Deliveroo", "Foodpanda", "GrabFood", "UberEats"}}
    };

    // Convert R-prefs to weights (8-1)
    for (const auto& restaurant : restaurants) {
        for (int i = 0; i < restaurant_prefs[restaurant].size(); ++i) {
            restaurant_weights[restaurant][restaurant_prefs[restaurant][i]] = platforms.size() - i;
        }
    }
}

// Core bidding score formula
double WeightedPreferenceBiddingAlgorithm::calculateBiddingScore(const std::string& platform, const std::string& restaurant) {
    // Formula: Score = sqrt(PlatformPref × RestaurantPref) × (Budget/Capacity) × 10
    double platform_pref = platform_weights[platform][restaurant];
    double restaurant_pref = restaurant_weights[restaurant][platform];
    double budget_factor = platform_budgets[platform] / 1500.0; // Normalize budget using max budget (1500)
    double capacity_req = restaurant_capacities[restaurant] / 100.0; // Normalize capacity using max capacity (100)

    double mutual_preference = std::sqrt(platform_pref * restaurant_pref);
    double economic_factor = budget_factor / capacity_req;

    return mutual_preference * economic_factor * 10.0; // Scale up for visibility
}

// Core WPBA execution logic
void WeightedPreferenceBiddingAlgorithm::runWeightedPreferenceBiddingAlgorithm() {

    // Clear previous matches/scores
    final_matches.clear();
    satisfaction_scores.clear();

    // PHASE 1: Calculate all bidding scores
    std::map<std::string, std::map<std::string, double>> bidding_matrix;

    for (const auto& platform : platforms) {
        for (const auto& restaurant : restaurants) {
            double score = calculateBiddingScore(platform, restaurant);
            bidding_matrix[platform][restaurant] = score;
        }
    }

    // PHASE 2: Competitive matching using iterative best-bid selection
    std::set<std::string> matched_platforms;
    std::set<std::string> matched_restaurants;
    int round = 1;

    // The maximum possible matches is the size of the smaller set (8 platforms)
    while (matched_platforms.size() < platforms.size() && round <= 10) {

        double max_score = -1;
        std::string best_platform, best_restaurant;

        // Find the highest unmatched bidding score
        for (const auto& platform : platforms) {
            if (matched_platforms.find(platform) != matched_platforms.end()) continue;

            for (const auto& restaurant : restaurants) {
                if (matched_restaurants.find(restaurant) != matched_restaurants.end()) continue;

                if (bidding_matrix[platform][restaurant] > max_score) {
                    max_score = bidding_matrix[platform][restaurant];
                    best_platform = platform;
                    best_restaurant = restaurant;
                }
            }
        }

        if (max_score > 0) {
            // Make the match
            final_matches[best_platform] = best_restaurant;
            matched_platforms.insert(best_platform);
            matched_restaurants.insert(best_restaurant);

            // Calculate satisfaction for this match
            double satisfaction = (platform_weights[best_platform][best_restaurant] +
                restaurant_weights[best_restaurant][best_platform]) /
                (double)(platforms.size() + restaurants.size()) * 100.0;
            satisfaction_scores[best_platform] = satisfaction;
        }
        else {
            // No positive score match found, stop early
            break;
        }

        round++;
    }

    // PHASE 3: Handle unmatched entities
    for (const auto& platform : platforms) {
        if (matched_platforms.find(platform) == matched_platforms.end()) {
            final_matches[platform] = ""; // Unmatched
            satisfaction_scores[platform] = 0.0;
        }
    }
}

// Public method to analyze stability
void WeightedPreferenceBiddingAlgorithm::analyzeStability() {
    std::cout << "\n=== STABILITY ANALYSIS (WPBA CRITERIA) ===" << std::endl;

    int blocking_pairs = 0;

    // Check for "blocking pairs" based on the bidding score
    for (const auto& platform : platforms) {
        for (const auto& restaurant : restaurants) {

            // Current Match and Scores
            std::string current_match_restaurant = final_matches[platform];

            // Only consider unmatched platform-restaurant pairs
            if (current_match_restaurant == restaurant) continue;

            double potential_score = calculateBiddingScore(platform, restaurant);

            // 1. Check if Platform P prefers R (better score than current match, if any)
            bool platform_prefers_potential;
            if (current_match_restaurant.empty()) {
                platform_prefers_potential = (potential_score > 0);
            }
            else {
                double current_score = calculateBiddingScore(platform, current_match_restaurant);
                platform_prefers_potential = (potential_score > current_score);
            }

            // 2. Check if Restaurant R prefers P (better score than current match, if any)
            std::string current_restaurant_partner = "";
            for (const auto& p : platforms) {
                if (final_matches[p] == restaurant) {
                    current_restaurant_partner = p;
                    break;
                }
            }

            bool restaurant_prefers_potential;
            if (current_restaurant_partner.empty()) {
                restaurant_prefers_potential = (potential_score > 0);
            }
            else {
                // To check R's preference for P, we use the potential score that (P, R) generated
                double current_partner_potential_score = calculateBiddingScore(current_restaurant_partner, restaurant);
                restaurant_prefers_potential = (potential_score > current_partner_potential_score);
            }

            if (platform_prefers_potential && restaurant_prefers_potential) {
                blocking_pairs++;
                std::cout << "Blocking Pair Found: " << platform << " - " << restaurant << std::endl;
            }
        }
    }

    if (blocking_pairs == 0) {
        std::cout << "Matching is STABLE under WPBA criteria!" << std::endl;
    }
    else {
        std::cout << "Found " << blocking_pairs << " blocking pairs. The WPBA may not be Stable based on its own score criteria." << std::endl;
    }
}