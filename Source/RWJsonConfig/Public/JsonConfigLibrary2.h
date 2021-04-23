// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Json.h"
#include "Dom/JsonObject.h"
#include "JsonConfigLibrary2.generated.h"

/**
 * 
 */
UCLASS()
class RWJSONCONFIG_API UJsonConfigLibrary2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "JsonConfig")
		static bool SetPawnSpeed(float InSpeed);

	UFUNCTION(BlueprintPure, Category = "JsonConfig")
		static float GetPawnSpeed(bool& Valid);

	UFUNCTION(BlueprintPure, Category = "JsonConfig")
		static FString GetJsonConfigPath();

	UFUNCTION(BlueprintCallable, Category = "JsonConfig")
		static bool SetLineColor(FString Key, FColor InColor);

	//UFUNCTION(BlueprintPure, Category = "JsonConfig")
	//	static FColor GetLineColor(FString Key, bool& Valid);

	UFUNCTION(BlueprintPure, Category = "JsonConfig")
		static FLinearColor GetLineColor(FString Key, bool& Valid);

	UFUNCTION(BlueprintPure, Category = "JsonConfig")
		static FLinearColor ColorToLinearColor(FColor Incolor);

	UFUNCTION(BlueprintPure, Category = "JsonConfig")
		static FLinearColor HexToLinearColor(FString HexString);
private:
	static bool LoadConfig(TSharedPtr<FJsonObject>& Config);

	static bool SaveConfig(TSharedPtr<FJsonObject> Config);

	static bool SaveEmptyConfig(TSharedPtr<FJsonObject> Config);
};
