#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;pthread.h&gt;
#include &lt;semaphore.h&gt;
#define N 5
#define MEALS 3
sem_t forks[N];
sem_t room;
void think(int id){
printf(&quot;Philosopher %d is thinking.\n&quot;, id);
usleep(100000);
}
void eat(int id){
printf(&quot;Philosopher %d is eating.\n&quot;, id);
usleep(100000);
}
void *philosopher(void *arg){
int id = *(int *)arg;
int left = id;
int right = (id + 1) % N;
for (int m = 0; m &lt; MEALS; m++) {
think(id);
sem_wait(&amp;room);
sem_wait(&amp;forks[left]);
printf(&quot;Philosopher %d picked up left fork %d\n&quot;, id, left);
sem_wait(&amp;forks[right]);

DEEPTHI PRABHAKARAN.P

953625148010

Page 21

printf(&quot;Philosopher %d picked up right fork %d\n&quot;, id, right);
eat(id);
sem_post(&amp;forks[right]);
sem_post(&amp;forks[left]);
printf(&quot;Philosopher %d put down both forks.\n&quot;, id);
sem_post(&amp;room);
}
return NULL;
}
int main(){
pthread_t phil[N];
int ids[N];
for (int i = 0; i &lt; N; i++)
sem_init(&amp;forks[i], 0, 1);
sem_init(&amp;room, 0, N - 1);
for (int i = 0; i &lt; N; i++) {
ids[i] = i;
pthread_create(&amp;phil[i], NULL, philosopher, &amp;ids[i]);
}
for (int i = 0; i &lt; N; i++)
pthread_join(phil[i], NULL);
for (int i = 0; i &lt; N; i++)
sem_destroy(&amp;forks[i]);
sem_destroy(&amp;room);
printf(&quot;\nAll philosophers have finished eating. No deadlock occurred.\n&quot;);
return 0;
}
