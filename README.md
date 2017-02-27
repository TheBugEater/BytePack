# BytePack
Reflection and Serialization Library Created from Scratch by Dilhan Geeth

You can easily make any C++ Class Reflected by adding few macros to your code. 

Example:
```
class Test : public BPObject
{
  BP_REFLECT(Test)

  uint64 ID;
  float floatVal;
};

BP_BEGIN_CLASS(Test, BPObject)
.Property(&Test::ID, "id", "An Integer for Saving the ID", EPropertyFlags::ReadWrite)
.Property(&Test::floatVal, "floatVal", "A Float Value", EPropertyFlags::ReadWrite)
.Build()
BP_END_CLASS(Test)
```
