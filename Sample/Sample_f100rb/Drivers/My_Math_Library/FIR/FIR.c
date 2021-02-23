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

