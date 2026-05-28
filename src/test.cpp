#include <iostream>
#include "zobrist.h"

int main() {
    std::cout << "--- Zobrist Hashing Standalone Test ---\n";

    // 1. Initialize the global tables with a seed
    Zobrist::init(1337);
    std::cout << "Tables initialized.\n";

    // 2. Create a tracker
    Zobrist::Tracker tracker;
    std::cout << "Starting Hash: " << tracker.current_hash << "\n\n";

    // 3. Simulate a move
    tracker.toggle_piece(10, 1);
    tracker.toggle_side(); // Swap turn to Black
    
    uint64_t hash_after_move = tracker.current_hash;
    std::cout << "Hash after move 1: " << hash_after_move << "\n";

    // 4. Simulate a completely different move to verify the hash changes
    tracker.toggle_piece(45, 12);
    std::cout << "Hash after move 2: " << tracker.current_hash << "\n\n";

    // 5. Undo the moves to verify the hash reverses perfectly
    tracker.toggle_piece(45, 12);
    tracker.toggle_side();        // Swap turn back to White
    tracker.toggle_piece(10, 1);

    std::cout << "Hash after undoing all moves: " << tracker.current_hash << "\n";

    // 6. Test Conclusion
    if (tracker.current_hash == 0) {
        std::cout << "\nSUCCESS: The hash perfectly reverted to its starting state!\n";
    } else {
        std::cout << "\nERROR: The hash did not revert. Something is wrong.\n";
    }

    return 0;
}