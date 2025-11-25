#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

// We use a Template class so this Cache can work with any data type (int, string, etc.)
template <typename K, typename V>
class LRUCache {
private:
    // 1. Capacity: The maximum number of items the cache can hold.
    size_t capacity;

    // 2. The List: Stores Key-Value pairs. 
    // Front = Most Recently Used | Back = Least Recently Used
    // We use std::list because it is a Doubly Linked List.
    std::list<std::pair<K, V>> itemsList;

    // 3. The Map: Stores the Key and points to the Iterator (address) of that item in the list.
    // This gives us O(1) access to any item in the list.
    using ListIterator = typename std::list<std::pair<K, V>>::iterator;
    std::unordered_map<K, ListIterator> cacheMap;

public:
    // Constructor to set the size
    LRUCache(size_t cap) : capacity(cap) {}

    // --- FUNCTION 1: GET (Retrieve Data) ---
    bool get(K key, V& value) {
        // Step A: Check if key exists in the map
        if (cacheMap.find(key) == cacheMap.end()) {
            return false; // Not found
        }

        // Step B: It exists! Move this item to the FRONT of the list (Most Recently Used).
        // 'splice' is a special C++ function that moves list nodes in O(1) time without copying.
        itemsList.splice(itemsList.begin(), itemsList, cacheMap[key]);

        // Step C: Return the value
        value = cacheMap[key]->second;
        return true;
    }

    // --- FUNCTION 2: PUT (Insert or Update Data) ---
    void put(K key, V value) {
        // Step A: If key already exists, update it
        if (cacheMap.find(key) != cacheMap.end()) {
            // Move to front (mark as recently used)
            itemsList.splice(itemsList.begin(), itemsList, cacheMap[key]);
            // Update the value
            cacheMap[key]->second = value;
            return;
        }

        // Step B: If key is new, check if we are full
        if (itemsList.size() == capacity) {
            // We are full! Delete the Least Recently Used item (the Back of the list).
            K keyToRemove = itemsList.back().first;
            itemsList.pop_back();        // Remove from List
            cacheMap.erase(keyToRemove); // Remove from Map
        }

        // Step C: Insert the new item at the Front
        itemsList.push_front({key, value});
        
        // Step D: Add the new entry to the Map
        cacheMap[key] = itemsList.begin();
    }

    // Helper function to print the cache status
    void display() {
        std::cout << "Cache (Most Recent -> Oldest): ";
        for (auto const& item : itemsList) {
            std::cout << "[" << item.first << ":" << item.second << "] ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // TEST CASE: Modeling a Browser History that only remembers 3 pages.
    LRUCache<int, std::string> browserHistory(3);

    std::cout << "--- LRU Cache Simulation ---\n";

    std::cout << "1. User visits Google (ID: 1)...\n";
    browserHistory.put(1, "Google.com");
    browserHistory.display();

    std::cout << "2. User visits YouTube (ID: 2)...\n";
    browserHistory.put(2, "YouTube.com");
    browserHistory.display();

    std::cout << "3. User visits GitHub (ID: 3)...\n";
    browserHistory.put(3, "GitHub.com");
    browserHistory.display();

    std::cout << "4. User visits Microsoft (ID: 4) -> Cache Full! Google (Oldest) should disappear...\n";
    browserHistory.put(4, "Microsoft.com");
    browserHistory.display();

    std::cout << "5. User visits YouTube AGAIN (ID: 2) -> YouTube moves to the front...\n";
    std::string val;
    browserHistory.get(2, val);
    browserHistory.display();

    return 0;
}