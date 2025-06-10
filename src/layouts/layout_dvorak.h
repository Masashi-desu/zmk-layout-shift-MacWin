#ifdef CONFIG_LAYOUT_SHIFT_TARGET_DVORAK
#define LAYOUT_DEFINED
// Dvorak keyboard layout mappings
// Maps US QWERTY keycodes to their Dvorak equivalents
static const struct keycode_mapping layout_map[] = {
    /* Letter position changes (QWERTY -> Dvorak) */
    {MINUS, LEFT_BRACKET},     // - -> [
    {EQUAL, RIGHT_BRACKET},    // = -> ]
    {Q, SINGLE_QUOTE},        // Q -> '
    {W, COMMA},               // W -> ,
    {E, DOT},                 // E -> .
    {R, P},                   // R -> P
    {T, Y},                   // T -> Y
    {Y, F},                   // Y -> F
    {U, G},                   // U -> G
    {I, C},                   // I -> C
    {O, R},                   // O -> R
    {P, L},                   // P -> L
    {LEFT_BRACKET, SLASH},    // [ -> /
    {RIGHT_BRACKET, EQUAL},   // ] -> =
    {S, O},                   // S -> O
    {D, E},                   // D -> E
    {F, U},                   // F -> U
    {G, I},                   // G -> I
    {H, D},                   // H -> D
    {J, H},                   // J -> H
    {K, T},                   // K -> T
    {L, N},                   // L -> N
    {SEMICOLON, S},           // ; -> S
    {SINGLE_QUOTE, MINUS},    // ' -> -
    {Z, SEMICOLON},           // Z -> ;
    {X, Q},                   // X -> Q
    {C, J},                   // C -> J
    {V, K},                   // V -> K
    {B, X},                   // B -> X
    {N, B},                   // N -> B
    {COMMA, W},               // , -> W
    {DOT, V},                 // . -> V
    {SLASH, Z},               // / -> Z
};
#endif