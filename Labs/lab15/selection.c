void swap(int *a, int *b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int selection_sort(int list[], int n) {
  int i, j, min_id;
  for (i = 0; i < n - 1; i++) {
    min_id = i;
    for (j = i + 1; j < n; j++) {
      if (list[j] < list[min_id])
        min_id = j;
    }
    swap(&list[i], &list[min_id]);
  }
}