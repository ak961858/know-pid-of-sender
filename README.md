# know-pid-of-sender
 it has two process p1 and p2
 and it needs little modification of signal handler func
 
 p1
 sends signal to p2
 waits for p2 to recieve the signal
 and catches the signal sent back by p2
 
 p2
 catches the signal,identifies the pid of the sender(here p1)
 and sends a signal back to the sender
