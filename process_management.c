#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/wait.h&gt;
int main(){
pid_t pid;
int status;
printf(&quot;Parent process: PID = %d\n&quot;, getpid());
pid = fork();
if (pid &lt; 0) {
perror(&quot;fork failed&quot;);
exit(1);
}
else if (pid == 0) {
printf(&quot;Child process: PID = %d, Parent PID = %d\n&quot;,getpid(), getppid());
printf(&quot;Child is about to execute &#39;ls -l&#39; using execlp()\n&quot;);
execlp(&quot;ls&quot;, &quot;ls&quot;, &quot;-l&quot;, NULL);
perror(&quot;execlp failed&quot;);
exit(1);
}
else {
printf(&quot;Parent waiting for child (PID = %d) to finish...\n&quot;, pid);
wait(&amp;status);
if (WIFEXITED(status))
printf(&quot;Child terminated normally with exit code %d\n&quot;,
WEXITSTATUS(status));
else
printf(&quot;Child terminated abnormally\n&quot;);

DEEPTHI PRABHAKARAN.P

953625148010

Page 4
printf(&quot;Parent process finished execution.\n&quot;);
}
return 0;
}
Sample Output
