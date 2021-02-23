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

//Наибольший элемент массива float
float Max_Array_Value_f ( float * Input, int16_t Count )
{
  float Max_Value = *Input++;
  
  while (Count > 1)
  {
      float Current_Value = *Input++;
    
    if ( (Max_Value) < (Current_Value) )
      {
        Max_Value = Current_Value;    
      }
    Count--;
  }
  
  return Max_Value;
}

//Наименьший элемент массива float
float Min_Array_Value_f ( float * Input, int16_t Count )
{
  float Min_Value = *Input++;
  
  while (Count > 1)
  {
      float Current_Value = *Input++;
    
    if ( (Min_Value) > (Current_Value) )
      {
        Min_Value = Current_Value;    
      }
    Count--;
  }
  
  return Min_Value;
}

//Среднее значение массива float
float Mean_Array_Value_f ( float * Input, int16_t Count )
{
  float   Mean_Value = 0;
  int16_t Array_Count = Count;
  
  while (Count > 1)
  {
      Mean_Value += (*Input++) / Array_Count;    
      Count--;
  }
  
  return Mean_Value;
}

//Среднеквадратичное отклонение массива float
float RMS_Array_Value_f ( float * Input, int16_t Count )
{
  float   Mean_Value = Mean_Array_Value_f ( Input, Count );
  float   RMS_Value = 0;
  int16_t Array_Count = Count;
  
  while (Count > 1)
  {
      RMS_Value += ((*Input++) - Mean_Value) / Array_Count;    
      Count--;
  }
  RMS_Value = sqrtf(RMS_Value);
  return RMS_Value;
}