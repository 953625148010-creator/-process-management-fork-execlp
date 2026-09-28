#include &lt;stdio.h&gt;
int main(){
int n, i, tq;
int bt[20], at[20], rem_bt[20], wt[20], tat[20];
float total_wt = 0, total_tat = 0;
printf(&quot;Enter number of processes: &quot;);
scanf(&quot;%d&quot;, &amp;n);
printf(&quot;Enter Arrival Time and Burst Time for each process:\n&quot;);
for (i = 0; i &lt; n; i++) {
printf(&quot;P%d - Arrival Time: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;at[i]);
printf(&quot;P%d - Burst Time: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;bt[i]);
rem_bt[i] = bt[i];
}
printf(&quot;Enter Time Quantum: &quot;);
scanf(&quot;%d&quot;, &amp;tq);
int current_time = 0, completed = 0;
int queue[1000], front = 0, rear = 0;
int in_queue[20] = {0};
for (i = 0; i &lt; n; i++) {
if (at[i] &lt;= current_time &amp;&amp; !in_queue[i]) {
queue[rear++] = i;
in_queue[i] = 1;
}
}

DEEPTHI PRABHAKARAN.P

953625148010

Page 12

while (completed != n) {
if (front == rear) {
current_time++;
for (i = 0; i &lt; n; i++)
if (at[i] &lt;= current_time &amp;&amp; !in_queue[i] &amp;&amp; rem_bt[i] &gt; 0) {
queue[rear++] = i;
in_queue[i] = 1;
}
continue;
}
int idx = queue[front++];
if (rem_bt[idx] &gt; tq) {
current_time += tq;
rem_bt[idx] -= tq;
} else {
current_time += rem_bt[idx];
wt[idx] = current_time - at[idx] - bt[idx];
tat[idx] = current_time - at[idx];
rem_bt[idx] = 0;
completed++;
}
for (i = 0; i &lt; n; i++)
if (at[i] &lt;= current_time &amp;&amp; !in_queue[i] &amp;&amp; rem_bt[i] &gt; 0) {
queue[rear++] = i;
in_queue[i] = 1;
}
if (rem_bt[idx] &gt; 0)
queue[rear++] = idx;
}
printf(&quot;\nProcess\tAT\tBT\tWT\tTAT\n&quot;);
for (i = 0; i &lt; n; i++) {
total_wt += wt[i];
total_tat += tat[i];
printf(&quot;P%d\t%d\t%d\t%d\t%d\n&quot;, i + 1, at[i], bt[i], wt[i], tat[i]);
}
printf(&quot;\nAverage Waiting Time = %.2f\n&quot;, total_wt / n);
printf(&quot;Average Turnaround Time = %.2f\n&quot;, total_tat / n);
return 0;
}
