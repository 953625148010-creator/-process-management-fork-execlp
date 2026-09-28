#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;unistd.h&gt;
#include &lt;fcntl.h&gt;
#include &lt;sys/stat.h&gt;
#define BUF_SIZE 1024
int main(int argc, char *argv[]){
int src_fd, dest_fd;
ssize_t n_read;
char buffer[BUF_SIZE];
char src_name[100], dest_name[100];
if (argc == 3) {
snprintf(src_name, sizeof(src_name), &quot;%s&quot;, argv[1]);
snprintf(dest_name, sizeof(dest_name), &quot;%s&quot;, argv[2]);
} else {
printf(&quot;Enter source file name: &quot;);
scanf(&quot;%99s&quot;, src_name);
printf(&quot;Enter destination file name: &quot;);
scanf(&quot;%99s&quot;, dest_name);
}
src_fd = open(src_name, O_RDONLY);
if (src_fd &lt; 0) {
perror(&quot;Error opening source file&quot;);
exit(1);
}
dest_fd = open(dest_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (dest_fd &lt; 0) {
perror(&quot;Error opening destination file&quot;);

DEEPTHI PRABHAKARAN.P

953625148010

Page 6

close(src_fd);
exit(1);
}
while ((n_read = read(src_fd, buffer, BUF_SIZE)) &gt; 0) {
if (write(dest_fd, buffer, n_read) != n_read) {
perror(&quot;Error writing to destination file&quot;);
close(src_fd);
close(dest_fd);
exit(1);
}
}
if (n_read &lt; 0)
perror(&quot;Error reading source file&quot;);
else
printf(&quot;File &#39;%s&#39; copied to &#39;%s&#39; successfully.\n&quot;, src_name, dest_name);
close(src_fd);
close(dest_fd);
return 0;
}
