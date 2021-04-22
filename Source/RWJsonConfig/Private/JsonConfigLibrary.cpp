// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonConfigLibrary.h"

//TSharedPtr<FJsonObject> UJsonConfigLibrary::ConfigObject;
//FString UJsonConfigLibrary::ConfigPath;
//
//bool UJsonConfigLibrary::LoadConfigJson(FString InPath)
//{
//	bool Valid = false;
//
//	if (FPaths::FileExists(InPath))
//	{
//		ConfigPath = InPath;
//		FArchive* const FileAr = IFileManager::Get().CreateFileReader(*InPath);
//		if(FileAr)
//		{ 
//			ConfigObject = MakeShareable(new FJsonObject);
//			TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(FileAr);
//			if (FJsonSerializer::Deserialize(Reader, ConfigObject))
//			{
//				Valid = true;
//			}
//			else
//			{
//				UE_LOG(LogTemp, Warning, TEXT("FileAr cant Deserialize"));
//			}
//			FileAr->Close();
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("FileAr is invalid"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("InPath: %s is not exists"), *InPath);
//	}
//	return Valid;
//}
//
//bool UJsonConfigLibrary::SaveConfigJson(FString InPath)
//{
//	bool Valid = false;
//
//	if (ConfigObject)
//	{
//		FArchive* const FileAr = IFileManager::Get().CreateFileWriter(*InPath, FILEWRITE_EvenIfReadOnly);
//		if (FileAr)
//		{
//			TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(FileAr);
//			FJsonSerializer::Serialize(ConfigObject.ToSharedRef(), Writer);
//			FileAr->Close();
//			Valid = true;
//		}
//	}
//
//	return Valid;
//}
//
//bool UJsonConfigLibrary::SaveEmptyConfigJson(FString InPath)
//{
//	bool Valid = false;
//
//	ConfigObject = MakeShareable(new FJsonObject);
//
//	FArchive* const FileAr = IFileManager::Get().CreateFileWriter(*InPath, FILEWRITE_EvenIfReadOnly);
//	if (FileAr)
//	{
//		TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(FileAr);
//		FJsonSerializer::Serialize(ConfigObject.ToSharedRef(), Writer);
//		FileAr->Close();
//		Valid = true;
//	}
//	return Valid;
//}
//
//bool UJsonConfigLibrary::SetPawnSpeed(float InSpeed)
//{
//	bool Valid = false;
//
//	if (ConfigObject)
//	{
//		ConfigObject->SetNumberField(TEXT("PawnSpeed"), InSpeed);
//		Valid = true;
//	}
//
//	return Valid;
//}
//
//float UJsonConfigLibrary::GetPawnSpeed(bool& Valid)
//{
//	if (!ConfigObject)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetPawnSpeed faild, ConfigObject invalid"));
//		Valid = false;
//		return 0;
//	}
//
//	Valid = true;
//	return ConfigObject->GetNumberField(TEXT("PawnSpeed"));
//}
//
//bool UJsonConfigLibrary::SetLineColor(FString InKey, FColor InColor)
//{
//	bool Valid = false;
//
//	if (ConfigObject)
//	{
//		TSharedPtr<FJsonObject> ColorObject = MakeShareable(new FJsonObject);
//		ColorObject->SetNumberField(TEXT("R"), InColor.R);
//		ColorObject->SetNumberField(TEXT("G"), InColor.G);
//		ColorObject->SetNumberField(TEXT("B"), InColor.B);
//		ColorObject->SetNumberField(TEXT("A"), InColor.A);
//
//		if (!ConfigObject->HasField(TEXT("LineColor")))
//		{
//			TSharedPtr<FJsonObject> LineColorObject = MakeShareable(new FJsonObject);
//			ConfigObject->SetObjectField(TEXT("LineColor"), LineColorObject);
//		}
//		ConfigObject->GetObjectField(TEXT("LineColor"))->SetObjectField(InKey, ColorObject);
//		
//		Valid = true;
//	}
//
//	return Valid;
//}
//
//FColor UJsonConfigLibrary::GetLineColor(FString InKey, bool& Valid)
//{
//	if (!ConfigObject)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetPawnSpeed faild, ConfigObject invalid"));
//		Valid = false;
//		return FColor();
//	}
//
//	if (!ConfigObject->HasField(TEXT("LineColor")))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetPawnSpeed faild, ConfigObject have not LineColor object"));
//		Valid = false;
//		return FColor();
//	}
//
//	TSharedPtr<FJsonObject> ColorObject = ConfigObject->GetObjectField(TEXT("LineColor"))->GetObjectField(InKey);
//	//FColor Color = FColor(int32(ColorObject->GetNumberField(TEXT("R"))), int32(ColorObject->GetNumberField(TEXT("G"))), int32(ColorObject->GetNumberField(TEXT("B"))), int32(ColorObject->GetNumberField(TEXT("A"))));
//	FColor Color = FColor(ColorObject->GetNumberField(TEXT("R")), ColorObject->GetNumberField(TEXT("G")), ColorObject->GetNumberField(TEXT("B")), ColorObject->GetNumberField(TEXT("A")));
//	Valid = true;
//	return Color;
//}