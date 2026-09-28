#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;pthread.h&gt;
#include &lt;semaphore.h&gt;
#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty; /* counts empty slots */
sem_t full; /* counts filled slots */
pthread_mutex_t mutex; /* protects buffer access */
void *producer(void *arg){
int item;
for (item = 1; item &lt;= ITEMS_TO_PRODUCE; item++) {
sem_wait(&amp;empty); /* wait for an empty slot */
pthread_mutex_lock(&amp;mutex); /* enter critical section */
buffer[in] = item;
printf(&quot;Producer produced item %d at slot %d\n&quot;, item, in);
in = (in + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&amp;mutex); /* leave critical section */
sem_post(&amp;full); /* signal a new filled slot */
usleep(100000); /* simulate production time */
}
return NULL;
}
void *consumer(void *arg){
int item;
for (int count = 1; count &lt;= ITEMS_TO_PRODUCE; count++) {
sem_wait(&amp;full); /* wait for a filled slot */
pthread_mutex_lock(&amp;mutex); /* enter critical section */
item = buffer[out];
printf(&quot;\tConsumer consumed item %d from slot %d\n&quot;, item, out);
out = (out + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&amp;mutex); /* leave critical section */
sem_post(&amp;empty); /* signal a new empty slot */
usleep(150000); /* simulate consumption time */
}
return NULL;
}
int main(){
pthread_t prod_thread, cons_thread;
sem_init(&amp;empty, 0, BUFFER_SIZE); /* initially all slots empty */
sem_init(&amp;full, 0, 0); /* initially no slots filled */
pthread_mutex_init(&amp;mutex, NULL);
pthread_create(&amp;prod_thread, NULL, producer, NULL);
pthread_create(&amp;cons_thread, NULL, consumer, NULL);
pthread_join(prod_thread, NULL);
pthread_join(cons_thread, NULL);
sem_destroy(&amp;empty);
sem_destroy(&amp;full);
pthread_mutex_destroy(&amp;mutex);
printf(&quot;\nAll items produced and consumed successfully.\n&quot;);
return 0;
}
