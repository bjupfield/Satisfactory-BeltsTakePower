// Copyright Epic Games, Inc. All Rights Reserved.

#include "BeltsTakePower.h"
#include "Patching/NativeHookManager.h"
#include "Buildables/FGBuildableConveyorBelt.h"
#include "FGChatManager.h"
#include "FGPlayerController.h"

#define LOCTEXT_NAMESPACE "FBeltsTakePowerModule"

void FBeltsTakePowerModule::StartupModule()
{
	if (!WITH_EDITOR) {
		SUBSCRIBE_METHOD_AFTER(AFGBuildableConveyorBelt::GetVelocityForBase, [](auto& Scope, const AFGBuildableConveyorBelt* Obj, class AActor* basedActor, class UPrimitiveComponent* baseComponent) {});
		//SUBSCRIBE_METHOD_AFTER(AFGBuildableConveyorBelt::OnBuildEffectFinished, [](const AFGBuildableConveyorBelt* Obj){});
		SUBSCRIBE_METHOD(AFGBuildable::TurnOffAndDestroy, [](auto& Scope, const AFGBuildable* Obj) {
			AFGChatManager b;
			FChatMessageStruct c = FChatMessageStruct("Hi", nullptr, 5000);
			b.Multicast_BroadcastChatMessage(c);
			UE_LOG(LogTemp, Warning, TEXT("HELLO"));

			}); // => for the destroy
		SUBSCRIBE_METHOD(AFGPlayerController::StartRespawn, [](auto& Scope, const AFGPlayerController* Obj) {

			UE_LOG(LogTemp, Warning, TEXT("HELLO"));
			//okay this actually does log wonderful

			});
		SUBSCRIBE_METHOD(AFGPlayerController::Suicide, [](auto& Scope, const AFGPlayerController* Obj) {

			UE_LOG(LogTemp, Warning, TEXT("HELLO"));

			});
		SUBSCRIBE_METHOD(AFGBuildable::SetBuiltWithRecipe, [](auto& Scope, const AFGBuildable* Obj, TSubclassOf< class UFGRecipe > recipe) {}); // => for the build hopefully
		//SUBSCRIBE_METHOD(AFGBuildable::SetOriginalBuildableVariant, [](auto& Scope, const AFGBuildable* Obj, const TSubclassOf< AFGBuildable > originalVariant) {});
		//SUBSCRIBE_METHOD(AFGBuildableConveyorBase::BuildStaticItemInstances, [](auto& Scope, const AFGBuildable* Obj) 
		//	{
		//		int a = 0;
		//		a += 2;
		//	});
		/*SUBSCRIBE_METHODB_AFTER(AFGBuildableConveyorBelt::GetVelocityForBase, [](const AFGBuildableConveyorBelt* Obj, class AActor* basedActor, class UPrimitiveComponent* baseComponent){
				__int32 a = 0;
				a+= 1;
			});*/
	}
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBeltsTakePowerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

//void* hooker(auto& scope, const AFGBuildableConveyorBelt* self) {
//
//}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBeltsTakePowerModule, BeltsTakePower)