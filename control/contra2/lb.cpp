int first_bigger(int* a, int n, int value) {
    if (a[n - 1] <= value) return -1;
    int l = 0, r = n - 1;
    while (l < r) {
        int center = (l + r + 1) / 2;
        if (a[center] <= value) l = center + 1;
        else r = center;
    }
    return l;
}
