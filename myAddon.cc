#include <nan.h>
#include <iostream>
using namespace std;
using v8::FunctionCallbackInfo;
   using v8::Isolate;
   using v8::Object;
   using v8::String;
   using v8::Value;
   using v8::Handle;
   using v8::Number;
   using v8::Local;
   using v8::HandleScope;
   using v8::Handle;
   using v8::Exception;


   /**
    *simple function to be export from this c++ code
   **/
 void sayHelloWorld(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
       args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Hello World !!!!!!!!!!!"));
   }

 void addTwoValue(const FunctionCallbackInfo<Value> &args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() < 2){
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Invalid arguments size")));
    return;
  }

  if(!args[0]-> IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Invalid arguments ")));
        return;
  }

  double value = args[0]->NumberValue() + args[1]->NumberValue();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);

   }


/*entry point,we can recieve upto two arguments here.First is export like  module.export
*/
void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "sayHelloWorld", sayHelloWorld);//NODE_SET_MET  HOD to export
  NODE_SET_METHOD(exports, "add", addTwoValue);
}

//to define entry point,first argument must match with target name in binding.gyp
NODE_MODULE(myAddon, Init)