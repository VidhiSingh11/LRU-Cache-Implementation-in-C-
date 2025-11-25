# High-Performance In-Memory LRU Cache (C++)

## 📌 Overview
A robust, template-based implementation of a **Least Recently Used (LRU) Caching system** in C++. This project demonstrates advanced memory management techniques and algorithmic optimization to achieve **O(1) time complexity** for both data retrieval and insertion operations.

It is designed to mimic the core logic used in high-throughput systems (like Redis or Database Buffer Pools) where efficient eviction policies are critical for performance.

## ⚙️ Engineering Highlights
* **Generic Programming:** Implemented using **C++ Templates**, allowing the cache to store polymorphic data types (e.g., `<int, string>`, `<string, UserObject>`) without code duplication.
* **O(1) Time Complexity:** Utilizes a hybrid data structure combining `std::unordered_map` (Hash Map) and `std::list` (Doubly Linked List) to ensure constant-time access and updates.
* **Zero-Copy Eviction:** Leveraged `std::list::splice` to reprioritize nodes within the linked list. This moves the underlying memory pointers without allocating/deallocating memory, significantly reducing CPU overhead compared to vector-based shifting.

## 🛠 Technical Architecture
The system relies on two synchronized data structures:
1.  **Doubly Linked List (`std::list`):** Stores the actual values ordered by usage.
    * *Front:* Most Recently Used (MRU)
    * *Back:* Least Recently Used (LRU)
2.  **Hash Map (`std::unordered_map`):** Maps keys to the specific iterator (pointer) of the node in the list, enabling instant $O(1)$ lookup without traversing the list.

## 🚀 Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| `get(key)` | **O(1)** | O(1) | Looks up key in map, moves node to front via `splice`. |
| `put(key)` | **O(1)** | O(1) | Inserts new item or updates existing. If full, evicts tail in O(1). |

## 💻 How to Run

### Prerequisites
* G++ Compiler (Supporting C++11 or higher)

### Build & Run
```bash
# Compile the program
g++ lru_cache.cpp -o lru_cache

# Run the executable
./lru_cache
