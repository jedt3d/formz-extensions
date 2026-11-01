/* Mirrors fzrt_curs_init (libFZRT x86_64 0x3df97-0x3e0e5): read count, then count rows. */
#include <stdio.h>
int main(int c, char **v) {
  FILE *f = fopen(v[1], "r"); int n, id[200], x[200], y[200];
  fscanf(f, "%d", &n);
  fscanf(f, "%d,%d,%d", &id[0], &x[0], &y[0]);
  for (int i = 1; i < n; i++) fscanf(f, "%d,%d,%d", &id[i], &x[i], &y[i]);
  printf("count=%d first=%d last=%d(%d,%d)\n", n, id[0], id[n-1], x[n-1], y[n-1]);
  int extra, ex, ey; if (fscanf(f, "%d,%d,%d", &extra, &ex, &ey) == 3) printf("left unread: %d,%d,%d\n", extra, ex, ey);
  for (int i = 0; i < n; i++) if (id[i] == 637) printf("637 found\n");
  return 0;
}
