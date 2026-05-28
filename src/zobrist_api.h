#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "zobrist.h"

namespace godot {

class ZobristAPI : public RefCounted {
    GDCLASS(ZobristAPI, RefCounted)

private:
    // Every instance of this class gets its own tracker.
    Zobrist::Tracker tracker;

protected:
    static void _bind_methods();

public:
    ZobristAPI();
    ~ZobristAPI();

    // 1. Global Initialization
    void init_keys(int64_t seed);

    // 2. Incremental Updates
    void toggle_piece(int square, int piece_value);
    void toggle_side();
    void update_castling(int old_rights, int new_rights);
    void update_en_passant(int old_file, int new_file);
    
    // 3. State Management
    void reset_tracker();
    
    // Returns Godot's signed 64-bit integer
    int64_t get_current_hash() const; 
};

}