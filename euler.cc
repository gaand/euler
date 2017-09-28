// hello.cc
#include <node.h>

namespace demo {

  #include <math.h>

  double
  reverseNumberInBase(double number, double base) {
    double reversed;
    for (reversed = 0; number > 0; number = (unsigned)(number / base) >> 0) {
      reversed = reversed * base + fmod(number, base);
    }

    return reversed;
  }

  #include <stdbool.h>

  bool
  testWithNumber(double number, double base) {
    return number == reverseNumberInBase(number, base);
  }

  double
  doubleBasePalindromeSum(unsigned base1,
      unsigned base2,
      unsigned upperLimit) {

    double sum = 0;
    for (unsigned i = 0; i < upperLimit; i++) {
      if (testWithNumber(i, base1) && testWithNumber(i, base2)) {
        sum += i;
      }
    }
    return sum;
  }

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::String;
using v8::Value;

void DoubleBasePalindromeSum(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() != 3) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  for (unsigned i = 0; i < 3; i++) {
    if (!args[i]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
      return;
    }
  }
  // Perform the operation
  double base1 = args[0]->NumberValue();
  double base2 = args[1]->NumberValue();
  double limit = args[2]->NumberValue();
  double value = doubleBasePalindromeSum(base1, base2, limit);
  Local<Number> num = Number::New(isolate, value);

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(num);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "doubleBasePalindromeSum", DoubleBasePalindromeSum);
}

NODE_MODULE(euler, init)

}  // namespace demo
