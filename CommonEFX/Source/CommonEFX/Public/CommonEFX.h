// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Modules/ModuleManager.h"
#include "Templates/Atomic.h"

class FSocket;
class FTcpListener;

class FCommonEFXModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenus();

	/** Starts/stops the TCP listener that triggers an import when a message is received. */
	void StartImportListener();
	void StopImportListener();

	/** Handles an accepted connection on the listener thread and queues an import. */
	bool HandleImportConnection(FSocket* ConnectionSocket, const FIPv4Endpoint& RemoteEndpoint);

	/** Runs on the game thread and imports the fixed snapshot file when a request is pending. */
	bool TickImportRequests(float DeltaTime);
	void ImportFixedSnapshot();

	TSharedPtr<FTcpListener> ImportListener;
	FSocket* ImportListenerSocket = nullptr;
	FTSTicker::FDelegateHandle ImportTickerHandle;
	TAtomic<bool> bImportRequested{false};
};
