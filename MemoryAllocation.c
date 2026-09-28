#include &lt;stdio.h&gt;
#include &lt;string.h&gt;
#define MAX 20
void first_fit(int bsize[], int nb, int psize[], int np){
int block[MAX], allocation[MAX];
int i, j;
for (i = 0; i &lt; nb; i++) block[i] = bsize[i]; /* remaining size of each block */
for (i = 0; i &lt; np; i++) allocation[i] = -1;
for (i = 0; i &lt; np; i++) {
for (j = 0; j &lt; nb; j++) {
if (block[j] &gt;= psize[i]) {
allocation[i] = j;
block[j] -= psize[i];
break;
}
}
}
printf(&quot;\n--- First Fit ---\n&quot;);
printf(&quot;Process\tSize\tBlock Allocated\n&quot;);
for (i = 0; i &lt; np; i++) {
if (allocation[i] != -1)
printf(&quot;P%d\t%d\tBlock %d\n&quot;, i + 1, psize[i], allocation[i] + 1);
else
printf(&quot;P%d\t%d\tNot Allocated\n&quot;, i + 1, psize[i]);
}
}
void best_fit(int bsize[], int nb, int psize[], int np){
int block[MAX], allocation[MAX];
int i, j;
for (i = 0; i &lt; nb; i++) block[i] = bsize[i];
for (i = 0; i &lt; np; i++) allocation[i] = -1;
for (i = 0; i &lt; np; i++) {
int best_idx = -1;
for (j = 0; j &lt; nb; j++) {
if (block[j] &gt;= psize[i]) {
if (best_idx == -1 || block[j] &lt; block[best_idx])
best_idx = j;
}
}
if (best_idx != -1) {
allocation[i] = best_idx;
block[best_idx] -= psize[i];
}
}
printf(&quot;\n--- Best Fit ---\n&quot;);
printf(&quot;Process\tSize\tBlock Allocated\n&quot;);
for (i = 0; i &lt; np; i++) {
if (allocation[i] != -1)
printf(&quot;P%d\t%d\tBlock %d\n&quot;, i + 1, psize[i], allocation[i] + 1);
else
printf(&quot;P%d\t%d\tNot Allocated\n&quot;, i + 1, psize[i]);
}
}
void worst_fit(int bsize[], int nb, int psize[], int np){
int block[MAX], allocation[MAX];
int i, j;
for (i = 0; i &lt; nb; i++) block[i] = bsize[i];
for (i = 0; i &lt; np; i++) allocation[i] = -1;
for (i = 0; i &lt; np; i++) {
int worst_idx = -1;
for (j = 0; j &lt; nb; j++) {
if (block[j] &gt;= psize[i]) {
if (worst_idx == -1 || block[j] &gt; block[worst_idx])
worst_idx = j;
}
}
if (worst_idx != -1) {
allocation[i] = worst_idx;
block[worst_idx] -= psize[i];
}
}
printf(&quot;\n--- Worst Fit ---\n&quot;);
printf(&quot;Process\tSize\tBlock Allocated\n&quot;);
for (i = 0; i &lt; np; i++) {
if (allocation[i] != -1)
printf(&quot;P%d\t%d\tBlock %d\n&quot;, i + 1, psize[i], allocation[i] + 1);
else
printf(&quot;P%d\t%d\tNot Allocated\n&quot;, i + 1, psize[i]);
}
}
int main()
{
int nb, np, i;
int bsize[MAX], psize[MAX];
printf(&quot;Enter number of memory blocks: &quot;);
scanf(&quot;%d&quot;, &amp;nb);
printf(&quot;Enter size of each block:\n&quot;);
for (i = 0; i &lt; nb; i++) {
printf(&quot;Block %d: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;bsize[i]);
}
printf(&quot;Enter number of processes: &quot;);
scanf(&quot;%d&quot;, &amp;np);
printf(&quot;Enter size of each process:\n&quot;);
for (i = 0; i &lt; np; i++) {
printf(&quot;Process %d: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;psize[i]);
}
first_fit(bsize, nb, psize, np);
best_fit(bsize, nb, psize, np);
worst_fit(bsize, nb, psize, np);
return 0;
}
