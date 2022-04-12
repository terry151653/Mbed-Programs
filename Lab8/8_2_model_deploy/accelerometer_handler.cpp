#include "accelerometer_handler.h"
#include "mbed.h"
#include "stm32l475e_iot01_accelero.h"

// Store x, y, z data
int16_t pDataXYZ[3] = {0};

// A buffer holding the last 200 sets of 3-channel values
static float save_data[600] = {0.0};
// Most recent position in the save_data buffer
int begin_index = 0;
// True if there is not yet enough data to run inference
bool pending_initial_data = true;
// How often we should save a measurement during downsampling
int sample_every_n = 1;
// The number of measurements since we last saved one
int sample_skip_counter = 1;

TfLiteStatus SetupAccelerometer(tflite::ErrorReporter* error_reporter) {
  // Init accelerometer
  BSP_ACCELERO_Init();
  return kTfLiteOk;
}

bool ReadAccelerometer(tflite::ErrorReporter* error_reporter, float* input,
                       int length, bool reset_buffer) {
  // Clear the buffer if required, e.g. after a successful prediction
  if (reset_buffer) {
    memset(save_data, 0, 600 * sizeof(float));
    begin_index = 0;
    pending_initial_data = true;
  }

  // Obtain a sample
  while(sample_skip_counter <= sample_every_n) {
     BSP_ACCELERO_AccGetXYZ(pDataXYZ);
     sample_skip_counter += 1;
  }

  // Write samples to our buffer, converting to milli-Gs
  save_data[begin_index++] = (float)pDataXYZ[0];
  save_data[begin_index++] = (float)pDataXYZ[1];
  save_data[begin_index++] = (float)pDataXYZ[2];

  // Since we took a sample, reset the skip counter
  sample_skip_counter = 1;

  // If we reached the end of the circle buffer, reset
  if (begin_index >= 600) {
    begin_index = 0;
  }

  // Check if we are ready for prediction or still pending more initial data
  if (pending_initial_data && begin_index >= 200) {
    pending_initial_data = false;
  }

  // Return if we don't have enough data
  if (pending_initial_data) {
    return false;
  }

  // Copy the requested number of bytes to the provided input tensor
  for (int i = 0; i < length; ++i) {
    int ring_array_index = begin_index + i - length;
    if (ring_array_index < 0) {
      ring_array_index += 600;
    }
    input[i] = save_data[ring_array_index];
  }

  return true;
}
