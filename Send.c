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

    key = ftok("message_q_key ", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }


    msg.mtype = 1;  
    printf("Enter a message to send: ");
    fgets(msg.mtext, sizeof(msg.mtext), stdin);


    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1)
   {
        perror("msgsnd");
        exit(1);
    }

    printf("MESSAGE SENT SUCCESSFULLY  !\n");

    return 0;
}