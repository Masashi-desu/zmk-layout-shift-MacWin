#ifdef CONFIG_LAYOUT_SHIFT_TARGET_JIS
#define LAYOUT_DEFINED
// Japanese (JIS) keyboard layout mappings
// Maps US layout keycodes to their JIS equivalents
static const struct keycode_mapping layout_map[] = {
    /* from -> to */
    {EQUAL, UNDERSCORE},           /* = -> _ */
    {CARET, EQUAL},                /* ^ -> = */
    {TILDE, PLUS},                 /* ~ -> + */
    {AT_SIGN, LEFT_BRACKET},       /* @ -> [ */
    {GRAVE, LEFT_BRACE},           /* ` -> { */
    {LEFT_BRACKET, RIGHT_BRACKET}, /* [ -> ] */
    {RIGHT_BRACKET, BACKSLASH},    /* ] -> \ */
    {LEFT_BRACE, RIGHT_BRACE},     /* { -> } */
    {RIGHT_BRACE, PIPE},           /* } -> | */
    {PLUS, COLON},                 /* + -> : */
    {COLON, SINGLE_QUOTE},         /* : -> ' */
    {ASTERISK, DOUBLE_QUOTES},     /* * -> " */
    {DOUBLE_QUOTES, AT_SIGN},      /* " -> @ */
    {AMPERSAND, CARET},            /* & -> ^ */
    {SINGLE_QUOTE, AMPERSAND},     /* ' -> & */
    {LEFT_PARENTHESIS, ASTERISK},  /* ( -> * */
    {RIGHT_PARENTHESIS, LEFT_PARENTHESIS}, /* ) -> ( */
    {UNDERSCORE, LS(0x87)},        /* _ */
    {BACKSLASH, 0x89},             /* \ */
    {PIPE, LS(0x89)},              /* | */
};
#endif