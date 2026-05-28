#pragma once

#include <cstdint>
#include "wyrand.hpp"

namespace Zobrist {
    inline uint64_t piece_keys[64][16];
    inline uint64_t castling_keys[16];
    inline uint64_t en_passant_keys[9];
    inline uint64_t side_key;

    inline void init(uint64_t seed = 123456789ULL) {
        Wyrand::Wyrand rng(seed);

        for (int sq = 0; sq < 64; ++sq) {
            for (int pc = 0; pc < 16; ++pc) {
                piece_keys[sq][pc] = rng();
            }
        }
        for (int i = 0; i < 16; ++i) {
            castling_keys[i] = rng();
        }
        for (int i = 0; i < 9; ++i) {
            en_passant_keys[i] = rng();
        }
        side_key = rng();
    }

    class Tracker {
    public:
        uint64_t current_hash = 0;

        // Toggles a piece on or off a square. 
        // Because a ^ a = 0, calling this twice removes the piece.
        inline void toggle_piece(int square, int piece_value) {
            // piece_value safely expects your 0-5 and & 8 logic
            current_hash ^= piece_keys[square][piece_value];
        }

        // Swaps the active turn
        inline void toggle_side() {
            current_hash ^= side_key;
        }

        // Updates castling rights. 
        // Pass the integer representation of your castling boolean states (0-15).
        inline void update_castling(int old_rights, int new_rights) {
            current_hash ^= castling_keys[old_rights]; // Remove old
            current_hash ^= castling_keys[new_rights]; // Apply new
        }

        // Updates en passant file. Use 8 for "None".
        inline void update_en_passant(int old_file, int new_file) {
            current_hash ^= en_passant_keys[old_file];
            current_hash ^= en_passant_keys[new_file];
        }

        // Resets the hash (useful when starting a new game)
        inline void reset() {
            current_hash = 0;
        }
    };
}