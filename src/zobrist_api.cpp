#include "zobrist_api.h"

namespace godot {

void ZobristAPI::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init_keys", "seed"), &ZobristAPI::init_keys);
    
    ClassDB::bind_method(D_METHOD("toggle_piece", "square", "piece_value"), &ZobristAPI::toggle_piece);
    ClassDB::bind_method(D_METHOD("toggle_side"), &ZobristAPI::toggle_side);
    ClassDB::bind_method(D_METHOD("update_castling", "old_rights", "new_rights"), &ZobristAPI::update_castling);
    ClassDB::bind_method(D_METHOD("update_en_passant", "old_file", "new_file"), &ZobristAPI::update_en_passant);
    
    ClassDB::bind_method(D_METHOD("reset_tracker"), &ZobristAPI::reset_tracker);
    ClassDB::bind_method(D_METHOD("get_current_hash"), &ZobristAPI::get_current_hash);
}

ZobristAPI::ZobristAPI() {
    // Constructor
}

ZobristAPI::~ZobristAPI() {
    // Destructor
}

void ZobristAPI::init_keys(int64_t seed) {
    // Cast the GDScript signed int to C++ unsigned int
    Zobrist::init(static_cast<uint64_t>(seed));
}

void ZobristAPI::toggle_piece(int square, int piece_value) {
    tracker.toggle_piece(square, piece_value);
}

void ZobristAPI::toggle_side() {
    tracker.toggle_side();
}

void ZobristAPI::update_castling(int old_rights, int new_rights) {
    tracker.update_castling(old_rights, new_rights);
}

void ZobristAPI::update_en_passant(int old_file, int new_file) {
    tracker.update_en_passant(old_file, new_file);
}

void ZobristAPI::reset_tracker() {
    tracker.reset();
}

int64_t ZobristAPI::get_current_hash() const {
    // Cast the C++ unsigned int to GDScript signed int for return
    return static_cast<int64_t>(tracker.current_hash);
}

} // namespace godot