#ifndef __CUSTOM_MATH
#define __CUSTOM_MATH
/* ----------------------- Platform defines ---------------------------------*/
#include "main.h"
#include "math.h"

/* ----------------------- Function prototypes ------------------------------*/
extern void Cmplx_mag_14bit ( int16_t * Source_Array_First_Element,
                              int16_t * Destination_Array_First_Element,
                              uint32_t Samples_Number);

extern void FIR_filtration (  int16_t * Input, 
                              int16_t * Output, 
                             uint16_t   Count, 
                                float * Coeff, 
                             uint16_t   Coef_Count );

extern int16_t Max_Array_Value_int  (  int16_t * Input, int16_t Count );

extern int16_t Min_Array_Value_int  (  int16_t * Input, int16_t Count );

extern int16_t Mean_Array_Value_int (  int16_t * Input, int16_t Count );

extern int16_t RMS_Array_Value_int  (  int16_t * Input, int16_t Count );

extern float Max_Array_Value_f  (  float * Input, int16_t Count );

extern float Min_Array_Value_f  (  float * Input, int16_t Count );

extern float Mean_Array_Value_f (  float * Input, int16_t Count );

extern float RMS_Array_Value_f  (  float * Input, int16_t Count );

extern float Auto_Correlation_Function ( int16_t * Analyzed_array_first_element,
                                         int16_t   Array_size,
                                         int16_t   Start_Corr_Interval,
                                         int16_t   Corr_Interval_Count);

extern float Cross_Correlation_Function ( int16_t *  Analyzed_array_first_element,
                                          int16_t *  Ref_array_first_element,
                                          uint16_t   Array_size,
                                          int16_t    Start_Corr_Interval,
                                          int16_t    Corr_Interval_Count);
#endif /*__CUSTOM_MATH*/