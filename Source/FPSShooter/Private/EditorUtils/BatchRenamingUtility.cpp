// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorUtils/BatchRenamingUtility.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"



#pragma region RenameSelectedAssets

void UBatchRenamingUtility::RenameSelectedAssets(FString SearchPattern, FString ReplacePattern, ESearchCase::Type SearchCase)
{
	if (SearchPattern.IsEmpty() || SearchPattern.Equals(ReplacePattern, SearchCase))
	{
		return;
	}

	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			FString AssetName = SelectedObject->GetName();
			if (AssetName.Contains(SearchPattern, SearchCase))
			{
				FString NewName = AssetName.Replace(*SearchPattern, *ReplacePattern, SearchCase);
				UEditorUtilityLibrary::RenameAsset(SelectedObject, NewName);
				++Counter;
			}
		}
	}
	GiveFeedback(TEXT("Renamed"), Counter);
}



void UBatchRenamingUtility::PrintToScreen(FString Message, FColor Color)
{
	if (ensure(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, Color, Message);
	}
}
#pragma endregion

#pragma region AddPrefixes
void UBatchRenamingUtility::AddPrefixes()
{
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();
	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			const FString* Prefix = PrefixMap.Find(SelectedObject->GetClass());
			if (ensure(Prefix) && !Prefix->Equals(""))
			{
				FString OldName = SelectedObject->GetName();
				if (!OldName.StartsWith(*Prefix))
				{
					FString NewName = *Prefix + OldName;
					UEditorUtilityLibrary::RenameAsset(SelectedObject, NewName);
					++Counter;
				}
			}
			else
			{
				PrintToScreen("Couldn't find prefix for class " + SelectedObject->GetClass()->GetName(), FColor::Red);

			}
		}
	}
	GiveFeedback("Added prefix to", Counter);
}

#pragma endregion

#pragma region CleanUpFolder
void UBatchRenamingUtility::CleanUpFolders(FString ParentFolder)
{
	
	if (!ParentFolder.StartsWith(TEXT("/Game")))
	{
		ParentFolder = FPaths::Combine(TEXT("/Game"), ParentFolder);
	}

	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	uint32 Counter = 0;

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			
			FString NewPath = FPaths::Combine(ParentFolder, SelectedObject->GetClass()->GetName(), SelectedObject->GetName());
			if (UEditorAssetLibrary::RenameLoadedAsset(SelectedObject, NewPath))
			{
				++Counter;
			}
			else
			{
				PrintToScreen("Couldn't move" + SelectedObject->GetPathName(), FColor::Red);
			}
			
		}
	}
	
	GiveFeedback("Moved", Counter);
	
}
#pragma endregion

#pragma region	Helper
void UBatchRenamingUtility::GiveFeedback(FString Method, uint32 Counter)
{
	FString Message = FString("No matching Files Found");
	FColor Color = Counter > 0 ? FColor::Green : FColor::Red;
	if (Counter > 0)
	{
		Message = Method.AppendChar(' ');
		Message.AppendInt(Counter);
		Message.Append(Counter == 1 ? TEXT(" file") : TEXT(" files"));
	}
	PrintToScreen(Message, Color);
}
#pragma endregion

