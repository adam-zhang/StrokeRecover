#pragma once
//#include <boost/shared_ptr.hpp>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>
#include "ThreadSafeQueue.h"
#include "StrokesWindow.h"
//#include "Queue.h"

class server;
class Gdiplus::Bitmap;
class PaintingData;
class Stroke;
class D2DPaintingData;
// CStrokeDialog 对话框

class CStrokeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStrokeDialog)

public:
	CStrokeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStrokeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STROKE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT onSocketMessages(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CStatic strokeCanvas_;
	CStatic beginningTime_;
	CStatic staticTotalTime_;
	CStatic staticStrokeX_;
	CStatic staticStrokeY_;
	CStatic staticPressure_;
	CListCtrl listStrokes_;
	//std::shared_ptr<DrawingData> strokes_;
	//std::shared_ptr<DrawingSingleValue> strokesX_;
	//std::shared_ptr<DrawingData> strokesY_;
	//std::shared_ptr<DrawingData> strokesPressure_;
	std::shared_ptr<PaintingData> strokes_;
	std::shared_ptr<PaintingData> strokesX_;
	//std::shared_ptr<D2DPaintingData> strokes_;
	ThreadSafeQueue<Stroke*> listData_;
	//std::condition_variable listEvent_;
	//std::mutex listMutex_;
	void changeButtonStates();
private:
	std::queue<Stroke*> savingStrokes_;
	CWinThread* drawingThread_;
	//std::atomic<bool> stop_;
	//std::shared_ptr<server> server_;
private:
	void initialize();
	void initializeData();
	void initializeList();
	//void initializeSocketServer();
	//void initializeDrawingData();
	//void startServer();
public:
	//void doStartSocket();
	void onCommandStart();
	void onCommandDrawing(Stroke*);
private:
	void clearData();
	void draw(Stroke*);
	void stopDrawing();
	//void fillStroke(Stroke*);
	void doFillListData();
public:
	void doAcceptStroke();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
private:
	CButton buttonSave_;
public:
	afx_msg void OnClose();
	afx_msg void OnIdcancel();
};
