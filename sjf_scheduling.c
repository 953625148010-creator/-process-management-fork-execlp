#include &lt;stdio.h&gt;
int main(){
int n, i;
int bt[20], at[20], wt[20], tat[20], done[20];
float total_wt = 0, total_tat = 0;
int completed = 0, current_time = 0;
printf(&quot;Enter number of processes: &quot;);
scanf(&quot;%d&quot;, &amp;n);
printf(&quot;Enter Arrival Time and Burst Time for each process:\n&quot;);
for (i = 0; i &lt; n; i++) {
printf(&quot;P%d - Arrival Time: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;at[i]);
printf(&quot;P%d - Burst Time: &quot;, i + 1);
scanf(&quot;%d&quot;, &amp;bt[i]);
done[i] = 0;
}
while (completed != n) {
int idx = -1;
int min_bt = 1000000;
for (i = 0; i &lt; n; i++) {
if (!done[i] &amp;&amp; at[i] &lt;= current_time) {
if (bt[i] &lt; min_bt) {
min_bt = bt[i];
idx = i;
}
}
}

DEEPTHI PRABHAKARAN.P

953625148010

Page 10

if (idx == -1) {
current_time++;
continue;
}
wt[idx] = current_time - at[idx];
current_time += bt[idx];
tat[idx] = current_time - at[idx];
done[idx] = 1;
completed++;
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
