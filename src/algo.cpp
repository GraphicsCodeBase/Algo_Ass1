#include "algo.hpp"

// Preference lists (best first) to rank maps (1 = best)
void GaleShapleyAlgorithm::convertPrefsToRanks(
    const std::map<std::string, std::vector<std::string>>& prefs,
    std::map<std::string, std::map<std::string, int>>& ranks,
    const std::vector<std::string>& all_partners)
{
    for (const auto& pair : prefs) {
        const std::string& entity = pair.first;
        const std::vector<std::string>& pref_list = pair.second;
        for (size_t i = 0; i < pref_list.size(); ++i) {
            ranks[entity][pref_list[i]] = i + 1; // Rank 1 is best
        }
    }
}

void GaleShapleyAlgorithm::initializeData() {
    // 5 Platforms and 5 Restaurants (The size must be equal for a complete matching in G-S)
    platforms = { "GrabFood", "Foodpanda", "Deliveroo", "WhyQ", "Oddle" };
    restaurants = { "PastaExpress_Orchard", "ChiliCrab_Marina", "BakKutTeh_Chinatown",
                      "ChickenRice_Bugis", "LaksaKing_Katong" };

    // Initialize next proposal index for all platforms to 0
    for (const auto& platform : platforms) {
        next_proposal_index[platform] = 0;
    }

    // --- PLATFORM PREFERENCE LISTS (best first) ---
    std::map<std::string, std::vector<std::string>> platform_prefs = {
        {"GrabFood", {"ChiliCrab_Marina", "PastaExpress_Orchard", "LaksaKing_Katong", "ChickenRice_Bugis", "BakKutTeh_Chinatown"}},
        {"Foodpanda", {"PastaExpress_Orchard", "ChiliCrab_Marina", "ChickenRice_Bugis", "LaksaKing_Katong", "BakKutTeh_Chinatown"}},
        {"Deliveroo", {"LaksaKing_Katong", "PastaExpress_Orchard", "ChiliCrab_Marina", "ChickenRice_Bugis", "BakKutTeh_Chinatown"}},
        {"WhyQ", {"ChickenRice_Bugis", "BakKutTeh_Chinatown", "LaksaKing_Katong", "ChiliCrab_Marina", "PastaExpress_Orchard"}},
        {"Oddle", {"BakKutTeh_Chinatown", "ChickenRice_Bugis", "LaksaKing_Katong", "PastaExpress_Orchard", "ChiliCrab_Marina"}}
    };
    convertPrefsToRanks(platform_prefs, platform_ranks, restaurants);

    // --- RESTAURANT PREFERENCE LISTS (best first) ---
    std::map<std::string, std::vector<std::string>> restaurant_prefs = {
        {"PastaExpress_Orchard", {"Deliveroo", "GrabFood", "Foodpanda", "Oddle", "WhyQ"}},
        {"ChiliCrab_Marina", {"GrabFood", "Foodpanda", "Deliveroo", "WhyQ", "Oddle"}},
        {"BakKutTeh_Chinatown", {"WhyQ", "Oddle", "GrabFood", "Foodpanda", "Deliveroo"}},
        {"ChickenRice_Bugis", {"Foodpanda", "GrabFood", "WhyQ", "Deliveroo", "Oddle"}},
        {"LaksaKing_Katong", {"GrabFood", "Deliveroo", "Foodpanda", "WhyQ", "Oddle"}}
    };
    convertPrefsToRanks(restaurant_prefs, restaurant_ranks, platforms);
}

// Display preference lists
void GaleShapleyAlgorithm::displayPreferences() {
    std::cout << "\n=== INITIAL PREFERENCE LISTS (Rank 1 = Best) ===" << std::endl;

    // P-Side Preferences
    std::cout << "\n--- PLATFORM PREFERENCES ---" << std::endl;
    for (const auto& platform : platforms) {
        std::cout << std::left << std::setw(12) << platform << ": ";
        std::vector<std::pair<int, std::string>> sorted_prefs;
        for (const auto& pair : platform_ranks[platform]) {
            sorted_prefs.push_back({ pair.second, pair.first });
        }
        std::sort(sorted_prefs.begin(), sorted_prefs.end());

        for (const auto& pair : sorted_prefs) {
            std::cout << pair.first << "(" << pair.second << "), ";
        }
        std::cout << std::endl;
    }

    // R-Side Preferences
    std::cout << "\n--- RESTAURANT PREFERENCES ---" << std::endl;
    for (const auto& restaurant : restaurants) {
        std::cout << std::left << std::setw(25) << restaurant << ": ";
        std::vector<std::pair<int, std::string>> sorted_prefs;
        for (const auto& pair : restaurant_ranks[restaurant]) {
            sorted_prefs.push_back({ pair.second, pair.first });
        }
        std::sort(sorted_prefs.begin(), sorted_prefs.end());

        for (const auto& pair : sorted_prefs) {
            std::cout << pair.first << "(" << pair.second << "), ";
        }
        std::cout << "\n" << std::endl;
    }
    std::cout << std::string(70, '-') << std::endl;
}

