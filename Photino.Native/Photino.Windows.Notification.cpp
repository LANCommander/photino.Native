#include "Photino.Notification.h"
#include "Photino.Windows.ToastHandler.h"

#include <vector>
#include "Dependencies/wintoastlib.h"

WinToastLib::WinToastTemplate _toast;

PhotinoNotification::PhotinoNotification(Photino* window)
{
	_window = window;
	_handler = new WinToastHandler(this);
}

std::vector<AutoString> PhotinoNotification::GetActions() const
{
	return _actionNames;
}

void PhotinoNotification::SetType(PhotinoNotificationType type)
{
	_type = type;
	
	WinToastLib::WinToastTemplate::WinToastTemplateType winToastType;

	switch (_type)
	{
		case PhotinoNotificationType::ImageAndText01:
			winToastType = WinToastLib::WinToastTemplate::ImageAndText01;

		case PhotinoNotificationType::ImageAndText02:
			winToastType = WinToastLib::WinToastTemplate::ImageAndText02;

		case PhotinoNotificationType::ImageAndText03:
			winToastType = WinToastLib::WinToastTemplate::ImageAndText03;

		case PhotinoNotificationType::ImageAndText04:
			winToastType = WinToastLib::WinToastTemplate::ImageAndText04;

		case PhotinoNotificationType::Text01:
			winToastType = WinToastLib::WinToastTemplate::Text01;

		case PhotinoNotificationType::Text02:
			winToastType = WinToastLib::WinToastTemplate::Text02;

		case PhotinoNotificationType::Text03:
			winToastType = WinToastLib::WinToastTemplate::Text03;

		case PhotinoNotificationType::Text04:
			winToastType = WinToastLib::WinToastTemplate::Text04;

		default:
			winToastType = WinToastLib::WinToastTemplate::Text01;
	}

	_toast = WinToastLib::WinToastTemplate(winToastType);
}

void PhotinoNotification::AddText(AutoString text)
{
	_textLines.push_back(text);

	switch (_textLines.size())
	{
		case 1:
			_toast.setTextField(_window->ToUTF16String(text), WinToastLib::WinToastTemplate::FirstLine);
			break;

		case 2:
			_toast.setTextField(_window->ToUTF16String(text), WinToastLib::WinToastTemplate::SecondLine);
			break;

		case 3:
			_toast.setTextField(_window->ToUTF16String(text), WinToastLib::WinToastTemplate::ThirdLine);
			break;

		case 4:
			_toast.setAttributionText(_window->ToUTF16String(text));
			break;
	}
}

void PhotinoNotification::AddAction(AutoString action)
{
	_actionNames.push_back(action);
	_toast.addAction(_window->ToUTF16String(action));
}

void PhotinoNotification::SetImagePath(AutoString imagePath)
{
	_imagePath = imagePath;
	_toast.setImagePath(_window->ToUTF16String(imagePath));
}

void PhotinoNotification::Show()
{
	WinToastLib::WinToast::instance()->showToast(_toast, _handler);
}