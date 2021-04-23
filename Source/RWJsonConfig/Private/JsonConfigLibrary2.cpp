// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonConfigLibrary2.h"

bool UJsonConfigLibrary2::LoadConfig(TSharedPtr<FJsonObject>& Config)
{
	bool Valid = false;

	FString InPath = GetJsonConfigPath();
	FString FileAr;

	if (FPaths::FileExists(InPath))
	{
		FFileHelper::LoadFileToString(FileAr, *(InPath));
		if (FileAr.Len() > 0)
		{
			Config = MakeShareable(new FJsonObject);
			TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(FileAr);
			Valid = FJsonSerializer::Deserialize(Reader, Config);
			if (!Valid)
			{
				UE_LOG(LogTemp, Warning, TEXT("FileAr cant Deserialize, %s"), *FileAr);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FileAr is invalid"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InPath: %s is not exists"), *InPath);
	}
	return Valid;
}

bool UJsonConfigLibrary2::SaveConfig(TSharedPtr<FJsonObject> Config)
{
	bool Valid = false;

	FString InPath = GetJsonConfigPath();
	if (Config)
	{
		FString FileAr;
		
		TSharedRef<TJsonWriter<>>Writer = TJsonWriterFactory<>::Create(&FileAr, 0);
		FJsonSerializer::Serialize(Config.ToSharedRef(), Writer);
		Valid = FFileHelper::SaveStringToFile(FileAr, *InPath);
	}

	return Valid;
}

bool UJsonConfigLibrary2::SaveEmptyConfig(TSharedPtr<FJsonObject> Config)
{
	bool Valid = false;

	FString InPath = GetJsonConfigPath();

	FString FileAr;
	TSharedRef<TJsonWriter<>>Writer = TJsonWriterFactory<>::Create(&FileAr, 0);
	FJsonSerializer::Serialize(Config.ToSharedRef(), Writer);
	Valid = FFileHelper::SaveStringToFile(FileAr, *InPath);

	return Valid;
}

FString UJsonConfigLibrary2::UJsonConfigLibrary2::GetJsonConfigPath()
{
	return FPaths::ProjectSavedDir() / TEXT("CustomConfig/Config.json");
}

bool UJsonConfigLibrary2::SetPawnSpeed(float InSpeed)
{
	bool Valid = false;

	TSharedPtr<FJsonObject> Config;
	if (FPaths::FileExists(GetJsonConfigPath()))
	{
		Valid = LoadConfig(Config);
	}
	if (!Valid)
	{
		Config = MakeShareable(new FJsonObject);
	}
	Config->SetNumberField(TEXT("PawnSpeed"), InSpeed);
	Valid = SaveConfig(Config);

	return Valid;
}

float UJsonConfigLibrary2::GetPawnSpeed(bool& Valid)
{
	Valid = false;
	float InSpeed = 0;

	if (FPaths::FileExists(GetJsonConfigPath()))
	{
		TSharedPtr<FJsonObject> Config;
		Valid = LoadConfig(Config);
		if (Valid)
		{
			Valid = Config->HasField(TEXT("PawnSpeed"));
			if (Valid)
			{
				InSpeed = Config->GetNumberField(TEXT("PawnSpeed"));
			}
		}
	}

	return InSpeed;
}

bool UJsonConfigLibrary2::SetLineColor(FString Key, FColor InColor)
{
	bool Valid = false;

	TSharedPtr<FJsonObject> Config;
	if (FPaths::FileExists(GetJsonConfigPath()))
	{
		Valid = LoadConfig(Config);
	}
	if (!Valid)
	{
		Config = MakeShareable(new FJsonObject);
	}

	TSharedPtr<FJsonObject> LineColor;
	if (Config->HasField(TEXT("LineColor")))
	{
		LineColor = Config->GetObjectField(TEXT("LineColor"));
	}
	else
	{
		LineColor = MakeShareable(new FJsonObject);
	}
	
	TSharedPtr<FJsonObject> Color = MakeShareable(new FJsonObject);
	float R = InColor.R;
	float G = InColor.G;
	float B = InColor.B;
	float A = InColor.A;
	Color->SetNumberField(TEXT("R"), R);
	Color->SetNumberField(TEXT("G"), G);
	Color->SetNumberField(TEXT("B"), B);
	Color->SetNumberField(TEXT("A"), A);
	LineColor->SetObjectField(Key, Color);

	Config->SetObjectField(TEXT("LineColor"), LineColor);
	Valid = SaveConfig(Config);

	return Valid;
}

FLinearColor UJsonConfigLibrary2::GetLineColor(FString Key, bool& Valid)
{
	Valid = false;
	FColor OutColor;
	uint8 R = 0;
	uint8 G = 0;
	uint8 B = 0;
	uint8 A = 0;

	if (FPaths::FileExists(GetJsonConfigPath()))
	{
		TSharedPtr<FJsonObject> Config;
		Valid = LoadConfig(Config);
		if (Valid)
		{
			Valid = Config->HasField(TEXT("LineColor"));
			TSharedPtr<FJsonObject> LineColor;
			if (Valid)
			{
				LineColor = Config->GetObjectField(TEXT("LineColor"));
				Valid = LineColor->HasField(Key);
				if(Valid)
				{
					TSharedPtr<FJsonObject> Color;
					Color = LineColor->GetObjectField(Key);
					R = Color->GetNumberField(TEXT("R"));
					G = Color->GetNumberField(TEXT("G"));
					B = Color->GetNumberField(TEXT("B"));
					A = Color->GetNumberField(TEXT("A"));
				}
			}
		}
	}
	OutColor = FColor(R, G, B, A);

	return FLinearColor(OutColor);
}

FLinearColor UJsonConfigLibrary2::ColorToLinearColor(FColor Incolor)
{
	return FLinearColor(Incolor);
}

FLinearColor UJsonConfigLibrary2::HexToLinearColor(FString HexString)
{
	FColor Color = FColor::FromHex(HexString);
	return FLinearColor(Color);
}