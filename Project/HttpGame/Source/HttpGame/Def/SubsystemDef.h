#pragma once

#ifndef SUBSYSTEM_GET_INS
#define SUBSYSTEM_GET_INS(SubsystemName)\
	GEngine && GEngine->GameViewport == nullptr ? nullptr : UGameInstance::GetSubsystem<U##SubsystemName>(GEngine->GameViewport->GetGameInstance())
#endif

//#ifndef SUBSYSTEM_GET_WORLD
//#define SUBSYSTEM_GET_WORLD(SubsystemName)\
//	//GetWorld() ? GetWorld()->GetSubsystem<U##SubsystemName>() : nullptr
//#endif

#ifndef SUBSYSTEM_GET_WORLD
#define SUBSYSTEM_GET_WORLD(SubsystemName)\
	GWorld->GetSubsystem<U##SubsystemName>()
#endif
