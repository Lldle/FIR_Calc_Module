/*****************************************************************************/
/**                                                                         **/
/**                           Custom Math                                   **/
/**                                                                         **/
/*****************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"
/* ----------------------- Platform includes --------------------------------*/
#include "Custom_Math.h"

/* ----------------------- Start implementation -----------------------------*/

//Наибольший элемент массива int16_t
int16_t Max_Array_Value_int (  int16_t * Input, int16_t Count )
{
  int16_t Max_Value = *Input++;
  
  while (Count > 1)
  {
      int16_t Current_Value = *Input++;
    
    if ( (Max_Value) < (Current_Value) )
      {
        Max_Value = Current_Value;    
      }
    Count--;
  }
  
  return Max_Value;
}

//Наименьший элемент массива int16_t
int16_t Min_Array_Value_int (  int16_t * Input, int16_t Count )
{
  int16_t Min_Value = *Input++;
  
  while (Count > 1)
  {
      int16_t Current_Value = *Input++;
    
    if ( (Min_Value) > (Current_Value) )
      {
        Min_Value = Current_Value;    
      }
    Count--;
  }
  
  return Min_Value;
}

//Среднее значение массива int16_t
int16_t Mean_Array_Value_int (  int16_t * Input, int16_t Count )
{
  float   Mean_Value = 0;
  int16_t Array_Count = Count;
  
  while (Count > 1)
  {
      Mean_Value += (*Input++) / Array_Count;    
      Count--;
  }
  
  return (int16_t) Mean_Value;
}

//Среднеквадратичное отклонение массива int16_t
int16_t RMS_Array_Value_int ( int16_t * Input, int16_t Count )
{
  int16_t Mean_Value = Mean_Array_Value_int ( Input, Count );
  float   RMS_Value = 0;
  int16_t Array_Count = Count;
  
  while (Count > 1)
  {
      RMS_Value += ((*Input++) - Mean_Value) / Array_Count;    
      Count--;
  }
  RMS_Value = sqrtf(RMS_Value);
  return (int16_t) RMS_Value;
}