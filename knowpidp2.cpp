#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<signal.h>
using namespace std;
struct sigaction sig;
pid_t p1;
void hdfn(int sig,siginfo_t *siginfo, void *context)
{
	cout<<"p2 got SIGUSR1 signal from p1\n";
	p1=siginfo->si_pid;
	cout<<"signal was sent from process "<<p1<<"\n";
	kill(p1,SIGUSR1);
	
}

int main()
{
	
	signal(SIGINT,SIG_DFL);
	sig.sa_sigaction =*hdfn; 
	sig.sa_flags |= SA_SIGINFO;  
	sigaction(SIGUSR2,&sig,NULL);

	
	key_t kx=ftok("x",65);
	int idx=shmget(kx,1024,0666|IPC_CREAT);
	int *x=(int *) shmat(idx,(void*)0,0);
	pid_t p2=getpid();
	*x=(int)p2;
	//raise(SIGUSR2);
	while(1)

	shmdt(x);
	shmctl(idx,IPC_RMID,NULL);
}
