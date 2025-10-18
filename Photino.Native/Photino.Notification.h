#pragma once

#ifndef PHOTINO_NOTIFICATION_H
#define PHOTINO_NOTIFICATION_H

#include "Photino.h"

#ifndef _WIN32
#include "Dependencies/wintoastlib.h"
#endif

enum class PhotinoNotificationType {
	ImageAndText01,
	ImageAndText02,
	ImageAndText03,
	ImageAndText04,
	Text01,
	Text02,
	Text03,
	Text04,
};

enum class PhotinoNotificationDismissalReason {
	UserCanceled,
	ApplicationHidden,
	TimedOut,
};

typedef void (*ActionCallback)(AutoString action);
typedef void (*ActivatedCallback)();
typedef void (*DismissedCallback)(PhotinoNotificationDismissalReason reason);

class PhotinoNotification
{
private:
	PhotinoNotificationType _type;

	ActionCallback _actionCallback;
	ActivatedCallback _activatedCallback;
	DismissedCallback _dismissedCallback;

	std::vector<AutoString> _textLines;
	std::vector<AutoString> _actionNames;
	AutoString _imagePath;

public:
#ifdef _WIN32
	PhotinoNotification(Photino* window);
#else
	PhotinoNotification();
#endif
	~PhotinoNotification();

	std::vector<AutoString> GetActions() const;

	void AddText(AutoString text);
	void AddAction(AutoString action);
	void SetImagePath(AutoString imagePath);
	void SetType(PhotinoNotificationType type);
	void Show();

	void SetActionCallback(ActionCallback callback) { _actionCallback = callback; }
	void SetActivatedCallback(ActivatedCallback callback) { _activatedCallback = callback; }
	void SetDismissedCallback(DismissedCallback callback) { _dismissedCallback = callback; }

	void InvokeAction(AutoString action) const
	{
		if (_actionCallback)
			return _actionCallback(action);
	}

	void InvokeActivated() const
	{
		if (_activatedCallback)
			return _activatedCallback();
	}

	void InvokeDismissed(PhotinoNotificationDismissalReason reason) const
	{
		if (_dismissedCallback)
			return _dismissedCallback(reason);
	}

protected:
#ifdef _WIN32
	Photino* _window;
	WinToastHandler* _handler;
#endif
};

#endif