#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct message
{
    long mtype;
    char mtext[100];
};

int main()
{
    key_t key;
    int msgid;
    struct message msg;

 
    key = ftok("message_q_key", 65);

   
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

   
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1)
    {
        perror("msgrcv");
        exit(1);
    }

    printf("RECEIVED MESSAGE: %s\n", msg.mtext);

    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    return 0;
}