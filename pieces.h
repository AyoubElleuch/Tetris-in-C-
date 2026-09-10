#pragma once

constexpr bool pieces[7][4][4] = {
    // I
    {
        { false, true, false, false },
        { false, true, false, false},
        { false, true, false, false },
        { false, true, false, false }
    },

    // O
    {
        { false, true,  true,  false },
        { false, true,  true,  false },
        { false, false, false, false },
        { false, false, false, false }
    },

    // T
    {
        { false, true,  false, false },
        { true,  true,  true,  false },
        { false, false, false, false },
        { false, false, false, false }
    },

    // S
    {
        { false, true,  true,  false },
        { true,  true,  false, false },
        { false, false, false, false },
        { false, false, false, false }
    },

    // Z
    {
        { true,  true,  false, false },
        { false, true,  true,  false },
        { false, false, false, false },
        { false, false, false, false }
    },

    // J
    {
        { true,  false, false, false },
        { true,  true,  true,  false },
        { false, false, false, false },
        { false, false, false, false }
    },

    // L
    {
        { false, false, true,  false },
        { true,  true,  true,  false },
        { false, false, false, false },
        { false, false, false, false }
    }
};
