#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

class GaleShapleyAlgorithm {
private:
    std::vector<std::string> platforms; // Proposing side (Men/Students)
    std::vector<std::string> restaurants; // Receiving side (Women/Hospitals)

    // Preference ranks: map[Entity][Partner] = Rank (1 = best, N = worst)
    std::map<std::string, std::map<std::string, int>> platform_ranks;
    std::map<std::string, std::map<std::string, int>> restaurant_ranks;

    // Current matches: map[Restaurant] = Platform
    std::map<std::string, std::string> current_matches;

    // Helper to track which restaurant a platform has proposed to
    std::map<std::string, int> next_proposal_index;

    // Helper to convert preference lists to rank maps
    void convertPrefsToRanks(
        const std::map<std::string, std::vector<std::string>>& prefs,
        std::map<std::string, std::map<std::string, int>>& ranks,
        const std::vector<std::string>& all_partners
    );

public:
    GaleShapleyAlgorithm() {
        initializeData();
    }

    void initializeData();

    // Core Algorithm functions
    void runGaleShapleyAlgorithm();
    bool isStable(); // Checks for blocking pairs

    // === PUBLIC GETTERS FOR TEST_F MANIPULATION ===
    std::map<std::string, std::string> getFinalMatches() const { return current_matches; }
    std::vector<std::string> getPlatforms() const { return platforms; }
    std::vector<std::string> getRestaurants() const { return restaurants; }

    // Setter for scenario creation (e.g., swapping preferences for a test case)
    void swapPlatformPreferences(const std::string& platform, const std::string& resA, const std::string& resB);
    void swapRestaurantPreferences(const std::string& restaurant, const std::string& platA, const std::string& platB);

    // Helper to get partner's rank for stability check
    int getRestaurantRank(const std::string& restaurant, const std::string& platform) const {
        return restaurant_ranks.at(restaurant).at(platform);
    }

    void displayPreferences();
};
