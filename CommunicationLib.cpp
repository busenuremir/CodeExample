#include "CommunicationLib.h"

extern  int int_data;

int incomingByte = 0;
uint8_t data_index = 0;
extern int data_ready_flag; 

int selectedDay;
int selectedWeek;
int selectedMonth;
int selectedPurchase;

extern account_t Sale ;
extern displayDataVal saleSt;
extern packet_status_t packet_status;
extern packet_t packet;
extern account_t Sale ;

extern dayDates_t dayDates[30];
extern weekDates_t weekDates[30];
extern monthDates_t monthDates[12];
extern lastPurchases_t lastPurchases[30];

void check_packet()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();

    switch (packet_status)
    {
      case protocol_stx:
        if (incomingByte == 0x2)
        {
          packet.stx = incomingByte;
          packet_status = protocol_cmd;
          //        Serial.println("Transmission started");
        }
        break;
        /*
        ######################################################################################################
        ############################################CENSORED##################################################
        ######################################################################################################
        */
      case protocol_data:
        packet.data_arr[data_index] = incomingByte;
        data_index++;
        if (data_index == packet.data_length) {
          packet_status = protocol_etx;
        }
        break;
      case protocol_etx:
        if (incomingByte == 0x3)
        {
          packet.etx = incomingByte;
          //          Serial.println("Transmission end");
          packet_status = protocol_stx;
          data_ready_flag = 1;
          //Serial.write(packet.data_arr, dataLengthInt);    
        }
        else
          packet_status = protocol_stx;

        break;
      default:
        break;
    }
  }
}

void selectCommand(int commandByteValue)
{
  switch (commandByteValue)
  {
    case sendSelectionWifi:
      sendSelection();
      break;
    case displayData:
      savePurchaseData();
      break;
    /*
    ######################################################################################################
    ############################################CENSORED##################################################
    ######################################################################################################
    */
    default:
      break;
  }
  memset(&packet, 0, sizeof(packet_t));
//  sendTotalGiroViaMQTT(); 
}

void sendGiroValues(int var)
{
  Serial.write(0x02);
  Serial.write(0x03);

  switch (var)
  {
    case totalGiro:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.totalGiro, sizeof(uint32_t));
      break;
    case temporalGiro:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.temporalGiro, sizeof(uint32_t));
      break;
    case cashBox:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.cashBox, sizeof(uint32_t));
      break;
    case banknote:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.banknote, sizeof(uint32_t));
      break;
    case saleViaCard:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.saleViaCard, sizeof(uint32_t));
      break;
    case coinOnTube:
      Serial.write(sizeof(uint32_t));
      Serial.write((uint8_t*)&Sale.coinOnTube, sizeof(uint32_t));
      break;
    case all:
      {

        int m = sizeof(Sale.saleOnSp) + sizeof(Sale.variableNames) + sizeof(Sale.saleOnRow) + sizeof(Sale.dailyPurchase) + sizeof(Sale.weeklyPurchase) + sizeof(Sale.monthlyPurchase) +
                sizeof(Sale.lastMonth) + sizeof(Sale.lastDay) + sizeof(Sale.dayOfWeek) + sizeof(Sale.monthlyIndex) +
                sizeof(Sale.weeklyIndex) + sizeof(Sale.dailyIndex) + sizeof(Sale.lastPurchaseIndex);
        Serial.write(sizeof(Sale) - m); //0x1C
        Serial.write((uint8_t*)&Sale, sizeof(Sale) - m);
      }
      break;
    default:
      break;
  }

  Serial.write(0x03);

}


void displayDailyPurchase()
{
  switch (packet.data_arr[0])
  {
    case 0:
      selectedDay = Sale.dailyIndex;
      break;
    case 1:
      selectedDay--;
      if (selectedDay < 0) {
        selectedDay = 0;
      }
      break;
    case 2:
      selectedDay++;
      if (selectedDay > Sale.dailyIndex) {
        selectedDay = Sale.dailyIndex;
      }
      break;
  }
  Serial.write(0x02);
  /*
  ######################################################################################################
  ############################################CENSORED##################################################
  ######################################################################################################
  */
  Serial.write((uint8_t*)&Sale.dailyPurchase[selectedDay], sizeof(uint32_t));
  Serial.write(dayDates[selectedDay].day);
  Serial.write(dayDates[selectedDay].month);
  Serial.write(dayDates[selectedDay].year);
  Serial.write(0x03);
}




/*
######################################################################################################
############################################CENSORED##################################################
######################################################################################################
*/