// --- CORE GALE-SHAPLEY IMPLEMENTATION ---
void GaleShapleyAlgorithm::runGaleShapleyAlgorithm() {

    // Clear matches and reset proposal state
    current_matches.clear();
    std::set<std::string> free_platforms;
    for (const auto& p : platforms) {
        free_platforms.insert(p);
        next_proposal_index[p] = 0; // Reset index to the first restaurant
    }

    int total_proposals = 0;

    std::cout << "=== GALE-SHAPLEY ALGORITHM (Platform-Proposing) ===" << std::endl;
    std::cout << "Phase 1: Sequential Proposals and Engagements" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    while (!free_platforms.empty()) {
        std::string proposer = *free_platforms.begin(); // Get a free platform

        // Find the restaurant corresponding to the current rank index
        std::string restaurant_to_propose_to = "";
        int target_rank = next_proposal_index[proposer] + 1;
        for (const auto& res : restaurants) {
            if (platform_ranks[proposer][res] == target_rank) {
                restaurant_to_propose_to = res;
                break;
            }
        }

        if (restaurant_to_propose_to.empty()) {
            // Platform has proposed to everyone, remove from free list
            free_platforms.erase(proposer);
            continue;
        }

        total_proposals++;
        std::cout << "  " << proposer << " proposes to " << restaurant_to_propose_to << std::endl;

        // 1. Check if the restaurant is free
        if (current_matches.find(restaurant_to_propose_to) == current_matches.end()) {
            // R is free, P and R become engaged
            current_matches[restaurant_to_propose_to] = proposer;
            free_platforms.erase(proposer);
            std::cout << "    Match! " << restaurant_to_propose_to << " is free and accepts." << std::endl;
        }
        // 2. R is engaged to P' (current_partner)
        else {
            std::string current_partner = current_matches[restaurant_to_propose_to];

            // Check if R prefers P (proposer) to P' (current_partner)
            int proposer_rank = restaurant_ranks[restaurant_to_propose_to][proposer];
            int current_partner_rank = restaurant_ranks[restaurant_to_propose_to][current_partner];

            if (proposer_rank < current_partner_rank) {
                // R prefers P to P', breaks engagement with P'
                current_matches[restaurant_to_propose_to] = proposer; // P and R engaged
                free_platforms.erase(proposer); // P is no longer free
                free_platforms.insert(current_partner); // P' becomes free
                std::cout << "    Rejection: " << restaurant_to_propose_to
                    << " rejects " << current_partner << " for better offer from " << proposer << std::endl;
            }
            else {
                // R prefers P' (current_partner) to P (proposer), P remains free
                std::cout << "    Rejection: " << restaurant_to_propose_to
                    << " rejects " << proposer << " and stays with " << current_partner << std::endl;
            }
        }

        // P has made a proposal, increment its proposal index for the next round
        next_proposal_index[proposer]++;
    }

    std::cout << "\nPhase 2: Final Match Summary" << std::endl;
    std::cout << "Total Proposals Made: " << total_proposals << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

// Helper to check for stability (no blocking pairs)
bool GaleShapleyAlgorithm::isStable() {
    std::cout << "\n=== STABILITY CHECK ===" << std::endl;

    for (const auto& platform : platforms) {
        // Find current match for this platform
        std::string current_restaurant = "";
        for (const auto& match : current_matches) {
            if (match.second == platform) {
                current_restaurant = match.first;
                break;
            }
        }

        // Check all restaurants this platform prefers to current match
        for (const auto& restaurant : restaurants) {
            if (restaurant == current_restaurant) continue; // Skip current match

            std::string restaurants_current_partner = current_matches.at(restaurant);

            // Does platform prefer this restaurant to current match?
            bool platform_prefers = false;
            if (current_restaurant.empty()) {
                platform_prefers = true; // Unmatched platform prefers any restaurant
            }
            else {
                int current_rank = platform_ranks[platform][current_restaurant];
                int other_rank = platform_ranks[platform][restaurant];
                platform_prefers = (other_rank < current_rank); // Lower rank = better
            }

            // Does restaurant prefer this platform to current partner?
            bool restaurant_prefers = false;
            int platform_rank = restaurant_ranks[restaurant][platform];
            int current_partner_rank = restaurant_ranks[restaurant][restaurants_current_partner];
            restaurant_prefers = (platform_rank < current_partner_rank);

            if (platform_prefers && restaurant_prefers) {
                std::cout << "BLOCKING PAIR FOUND: " << platform
                    << " and " << restaurant << " would both prefer each other!" << std::endl;
                return false;
            }
        }
    }

    std::cout << "No blocking pairs found - matching is STABLE!" << std::endl;
    return true;
}

// Setters for test manipulation
void GaleShapleyAlgorithm::swapPlatformPreferences(const std::string& platform, const std::string& resA, const std::string& resB) {
    if (platform_ranks.count(platform) && platform_ranks[platform].count(resA) && platform_ranks[platform].count(resB)) {
        std::swap(platform_ranks[platform][resA], platform_ranks[platform][resB]);
    }
}

void GaleShapleyAlgorithm::swapRestaurantPreferences(const std::string& restaurant, const std::string& platA, const std::string& platB) {
    if (restaurant_ranks.count(restaurant) && restaurant_ranks[restaurant].count(platA) && restaurant_ranks[restaurant].count(platB)) {
        std::swap(restaurant_ranks[restaurant][platA], restaurant_ranks[restaurant][platB]);
    }
}