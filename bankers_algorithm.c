#include &lt;stdio.h&gt;
#define P 5
#define R 3
int allocation[P][R];
int max[P][R];
int need[P][R];
int available[R];
void calculate_need(){
int i, j;
for (i = 0; i &lt; P; i++)
for (j = 0; j &lt; R; j++)
need[i][j] = max[i][j] - allocation[i][j];
}
int is_safe(int safe_seq[]){
int work[R];
int finish[P] = {0};
int i, j, count = 0;
for (i = 0; i &lt; R; i++)
work[i] = available[i];
while (count &lt; P) {
int found = 0;
for (i = 0; i &lt; P; i++) {
if (!finish[i]) {
int can_allocate = 1;
for (j = 0; j &lt; R; j++) {
if (need[i][j] &gt; work[j]) {
can_allocate = 0;
break;
}
}
if (can_allocate) {
for (j = 0; j &lt; R; j++)
work[j] += allocation[i][j];
safe_seq[count++] = i;
finish[i] = 1;
found = 1;
}
}
}
if (!found)
return 0; /* no process could proceed -&gt; unsafe */
}
return 1;
}
int request_resources(int p_id, int request[R]){
int i;
int safe_seq[P];
for (i = 0; i &lt; R; i++) {
if (request[i] &gt; need[p_id][i]) {
printf(&quot;Error: Process P%d has exceeded its maximum claim.\n&quot;, p_id);
return 0;
}
}
for (i = 0; i &lt; R; i++) {
if (request[i] &gt; available[i]) {
printf(&quot;Process P%d must wait; resources are not available.\n&quot;, p_id);
return 0;
}
}
for (i = 0; i &lt; R; i++) {
available[i] -= request[i];
allocation[p_id][i] += request[i];
need[p_id][i] -= request[i];
}
if (is_safe(safe_seq)) {
printf(&quot;Request can be granted safely.\nNew safe sequence: &quot;);
for (i = 0; i &lt; P; i++)
printf(&quot;P%d &quot;, safe_seq[i]);
printf(&quot;\n&quot;);
return 1;
} else {
for (i = 0; i &lt; R; i++) {
available[i] += request[i];
allocation[p_id][i] -= request[i];
need[p_id][i] += request[i];
}
printf(&quot;Request denied: granting it would leave the system in an unsafe state.\n&quot;);
return 0;
}
}
int main(){
int i, j;
printf(&quot;Enter Allocation matrix (%d processes x %d resources):\n&quot;, P, R);
for (i = 0; i &lt; P; i++) {
printf(&quot;P%d: &quot;, i);
for (j = 0; j &lt; R; j++)
scanf(&quot;%d&quot;, &amp;allocation[i][j]);
}
printf(&quot;Enter Maximum matrix (%d processes x %d resources):\n&quot;, P, R);
for (i = 0; i &lt; P; i++) {
printf(&quot;P%d: &quot;, i);
for (j = 0; j &lt; R; j++)
scanf(&quot;%d&quot;, &amp;max[i][j]);
}
printf(&quot;Enter Available resources vector (%d resources):\n&quot;, R);
for (j = 0; j &lt; R; j++)
scanf(&quot;%d&quot;, &amp;available[j]);
calculate_need();
printf(&quot;\nNeed matrix:\n&quot;);
for (i = 0; i &lt; P; i++) {
printf(&quot;P%d: &quot;, i);
for (j = 0; j &lt; R; j++)
printf(&quot;%d &quot;, need[i][j]);
printf(&quot;\n&quot;);
}
int safe_seq[P];
if (is_safe(safe_seq)) {
printf(&quot;\nSystem is in a SAFE state.\nSafe sequence: &quot;);
for (i = 0; i &lt; P; i++)
printf(&quot;P%d &quot;, safe_seq[i]);
printf(&quot;\n&quot;);
} else {
printf(&quot;\nSystem is in an UNSAFE state (deadlock may occur).\n&quot;);
return 0;
}
int p_id;
int request[R];
printf(&quot;\nEnter process number requesting resources: &quot;);
scanf(&quot;%d&quot;, &amp;p_id);
printf(&quot;Enter request vector (%d resources): &quot;, R);
for (j = 0; j &lt; R; j++)
scanf(&quot;%d&quot;, &amp;request[j]);
request_resources(p_id, request);
return 0;
}
