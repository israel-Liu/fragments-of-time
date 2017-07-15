
// match_star : search for c*regexp at beginning of text
int match_star(int c, char* regexp, char* text)
{
    do { // a * matches zero or more instances
        if (match_here(regexp, text)) {
            return 1;
        }
    } while (*text != '\0' && (*text++ == c || c == '.'));

    return 0;
}

// match_here : search for regexp at beginning of text
int match_here(char* regexp, char* text)
{
    if (regexp[0] == '\0') {
        return 1;
    }

    if (regexp[1] == '*') {
        return match_star(regexp[0], regexp + 2, text);
    }

    if (regexp[0] == '$' && regexp[1] == '\0') {
        return *text == '\0';
    }

    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) {
        return match_here(regexp + 1, text + 1);
    }

    return 0;
}

// match : search for regexp anywhere in text
int match(char* regexp, char* text)
{
    if (regexp[0] == '^') {
        return match_here(regexp + 1, text);
    }

    do { // must look even if string is empty
        if (match_here(regexp, text)) {
            return 1;
        }
    } while (*text++ != '\0');

    return 0;
}

// match_star : leftmost longest search for c*regexp
int match_star_leftmost(int c, char* regexp, char* text)
{
    char* t = text;
    for (; * t != '\0' && (*t == c || c == '.'); ++t) {
        ;
    }

    do { // matches zero or more
        if (match_here(regexp, t)) {
            return 1;
        }
    } while (t-- > text);

    return 0;
}