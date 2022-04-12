#ifndef ACCELEROMETER_HANDLER_H_
#define ACCELEROMETER_HANDLER_H_

#define kChannelNumber 3

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

extern int begin_index;
extern TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter);
extern bool ReadAccelerometer(tflite::ErrorReporter* error_reporter,
                              float* input, int length, bool reset_buffer);

#endif  // ACCELEROMETER_HANDLER_H_
