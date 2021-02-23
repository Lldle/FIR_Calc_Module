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
//Вычисление комплексных амплитуд массива (переписано из DSP и оптимизировано до работающего состояния)
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
    //Комплексное сопряжение
    Real = *Source_Array_First_Element++;
    Imag = *Source_Array_First_Element++;
    //Возведение в квадрат
    Accumulator_Re = (int32_t) (Real * Real);
    Accumulator_Im = (int32_t) (Imag * Imag);
    //Вычисление квадратного корня от суммы
    //Такой путь допустим при использовании до 14 бит АЦП  включительно
    *Destination_Array_First_Element++ = (int16_t) sqrtf ((float) ( Accumulator_Re + Accumulator_Im ));
    Samples_Number--;
  }
}

//Фильтрация / сглаживание данных
void FIR_filtr ( int16_t * Input, 
                 int16_t * Output, 
                 uint16_t  Count, 
                 float * Coeff, 
                 uint16_t  Coef_Count )                        //Обязательно должно быть нечетным!!!
{
  uint16_t Half_Coeff_Count = ( (uint16_t) (Coef_Count / 2) ); //Преобразование типа должно отбрасывать 0.5
  
  int16_t * Output_ADDR_ARRAY = Output + Half_Coeff_Count;     //Сдвиг на целочисленную половину числа коэффициентов сглаживания
  
  for (uint16_t i = Half_Coeff_Count; i < (Count - Half_Coeff_Count); i++)      // Y = Sigma_n(Kn*Xn), где n - Coef_Count
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
  
  int16_t * Output_ADDR_IN = Output + Half_Coeff_Count;                         //первым элементам массива присваивается значение Первого Обработанного в основном цикле for
  
  for (uint16_t i = 0; i <= Half_Coeff_Count; i++)
  {
    *Output_ADDR_IN-- = *(Output + Half_Coeff_Count);
  }
    
  int16_t * Output_ADDR_OUT = Output + (Count - Half_Coeff_Count);              //последним элементам массива присваивается значение Первого Обработанного в основном цикле for
  
  for (uint16_t i = 0; i <= Half_Coeff_Count; i++)
  {
   *Output_ADDR_OUT++ = *( Output + (Count - Half_Coeff_Count) ); 
  }
  
}

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

//Наибольший элемент массива float
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

//Наименьший элемент массива float
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

//Нормировка массива (Приводится к масштабу в 1 байт) 
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

//Автокорреляция (К одной оси данные нужно привести до того, как передавать в эту функцию)
float Auto_Correlation_Function ( int16_t * Analyzed_array_first_element,
                                  int16_t   Array_size,
                                 uint16_t   Corr_Interval)
{
  float   Auto_Corr_Value = 0;
  int16_t * Analyzed_array_addr = Analyzed_array_first_element + Corr_Interval;
  int16_t * Ref_array_addr      = Analyzed_array_first_element;
  uint16_t Summ_array_size    = Array_size - abs(Corr_Interval);
           
  for ( uint16_t Summation_Cycle = 0;                                                    //Вычисление значения корреляционой функции для текущего интервала расхождения
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Auto_Corr_Value += (float)( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //Предполагается, что данные уже приведены к одному уровню
         }
  
  Auto_Corr_Value /= Summ_array_size;                                                    //Делить на количество элементов суммы
  return Auto_Corr_Value;
}

//Взаимная корреляция (К одной оси данные нужно привести до того, как передавать в эту функцию)
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
           
  for ( uint16_t Summation_Cycle = 0;                                              //Вычисление значения корреляционой функции для текущего интервала расхождения
                 Summation_Cycle < Summ_array_size; 
                 Summation_Cycle++ )
         {
           Cross_Corr_Value += ( *Ref_array_addr++ ) * ( *Analyzed_array_addr++ ); //Предполагается, что данные уже приведены к одному уровню
         }
  
  Cross_Corr_Value /= Summ_array_size;                                             //Делить на количество элементов суммы
  return Cross_Corr_Value;
}