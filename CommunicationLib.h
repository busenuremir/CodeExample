#ifndef _COMMUNICATIONLIB_H    
#define _COMMUNICATIONLIB_H    

#include <stdint.h>
#include "TypeDefLib.h"
/*
######################################################################################################
############################################CENSORED##################################################
######################################################################################################
*/


void selectCommand(int commandByteValue);
void check_packet();
void sendGiroValues(int var);
void savePurchaseData();


void displayDailyPurchase();
void displayWeeklyPurchase();
void displayMonthlyPurchase();
void displayLastPurchases();

void sendSelection();
void sendAck();


#endif
