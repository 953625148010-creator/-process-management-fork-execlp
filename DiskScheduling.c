#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#define MAX 100
void sstf(int req[], int n, int head)
{
int visited[MAX] = {0};
int total = 0, cur = head, i, count = 0;
printf(&quot;\n--- SSTF (Shortest Seek Time First) ---\n&quot;);
printf(&quot;Seek Sequence: %d&quot;, cur);
while (count &lt; n) {
int min_dist = 1000000, idx = -1;
for (i = 0; i &lt; n; i++) {
if (!visited[i]) {
int dist = abs(req[i] - cur);
if (dist &lt; min_dist) {
min_dist = dist;
idx = i;
}
}
}
visited[idx] = 1;
total += min_dist;
cur = req[idx];
printf(&quot; -&gt; %d&quot;, cur);
count++;
}
printf(&quot;\nTotal Head Movement (SSTF) = %d\n&quot;, total);
}
int cmp(const void *a, const void *b)
{
return (*(int *)a - *(int *)b);
}
void scan(int req[], int n, int head, int disk_size, int direction)
{
int sorted[MAX];
int i;
for (i = 0; i &lt; n; i++) sorted[i] = req[i];
qsort(sorted, n, sizeof(int), cmp);
int total = 0, cur = head;
printf(&quot;\n--- SCAN (Elevator Algorithm) ---\n&quot;);
printf(&quot;Seek Sequence: %d&quot;, cur);
if (direction == 1) { /* move up towards disk_size-1, then reverse */
for (i = 0; i &lt; n; i++) {
if (sorted[i] &gt;= head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(sorted[i] - cur);
cur = sorted[i];
}
}
if (cur != disk_size - 1) {
printf(&quot; -&gt; %d&quot;, disk_size - 1);
total += abs((disk_size - 1) - cur);
cur = disk_size - 1;
}
for (i = n - 1; i &gt;= 0; i--) {
if (sorted[i] &lt; head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(cur - sorted[i]);
cur = sorted[i];
}
}
} else {
for (i = n - 1; i &gt;= 0; i--) {
if (sorted[i] &lt;= head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(cur - sorted[i]);
cur = sorted[i];
}
}
if (cur != 0) {
printf(&quot; -&gt; %d&quot;, 0);
total += abs(cur - 0);
cur = 0;
}
for (i = 0; i &lt; n; i++) {
if (sorted[i] &gt; head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(sorted[i] - cur);
cur = sorted[i];
}
}
}
printf(&quot;\nTotal Head Movement (SCAN) = %d\n&quot;, total);
}
void cscan(int req[], int n, int head, int disk_size)
{
int sorted[MAX];
int i;
for (i = 0; i &lt; n; i++) sorted[i] = req[i];
qsort(sorted, n, sizeof(int), cmp);
int total = 0, cur = head;
printf(&quot;\n--- C-SCAN (Circular SCAN) ---\n&quot;);
printf(&quot;Seek Sequence: %d&quot;, cur);
for (i = 0; i &lt; n; i++) {
if (sorted[i] &gt;= head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(sorted[i] - cur);
cur = sorted[i];
}
}
if (cur != disk_size - 1) {
printf(&quot; -&gt; %d&quot;, disk_size - 1);
total += abs((disk_size - 1) - cur);
cur = disk_size - 1;
}
printf(&quot; -&gt; 0 (jump)&quot;);
cur = 0;
for (i = 0; i &lt; n; i++) {
if (sorted[i] &lt; head) {
printf(&quot; -&gt; %d&quot;, sorted[i]);
total += abs(sorted[i] - cur);
cur = sorted[i];
}
}
printf(&quot;\nTotal Head Movement (C-SCAN) = %d\n&quot;, total);
}
int main()
{
int n, head, disk_size, i, direction;
int req[MAX];
printf(&quot;Enter number of disk requests: &quot;);
scanf(&quot;%d&quot;, &amp;n);
printf(&quot;Enter the request queue (cylinder numbers):\n&quot;);
for (i = 0; i &lt; n; i++)
scanf(&quot;%d&quot;, &amp;req[i]);
printf(&quot;Enter initial head position: &quot;);
scanf(&quot;%d&quot;, &amp;head);
printf(&quot;Enter disk size (max cylinder number + 1, e.g. 200): &quot;);
scanf(&quot;%d&quot;, &amp;disk_size);
printf(&quot;Enter initial direction for SCAN (1 = towards higher, 0 = towards lower): &quot;);
scanf(&quot;%d&quot;, &amp;direction);
sstf(req, n, head);
scan(req, n, head, disk_size, direction);
cscan(req, n, head, disk_size);
return 0;
}
