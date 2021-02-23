#ifndef __CUSTOM_MATH
#define __CUSTOM_MATH

#include "main.h"
#include "math.h"

typedef enum
{
  Filter_Points_32,
  Filter_Points_64,
  Filter_Points_128,
  Filter_Points_256,
  Filter_Points_512,
  Filter_Points_1024,
  Filter_Points_2048,
  Filter_Points_4096,
  Filter_Points_8192
} Filter_Points_Count;


extern void  Calc_BAND_PASS_Coeff      (    float *           Destination_Array,
                                         uint16_t             Low__Freq_Threshold,
                                         uint16_t             High_Freq_Threshold,
                                         Filter_Points_Count  Coeff_Count);

extern void  Calc_LOW_PASS_Coeff       (    float *           Destination_Array,
                                         uint16_t             High_Freq_Threshold,
                                         Filter_Points_Count  Coeff_Count);

extern void  Calc_HIGH_PASS_Coeff      (    float *           Destination_Array,
                                         uint16_t             Low__Freq_Threshold,
                                         Filter_Points_Count  Coeff_Count);

extern void  Calc_BAND_STOP_PASS_Coeff (    float *           Destination_Array,
                                         uint16_t             Low__Freq_Threshold,
                                         uint16_t             High_Freq_Threshold,
                                         Filter_Points_Count  Coeff_Count);



#endif /*__CUSTOM_MATH*/