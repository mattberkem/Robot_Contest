
#ifndef PROCESSOR_INPUT_DEVICE_H
#define PROCESSOR_INPUT_DEVICE_H

class ProcessorInputDevice {

 public:
  virtual unsigned char getInputPortValue() const = 0;


};

#endif // PROCESSOR_INPUT_DEVICE_H
