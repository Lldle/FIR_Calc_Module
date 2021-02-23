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
//���������� ����������� �������� ������� (���������� �� DSP � �������������� �� ����������� ���������)
void Cmplx_mag_14bit     ( int16_t * Source_Array_First_Element,
                           int16_t * Destination_Array_First_Element,
                           uint32_t Samples_Number
                           )
{
  int16_t Accumulator_Re = 0;
  int16_t Accumulator_Im = 0;
  int16_t Real = 0;
  int16_t Imag = 0;
  
  while(Samples_Number > 0)
  {
    //����������� ����������
    Real = *Source_Array_First_Element++;
    Imag = *Source_Array_First_Element++;
    //���������� � �������
    Accumulator_Re = (int32_t) (Real * Real);
    Accumulator_Im = (int32_t) (Imag * Imag);
    //���������� ����������� ����� �� �����
    //����� ���� �������� ��� ������������� �� 14 ��� ���  ������������
    *Destination_Array_First_Element++ = (int16_t) sqrtf ((float) ( Accumulator_Re + Accumulator_Im ));
    Samples_Number--;
  }
}

//���������� / ����������� ������
void FIR_filtr ( int16_t * Input, 
                 int16_t * Output, 
                 uint16_t  Count, 
                 float * Coeff, 
                 uint16_t  Coef_Count )                        //����������� ������ ���� ��������!!!
{
  uint16_t Half_Coeff_Count = ( (uint16_t) (Coef_Count / 2) ); //�������������� ���� ������ ����������� 0.5
  
  int16_t * Output_ADDR_ARRAY = Output + Half_Coeff_Count;     //����� �� ������������� �������� ����� ������������� �����������
  
  for (uint16_t i = Half_Coeff_Count; i < (Count - Half_Coeff_Count); i++)      // Y = Sigma_n(Kn*Xn), ��� n - Coef_Count
  {
    int16_t * Input_ADDR = Input;
     float * Coeff_ADDR = Coeff;
     float Output_ADDR_ARRAY_float = 0;

   
   for (uint16_t g = 0; g < Coef_Count; g++)
   {
     Output_ADDR_ARRAY_float += ((*Coeff_ADDR++) * (float)(*Input_ADDR++));
   }

   *Input++;
   *Output_ADDR_ARRAY++ = ((int16_t) Output_ADDR_ARRAY_float) & 0xFFFE; 
  }
  
  int16_t * Output_ADDR_IN = Output + Half_Coeff_Count;                         //������ ��������� ������� ������������� �������� ������� ������������� � �������� ����� for
  
  for (uint16_t i = 0; i <= Half_Coeff_Count; i++)
  {
    *Output_ADDR_IN-- = *(Output + Half_Coeff_Count);
  }
    
  int16_t * Output_ADDR_OUT = Output + (Count - Half_Coeff_Count);              //��������� ��������� ������� ������������� �������� ������� ������������� � �������� ����� for
  
  for (uint16_t i = 0; i <= Half_Coeff_Count; i++)
  {
   *Output_ADDR_OUT++ = *( Output + (Count - Half_Coeff_Count) ); 
  }
  
}

//���������� ������� ������� int16_t
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

//���������� ������� ������� int16_t
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

//���������� ������� ������� float
float Max_Array_Value ( float * Input, int16_t Count )
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

//���������� ������� ������� float
float Min_Array_Value ( float * Input, int16_t Count )
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

//���������� ������� (���������� � �������� � 1 ����) 
void Array_Normalization ( int16_t * Input,
                           int16_t * Output,
                           int16_t   Count,
                           int16_t   Norm_Value )
{
  int16_t * Input_Norm = Input;
    while (Count > 0)
  {
     *Output++ = (int16_t) (0xFF * (*Input_Norm++) / Norm_Value);
      Count--;
  } 
}

//�������������� (� ����� ��� ������ ����� �������� �� ����, ��� ���������� � ��� �������)
float Auto_Correlation_Function ( int16_t * Analyzed_array_first_element,
                                  int16_t   Array_size,
                                 uint16_t   Corr_Interval)
{
  float   Auto_Corr_Value = 0;
  int16_t * Analyzed_array_addr = Analyzed_array_first_element + Corr_Interval;
  int16_t * Ref_array_addr      = Analyzed_array_first_element;
  uint16_t Summ_array_size    = Array_size - abs(Corr_Interval);
           
  for ( uint16_t Summation_Cycle = 0;                                                    //���������� �������� ������������� ������� ��� �������� ��������� �����������
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Auto_Corr_Value += (float)( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //��������������, ��� ������ ��� ��������� � ������ ������
         }
  
  Auto_Corr_Value /= Summ_array_size;                                                    //������ �� ���������� ��������� �����
  return Auto_Corr_Value;
}

//�������� ���������� (� ����� ��� ������ ����� �������� �� ����, ��� ���������� � ��� �������)
float Cross_Correlation_Function ( int16_t *  Analyzed_array_first_element,
                                   int16_t *  Ref_array_first_element,
                                   uint16_t   Array_size,
                                   int16_t    Corr_Interval)
{
  int16_t * Analyzed_array_addr;
  int16_t * Ref_array_addr;        
  
  float   Cross_Corr_Value = 0;
  if (Corr_Interval >= 0)
  {
    Analyzed_array_addr = Analyzed_array_first_element + abs(Corr_Interval);
    Ref_array_addr      = Ref_array_first_element;
  } else {
    Analyzed_array_addr = Analyzed_array_first_element;
    Ref_array_addr      = Ref_array_first_element + abs(Corr_Interval);
  }
  uint16_t Summ_array_size    = Array_size - abs(Corr_Interval);
           
  for ( uint16_t Summation_Cycle = 0;                                              //���������� �������� ������������� ������� ��� �������� ��������� �����������
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Cross_Corr_Value += ( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //��������������, ��� ������ ��� ��������� � ������ ������
         }
  
  Cross_Corr_Value /= Summ_array_size;                                             //������ �� ���������� ��������� �����
  return Cross_Corr_Value;
}