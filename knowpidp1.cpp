#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
struct sigaction sig;
pid_t p1,p2;
void hdfn(int sig,siginfo_t *siginfo, void *context)
{
	
	cout<<"now p1 got SIGUSR1 signal from p2\n";

	p2=siginfo->si_pid;

	cout<<"signal was sent from process p2 whose id is - "<<p2<<"\n";
	sleep(2);
	cout<<"sending KILL signal to p2";
	kill(p2,SIGINT);
	kill(p1,SIGINT);

}
int main()
{
	signal(SIGINT,SIG_DFL);
	      
      	sig.sa_sigaction =*hdfn;
	sig.sa_flags |= SA_SIGINFO;
	sigaction(SIGUSR1,&sig,NULL);

	cout<<"waiting for pid of process 2\n";
	key_t kx=ftok("x",65);
	int idx=shmget(kx,1024,0666|IPC_CREAT); 
	int *x=(int *) shmat(idx,(void*)0,0);   
	sleep(7);
	p2=*x;
	p1=getpid();
	cout<<"got pid of process p2, sending signal to process p2\n";
	kill(p2,SIGUSR2);
	
	while(1)
	shmdt(x);

}	
