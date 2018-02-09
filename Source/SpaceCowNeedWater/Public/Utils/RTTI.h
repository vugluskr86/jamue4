#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

namespace RTTI
{

template<typename T>
inline static T* GetResouce(const TCHAR* name)
{
   ConstructorHelpers::FClassFinder<T> Resource(name);
   if (Resource.Class != NULL) {
      return Resource.Class->GetDefaultObject<T>();
   }
   return nullptr;
}


}