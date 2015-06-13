int first_bigger(int* a, int n, int value) {
    if (a[n - 1] <= value) return -1;
    int left = 0, right = n - 1;
    while (left < right) {
        int center = (left + right + 1) / 2;
        if (a[center] <= value) left = center + 1;
        else right = center;
    }
    return left;
}
