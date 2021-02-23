/*****************************************************************************/
/**                                                                         **/
/**                           FIR CALC MODULE                               **/
/**                                                                         **/
/*****************************************************************************/
/**                                                                         **/
/**    Функции используют быстрое преобразование Фурье для пересчета        **/
/**    АФЧХ фильтра в коэффициенты КИХ.                                     **/
/**                                                                         **/
/*****************************************************************************/
#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "arm_math.h"
#include "arm_const_structs.h"

#include "FIR_Calc_Module.h"


//Расчёт коэффициентов полосового фильтра
void Calc_BAND_PASS_Coeff         (    float *           Destination_Array,      //Указатель на массив коэффицентов
                                    uint16_t             Low__Freq_Threshold,    //Нижняя частота среза
                                    uint16_t             High_Freq_Threshold,    //Верхняя частота среза
                                    Filter_Points_Count  Coeff_Count             //Количество коэффициентов фильтра
                                  )
{
   float * Local_Destination_Array = Destination_Array;
   
   uint16_t N_Coeff;
   arm_cfft_instance_f32 FFT_Config;

  switch(Coeff_Count)
    {
      case(Filter_Points_32)  : N_Coeff = 32;   FFT_Config = arm_cfft_sR_f32_len16;   break;
      case(Filter_Points_64)  : N_Coeff = 64;   FFT_Config = arm_cfft_sR_f32_len32;   break;
      case(Filter_Points_128) : N_Coeff = 128;  FFT_Config = arm_cfft_sR_f32_len64;   break;
      case(Filter_Points_256) : N_Coeff = 256;  FFT_Config = arm_cfft_sR_f32_len128;  break;     
      case(Filter_Points_512) : N_Coeff = 512;  FFT_Config = arm_cfft_sR_f32_len256;  break;
      case(Filter_Points_1024): N_Coeff = 1024; FFT_Config = arm_cfft_sR_f32_len512;  break;     
      case(Filter_Points_2048): N_Coeff = 2048; FFT_Config = arm_cfft_sR_f32_len1024; break;
      case(Filter_Points_4096): N_Coeff = 4096; FFT_Config = arm_cfft_sR_f32_len2048; break;    
      case(Filter_Points_8192): N_Coeff = 8192; FFT_Config = arm_cfft_sR_f32_len4096; break;     
    }
  
   Low__Freq_Threshold /= 2;      //Костыль :-(
   High_Freq_Threshold /= 2;
   N_Coeff             /= 2;
   
  float Mag;
  float Phase;
  
  for (uint16_t k_Coeff = 0; k_Coeff < N_Coeff; k_Coeff++)
    {
      float Mag_exp_Val_1, Mag_exp_Val_2;
      float Mag_exp_Val_1_Full, Mag_exp_Val_2_Full;
      
      Mag_exp_Val_1 = exp( ( 2 * PI / N_Coeff ) * ( Low__Freq_Threshold - k_Coeff ) );
      Mag_exp_Val_2 = exp( ( 2 * PI / N_Coeff ) * ( k_Coeff - High_Freq_Threshold ) );  
  
      Mag_exp_Val_1_Full = Mag_exp_Val_1;
      Mag_exp_Val_2_Full = Mag_exp_Val_2;
      
      for (uint8_t n = 0; n < 8; n++)                                            //Меняя число итераций, можно изменять крутизну фильтра
          {
             Mag_exp_Val_1_Full *= Mag_exp_Val_1;
             Mag_exp_Val_2_Full *= Mag_exp_Val_2;
          }
      
      Mag   = (1 / ( Mag_exp_Val_1_Full + 1 )  ) 
            + (1 / ( Mag_exp_Val_2_Full + 1 )  )
            - 1;
      
      if ( k_Coeff <= ( ( N_Coeff - 1 ) / 2 ) )
      {
      Phase = (-1) * (N_Coeff - 1) *  PI * k_Coeff / N_Coeff;
      } else {
      Phase = (-1) * (N_Coeff - 1) * PI * (k_Coeff - N_Coeff) / N_Coeff ;
      }
      
      *Local_Destination_Array++ = Mag * sin( Phase );
      *Local_Destination_Array++ = Mag * cos( Phase );
    }
  
  arm_cfft_f32( &FFT_Config, Destination_Array, 1, 1 );
  
}
//Расчёт коэффициентов фильтра низких частот
void Calc_LOW_PASS_Coeff  (    float *           Destination_Array,              //Указатель на массив коэффицентов
                            uint16_t             High_Freq_Threshold,            //Верхняя частота среза
                            Filter_Points_Count  Coeff_Count                     //Количество коэффициентов фильтра
                          )                                                      
{
   float * Local_Destination_Array = Destination_Array;
   
   uint16_t N_Coeff;
   arm_cfft_instance_f32 FFT_Config;

  switch(Coeff_Count)
    {
      case(Filter_Points_32)  : N_Coeff = 32;   FFT_Config = arm_cfft_sR_f32_len16;   break;
      case(Filter_Points_64)  : N_Coeff = 64;   FFT_Config = arm_cfft_sR_f32_len32;   break;
      case(Filter_Points_128) : N_Coeff = 128;  FFT_Config = arm_cfft_sR_f32_len64;   break;
      case(Filter_Points_256) : N_Coeff = 256;  FFT_Config = arm_cfft_sR_f32_len128;  break;     
      case(Filter_Points_512) : N_Coeff = 512;  FFT_Config = arm_cfft_sR_f32_len256;  break;
      case(Filter_Points_1024): N_Coeff = 1024; FFT_Config = arm_cfft_sR_f32_len512;  break;     
      case(Filter_Points_2048): N_Coeff = 2048; FFT_Config = arm_cfft_sR_f32_len1024; break;
      case(Filter_Points_4096): N_Coeff = 4096; FFT_Config = arm_cfft_sR_f32_len2048; break;    
      case(Filter_Points_8192): N_Coeff = 8192; FFT_Config = arm_cfft_sR_f32_len4096; break;     
    }
  
   High_Freq_Threshold /= 2;
   N_Coeff             /= 2;
   
  float Mag;
  float Phase;
  
  for (uint16_t k_Coeff = 0; k_Coeff < N_Coeff; k_Coeff++)
    {
      float Mag_exp_Val_2;
      float Mag_exp_Val_2_Full;
      
      
      Mag_exp_Val_2 = exp( ( 2 * PI / N_Coeff ) * ( k_Coeff - High_Freq_Threshold ) );  
      Mag_exp_Val_2_Full = Mag_exp_Val_2;
      
      for (uint8_t n = 0; n < 8; n++)
          {
             Mag_exp_Val_2_Full *= Mag_exp_Val_2;
          }
      
      Mag   = 1 / ( Mag_exp_Val_2_Full + 1 );
      
      if ( k_Coeff <= ( ( N_Coeff - 1 ) / 2 ) )
      {
      Phase = (-1) * (N_Coeff - 1) *  PI * k_Coeff / N_Coeff;
      } else {
      Phase = (-1) * (N_Coeff - 1) * PI * (k_Coeff - N_Coeff) / N_Coeff ;
      }
      
      *Local_Destination_Array++ = Mag * sin( Phase );
      *Local_Destination_Array++ = Mag * cos( Phase );
    }
  
  arm_cfft_f32( &FFT_Config, Destination_Array, 1, 1 );
  
}
//Расчёт коэффициентов фильтра высоких частот
void Calc_HIGH_PASS_Coeff         (    float *           Destination_Array,      //Указатель на массив коэффицентов
                                    uint16_t             Low__Freq_Threshold,    //Нижняя частота среза
                                    Filter_Points_Count  Coeff_Count             //Количество коэффициентов фильтра
                                  )
{
   float * Local_Destination_Array = Destination_Array;
   
   uint16_t N_Coeff;
   arm_cfft_instance_f32 FFT_Config;

  switch(Coeff_Count)
    {
      case(Filter_Points_32)  : N_Coeff = 32;   FFT_Config = arm_cfft_sR_f32_len16;   break;
      case(Filter_Points_64)  : N_Coeff = 64;   FFT_Config = arm_cfft_sR_f32_len32;   break;
      case(Filter_Points_128) : N_Coeff = 128;  FFT_Config = arm_cfft_sR_f32_len64;   break;
      case(Filter_Points_256) : N_Coeff = 256;  FFT_Config = arm_cfft_sR_f32_len128;  break;     
      case(Filter_Points_512) : N_Coeff = 512;  FFT_Config = arm_cfft_sR_f32_len256;  break;
      case(Filter_Points_1024): N_Coeff = 1024; FFT_Config = arm_cfft_sR_f32_len512;  break;     
      case(Filter_Points_2048): N_Coeff = 2048; FFT_Config = arm_cfft_sR_f32_len1024; break;
      case(Filter_Points_4096): N_Coeff = 4096; FFT_Config = arm_cfft_sR_f32_len2048; break;    
      case(Filter_Points_8192): N_Coeff = 8192; FFT_Config = arm_cfft_sR_f32_len4096; break;     
    }
  
   Low__Freq_Threshold /= 2;
   N_Coeff             /= 2;
   
  float Mag;
  float Phase;
  
  for (uint16_t k_Coeff = 0; k_Coeff < N_Coeff; k_Coeff++)
    {
      float Mag_exp_Val_1;
      float Mag_exp_Val_1_Full;
      
      Mag_exp_Val_1 = exp( ( 2 * PI / N_Coeff ) * ( Low__Freq_Threshold - k_Coeff ) );  
      Mag_exp_Val_1_Full = Mag_exp_Val_1;
      
      for (uint8_t n = 0; n < 8; n++)
          {
             Mag_exp_Val_1_Full *= Mag_exp_Val_1;
          }
      
      Mag   = 1 / ( Mag_exp_Val_1_Full + 1);
      
      if ( k_Coeff <= ( ( N_Coeff - 1 ) / 2 ) )
      {
      Phase = (-1) * (N_Coeff - 1) *  PI * k_Coeff / N_Coeff;
      } else {
      Phase = (-1) * (N_Coeff - 1) * PI * (k_Coeff - N_Coeff) / N_Coeff ;
      }
      
      *Local_Destination_Array++ = Mag * sin( Phase );
      *Local_Destination_Array++ = Mag * cos( Phase );
    }
  
  arm_cfft_f32( &FFT_Config, Destination_Array, 1, 1 );
  
}
//Расчёт коэффициентов полосно-заграждающего фильтра
void Calc_BAND_STOP_PASS_Coeff    (    float *           Destination_Array,       //Указатель на массив коэффицентов
                                    uint16_t             Low__Freq_Threshold,     //Нижняя частота среза
                                    uint16_t             High_Freq_Threshold,     //Верхняя частота среза
                                    Filter_Points_Count  Coeff_Count              //Количество коэффициентов фильтра
                                  )
{
   float * Local_Destination_Array = Destination_Array;
   
   uint16_t N_Coeff;
   arm_cfft_instance_f32 FFT_Config;

  switch(Coeff_Count)
    {
      case(Filter_Points_32)  : N_Coeff = 32;   FFT_Config = arm_cfft_sR_f32_len16;   break;
      case(Filter_Points_64)  : N_Coeff = 64;   FFT_Config = arm_cfft_sR_f32_len32;   break;
      case(Filter_Points_128) : N_Coeff = 128;  FFT_Config = arm_cfft_sR_f32_len64;   break;
      case(Filter_Points_256) : N_Coeff = 256;  FFT_Config = arm_cfft_sR_f32_len128;  break;     
      case(Filter_Points_512) : N_Coeff = 512;  FFT_Config = arm_cfft_sR_f32_len256;  break;
      case(Filter_Points_1024): N_Coeff = 1024; FFT_Config = arm_cfft_sR_f32_len512;  break;     
      case(Filter_Points_2048): N_Coeff = 2048; FFT_Config = arm_cfft_sR_f32_len1024; break;
      case(Filter_Points_4096): N_Coeff = 4096; FFT_Config = arm_cfft_sR_f32_len2048; break;    
      case(Filter_Points_8192): N_Coeff = 8192; FFT_Config = arm_cfft_sR_f32_len4096; break;     
    }
  
   Low__Freq_Threshold /= 2;
   High_Freq_Threshold /= 2;
   N_Coeff             /= 2;
   
  float Mag;
  float Phase;
  
  for (uint16_t k_Coeff = 0; k_Coeff < N_Coeff; k_Coeff++)
    {
      float Mag_exp_Val_1, Mag_exp_Val_2;
      float Mag_exp_Val_1_Full, Mag_exp_Val_2_Full;
      
      Mag_exp_Val_1 = exp( ( 2 * PI / N_Coeff ) * ( k_Coeff - Low__Freq_Threshold ) );
      Mag_exp_Val_2 = exp( ( 2 * PI / N_Coeff ) * ( High_Freq_Threshold - k_Coeff ) );  
  
      Mag_exp_Val_1_Full = Mag_exp_Val_1;
      Mag_exp_Val_2_Full = Mag_exp_Val_2;
      
      for (uint8_t n = 0; n < 8; n++)
          {
             Mag_exp_Val_1_Full *= Mag_exp_Val_1;
             Mag_exp_Val_2_Full *= Mag_exp_Val_2;
          }
      
      Mag   = (1 / ( Mag_exp_Val_1_Full + 1 )  ) 
            + (1 / ( Mag_exp_Val_2_Full + 1 )  );
      
      if ( k_Coeff <= ( ( N_Coeff - 1 ) / 2 ) )
      {
      Phase = (-1) * (N_Coeff - 1) *  PI * k_Coeff / N_Coeff;
      } else {
      Phase = (-1) * (N_Coeff - 1) * PI * (k_Coeff - N_Coeff) / N_Coeff ;
      }
      
      *Local_Destination_Array++ = Mag * sin( Phase );
      *Local_Destination_Array++ = Mag * cos( Phase );
    }
  
  arm_cfft_f32( &FFT_Config, Destination_Array, 1, 1 );
  
}