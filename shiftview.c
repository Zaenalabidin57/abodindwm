/**
 * Author: Fernando C.V.
 * http://lists.suckless.org/dev/1104/7590.html
 */

/** Function to shift view only across occupied (active) tags
 *
 * @param: "arg->i" positive to move right, negative to move left
 *         magnitude indicates how many occupied tags to skip
 */
void
shiftview(const Arg *arg) {
    Arg a = {0};
    unsigned int occ = 0, seltagmask;
    Client *c;
    int i, dir, steps, next, j;
    unsigned int curtag = 0;

    /* Build bitmask of occupied tags on the current monitor */
    for (c = selmon->clients; c; c = c->next)
        occ |= c->tags;

    occ &= TAGMASK;
    if (occ == 0)
        return; /* nothing to cycle through */

    seltagmask = selmon->tagset[selmon->seltags];

    /* Determine current tag index (0..LENGTH(tags)-1).
     * Prefer the first set bit in the current selection; if none, fallback to first occupied. */
    for (i = 0; i < LENGTH(tags); i++)
        if (seltagmask & (1u << i)) { curtag = i; break; }
    if (i == LENGTH(tags)) {
        for (i = 0; i < LENGTH(tags); i++)
            if (occ & (1u << i)) { curtag = i; break; }
    }

    dir = (arg->i > 0) ? 1 : -1;
    steps = (arg->i > 0) ? arg->i : -arg->i;
    next = (int)curtag;

    while (steps--) {
        for (j = 0; j < LENGTH(tags); j++) {
            next = dir > 0 ? (next + 1) % LENGTH(tags)
                           : (next - 1 + LENGTH(tags)) % LENGTH(tags);
            if (occ & (1u << next))
                break; /* found next occupied tag in this direction */
        }
    }

    a.ui = 1u << next;
    view(&a);
}
