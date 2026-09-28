#include &lt;stdio.h&gt;
#define MAX 50
int is_present(int frames[], int nf, int page){
int i;
for (i = 0; i &lt; nf; i++)
if (frames[i] == page)
return 1;
return 0;
}
void fifo(int ref[], int n, int nf)
{
int frames[MAX];
int i, j, faults = 0, next = 0;
for (i = 0; i &lt; nf; i++) frames[i] = -1;
printf(&quot;\n--- FIFO Page Replacement ---\n&quot;);
for (i = 0; i &lt; n; i++) {
if (!is_present(frames, nf, ref[i])) {
frames[next] = ref[i];
next = (next + 1) % nf;
faults++;
printf(&quot;Page %d -&gt; Fault \tFrames: &quot;, ref[i]);
} else {
printf(&quot;Page %d -&gt; Hit \tFrames: &quot;, ref[i]);
}
for (j = 0; j &lt; nf; j++)
printf(&quot;%d &quot;, frames[j]);
printf(&quot;\n&quot;);
}
printf(&quot;Total Page Faults (FIFO) = %d\n&quot;, faults);
}
void lru(int ref[], int n, int nf)
{
int frames[MAX], last_used[MAX];
int i, j, faults = 0;
for (i = 0; i &lt; nf; i++) { frames[i] = -1; last_used[i] = -1; }
printf(&quot;\n--- LRU Page Replacement ---\n&quot;);
for (i = 0; i &lt; n; i++) {
if (!is_present(frames, nf, ref[i])) {
int idx = -1;
for (j = 0; j &lt; nf; j++)
if (frames[j] == -1) { idx = j; break; }
if (idx == -1) {
int lru_idx = 0;
for (j = 1; j &lt; nf; j++)
if (last_used[j] &lt; last_used[lru_idx])
lru_idx = j;
idx = lru_idx;
}
frames[idx] = ref[i];
last_used[idx] = i;
faults++;
printf(&quot;Page %d -&gt; Fault \tFrames: &quot;, ref[i]);
} else {
for (j = 0; j &lt; nf; j++)
if (frames[j] == ref[i]) last_used[j] = i;
printf(&quot;Page %d -&gt; Hit \tFrames: &quot;, ref[i]);
}
for (j = 0; j &lt; nf; j++)
printf(&quot;%d &quot;, frames[j]);
printf(&quot;\n&quot;);
}
printf(&quot;Total Page Faults (LRU) = %d\n&quot;, faults);
}
void optimal(int ref[], int n, int nf)
{
int frames[MAX];
int i, j, k, faults = 0;
for (i = 0; i &lt; nf; i++) frames[i] = -1;
printf(&quot;\n--- Optimal Page Replacement ---\n&quot;);
for (i = 0; i &lt; n; i++) {
if (!is_present(frames, nf, ref[i])) {
int idx = -1;
for (j = 0; j &lt; nf; j++)
if (frames[j] == -1) { idx = j; break; }
if (idx == -1) {
int farthest = -1, replace_idx = 0;
for (j = 0; j &lt; nf; j++) {
int k_use = -1;
for (k = i + 1; k &lt; n; k++) {
if (frames[j] == ref[k]) { k_use = k; break; }
}
if (k_use == -1) { replace_idx = j; break; } /* never used again */
if (k_use &gt; farthest) { farthest = k_use; replace_idx = j; }
}
idx = replace_idx;
}
frames[idx] = ref[i];
faults++;
printf(&quot;Page %d -&gt; Fault \tFrames: &quot;, ref[i]);
} else {
printf(&quot;Page %d -&gt; Hit \tFrames: &quot;, ref[i]);
}
for (j = 0; j &lt; nf; j++)
printf(&quot;%d &quot;, frames[j]);
printf(&quot;\n&quot;);
}
printf(&quot;Total Page Faults (Optimal) = %d\n&quot;, faults);
}
int main()
{
int ref[MAX], n, nf;
printf(&quot;Enter number of pages in reference string: &quot;);
scanf(&quot;%d&quot;, &amp;n);
printf(&quot;Enter the reference string:\n&quot;
for (int i = 0; i &lt; n; i++)
scanf(&quot;%d&quot;, &amp;ref[i]);
printf(&quot;Enter number of page frames: &quot;);
scanf(&quot;%d&quot;, &amp;nf);
fifo(ref, n, nf);
lru(ref, n, nf);
optimal(ref, n, nf);
return 0;
}
