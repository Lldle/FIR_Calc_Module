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

