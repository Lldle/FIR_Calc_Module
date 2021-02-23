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

//�������������� (� ����� ��� ������ ����� �������� �� ����, ��� ���������� � ��� �������)
float Auto_Correlation_Function ( int16_t * Analyzed_array_first_element,
                                  int16_t   Array_size,
                                  int16_t   Start_Corr_Interval,
                                  int16_t   Corr_Interval_Count)
{
  float   Max_Auto_Corr_Value = 0;
  float   Auto_Corr_Value = 0;
  
  int16_t * Analyzed_array_addr;
  int16_t * Ref_array_addr;      
  uint16_t Summ_array_size;  
    
  for ( int16_t Corr_Interval = Start_Corr_Interval; 
                Corr_Interval < (Start_Corr_Interval + Corr_Interval_Count ); 
                Corr_Interval++ )
  {
    if( Corr_Interval > 0)
    {
       Analyzed_array_addr = Analyzed_array_first_element + abs(Corr_Interval);
       Ref_array_addr      = Analyzed_array_first_element;
       Summ_array_size     = Array_size - abs(Corr_Interval);
    }  else {
       Analyzed_array_addr = Analyzed_array_first_element;
       Ref_array_addr      = Analyzed_array_first_element + abs(Corr_Interval);
       Summ_array_size     = Array_size - abs(Corr_Interval);
    }
    
  for ( uint16_t Summation_Cycle = 0;                                                    //���������� �������� ������������� ������� ��� �������� ��������� �����������
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Auto_Corr_Value += (float)( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //��������������, ��� ������ ��� ��������� � ������ ������
         }
  
  Auto_Corr_Value /= Summ_array_size;                                                    //������ �� ���������� ��������� �����
  
    if(Auto_Corr_Value > Max_Auto_Corr_Value)
     {
        Max_Auto_Corr_Value = Auto_Corr_Value;
     }
  }
  return Max_Auto_Corr_Value;
}

//�������� ���������� (� ����� ��� ������ ����� �������� �� ����, ��� ���������� � ��� �������)
float Cross_Correlation_Function ( int16_t *  Analyzed_array_first_element,
                                   int16_t *  Ref_array_first_element,
                                   uint16_t   Array_size,
                                   int16_t   Start_Corr_Interval,
                                   int16_t   Corr_Interval_Count)
{
  float   Max_Cross_Corr_Value = 0;
  float   Cross_Corr_Value = 0;
  
  int16_t * Analyzed_array_addr;
  int16_t * Ref_array_addr;      
  uint16_t Summ_array_size;  
    
  for ( int16_t Corr_Interval = Start_Corr_Interval; 
                Corr_Interval < (Start_Corr_Interval + Corr_Interval_Count ); 
                Corr_Interval++ )
  {
    if( Corr_Interval > 0)
    {
       Analyzed_array_addr = Analyzed_array_first_element + abs(Corr_Interval);
       Ref_array_addr      = Ref_array_first_element;
       Summ_array_size     = Array_size - abs(Corr_Interval);
    }  else {
       Analyzed_array_addr = Analyzed_array_first_element;
       Ref_array_addr      = Ref_array_first_element      + abs(Corr_Interval);
       Summ_array_size     = Array_size - abs(Corr_Interval);
    }
    
  for ( uint16_t Summation_Cycle = 0;                                                    //���������� �������� ������������� ������� ��� �������� ��������� �����������
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Cross_Corr_Value += (float)( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //��������������, ��� ������ ��� ��������� � ������ ������
         }
  
  Cross_Corr_Value /= Summ_array_size;                                                    //������ �� ���������� ��������� �����
  
    if(Cross_Corr_Value > Max_Cross_Corr_Value)
     {
        Max_Cross_Corr_Value = Cross_Corr_Value;
     }
  }
  return Max_Cross_Corr_Value;
}