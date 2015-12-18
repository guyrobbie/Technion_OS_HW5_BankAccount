#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#define ACCOUNT_NUM_LEN             5

#define OPEN_CMD_NUM_OF_ARG         3
#define DEPOSIT_CMD_NUM_OF_ARG      3
#define WITHDRAW_CMD_NUM_OF_ARG     3
#define BALANCE_CMD_NUM_OF_ARG      2
#define TRANSFER_CMD_NUM_OF_ARG     4

typedef struct _account{
    unsigned int    number;
    unsigned int    balance;
    unsigned int    password;
    }Account, *pAccount;





#endif // #ifndef _ACCOUNT_H_