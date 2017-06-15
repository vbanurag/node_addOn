#include <nan.h>
#include <iostream>
#include <algorithm>
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
   using v8::Array;


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

   // Array sort using template vector sort method

   void arraySort(const FunctionCallbackInfo<Value> &args){
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    int n = args[0]->NumberValue();
    //Local<Array> arr = Array::New(isolate, n);

    Local<Array> input_array = Local<Array>::Cast(args[0]);
    int temp;

    for(int i =0 ; i< input_array->Length(); i++){
        for(int j =0 ; j<input_array->Length()-i-1; j++){
            if(input_array->Get(j)->NumberValue()>input_array->Get(j+1)->NumberValue()){
                temp = input_array->Get(j)->NumberValue();
                input_array->Set(j,Number::New(isolate,input_array->Get(j+1)->NumberValue()));
                input_array->Set(j+1, Number::New(isolate,temp));
            }
        }
        //arr->Set(i, Number::New(isolate, input_array->Get(i)->NumberValue()));
    }
    args.GetReturnValue().Set(input_array);
   }

/*entry point,we can recieve upto two arguments here.First is export like  module.export
*/
void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "sayHelloWorld", sayHelloWorld);//NODE_SET_MET  HOD to export
  NODE_SET_METHOD(exports, "add", addTwoValue);
  NODE_SET_METHOD(exports,"sortNode",arraySort);
}

//to define entry point,first argument must match with target name in binding.gyp
NODE_MODULE(myAddon, Init)