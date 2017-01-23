#pragma once

#include <vector>

#include <QDebug>
#include <QTimer>

#include "UiaUtil.h"
#include "HRutil.h"

struct TaskViewItem
{
	int index;
	QString name;
	RECT rect;
};


class TaskViewUiaClient : public QObject, public ComObject<IUIAutomationStructureChangedEventHandler, IUIAutomationEventHandler>
{
	Q_OBJECT

public:
	TaskViewUiaClient(QObject *parent = Q_NULLPTR);

	bool IsTaskViewShowing();
	void Show();
	void SwitchTo(int index);
	void Dismiss();

signals:
	void TaskViewShown();
	void TaskViewChanged(const std::vector<TaskViewItem>& items);
	void TaskViewDisappeared();

private:
	QTimer* _throttleTimer;
	IUIAutomation* _client;
	UiaElemArrPtr _taskViewWindows;
	ComPtr<IUIAutomationElement> _rootElem;
	ComPtr<IUIAutomationCacheRequest> _nameCacheReq;

	Q_SLOT void sycTaskViews();

	HRESULT STDMETHODCALLTYPE HandleAutomationEvent(IUIAutomationElement * pSender, EVENTID eventID) override;
	HRESULT STDMETHODCALLTYPE HandleStructureChangedEvent(IUIAutomationElement* pSender, StructureChangeType changeType, SAFEARRAY* pRuntimeID) override;

	void notifyDisappearing();
};
