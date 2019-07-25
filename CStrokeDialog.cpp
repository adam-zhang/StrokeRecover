// CStrokeDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "RestoreDemo.h"
#include "CStrokeDialog.h"
#include "afxdialogex.h"
#include "SocketServer.h"
#include "Messages.h"
#include "GlobalVariable.h"
#include "DrawingData.h"
#include "Painter.h"
#include "GlobalData.h"
#include "Debugger.h"
#include "PaintingData.h"
#include "Performence.h"
#include <fstream>
#include <gdiplus.h>
#include <string>
#include <chrono>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CStrokeDialog 对话框

using namespace std;
//using namespace Gdiplus;


void insertData(CListCtrl& control, Stroke* data)
{

		auto count = control.GetItemCount();
		//OutputDebugString((to_wstring(count) + TEXT("\n")).c_str());
		auto index = control.InsertItem(count, to_wstring(data->id).c_str());
		control.SetItemText(index, 1, to_wstring(data->x).c_str());
		control.SetItemText(index, 2, to_wstring(data->y).c_str());
		control.SetItemText(index, 3, to_wstring(data->pressure).c_str());
		if (index > 0)
			control.EnsureVisible(index, FALSE);
}

IMPLEMENT_DYNAMIC(CStrokeDialog, CDialogEx)

CStrokeDialog::CStrokeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STROKE, pParent)
	, drawingThread_(0)
//	, stop_(false)
{

}

CStrokeDialog::~CStrokeDialog()
{
}

void CStrokeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STROKE, strokeCanvas_);
	DDX_Control(pDX, IDC_LIST_STROKES, listStrokes_);
	DDX_Control(pDX, IDC_STATIC_BEGINNING, beginningTime_);
	DDX_Control(pDX, IDC_STATIC_TOTAL_TIME, staticTotalTime_);
	DDX_Control(pDX, IDC_STATIC_STORK_X, staticStrokeX_);
	DDX_Control(pDX, IDC_STATIC_STORK_Y, staticStrokeY_);
	DDX_Control(pDX, IDC_STATIC_STORK_PRESSURE, staticPressure_);
	DDX_Control(pDX, IDC_BUTTON_SAVE, buttonSave_);
}


BEGIN_MESSAGE_MAP(CStrokeDialog, CDialogEx)
	ON_MESSAGE(WM_SOCKET_MSG, onSocketMessages)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CStrokeDialog::OnBnClickedButtonSave)
	ON_WM_CLOSE()
	ON_COMMAND(IDCANCEL, &CStrokeDialog::OnIdcancel)
END_MESSAGE_MAP()


// CStrokeDialog 消息处理程序

void CStrokeDialog::initialize()
{
	//initializeSocketServer();
	initializeList();
	initializeData();
	//startServer();
}

//void CStrokeDialog::initializeSocketServer()
//{
//}

void CStrokeDialog::initializeData()
{
	shared_ptr<Painter> p = make_shared<StrokesPainter>();
	strokes_ = make_shared<PaintingData>(&strokeCanvas_, p);
	p = make_shared<StrokesXPainter>();
	strokesX_ = make_shared<PaintingData>(&staticStrokeX_, p);
	//strokesX_->setClearFunc(clearStroke);
	//func = paintStrokeX;
	// strokesX_->setDrawingFunc(func);
}

//void CStrokeDialog::initializeDrawingData()
//{
//	//shared_ptr<Painter> p = make_shared<StrokesPainter>();
//	//strokes_ = make_shared<DrawingData>(&strokeCanvas_, p);
//	//shared_ptr<Painter> painter = make_shared<StrokesXPainter>();
//	//strokesX_ = make_shared<DrawingSingleValue>(&staticStrokeX_, painter);
//	//p = make_shared<StrokesYPainter>();
//	//strokesY_ = make_shared<DrawingData>(&staticStrokeY_, p);
//	//p = make_shared<StrokesPressurePainter>();
//	//strokesPressure_ = make_shared<DrawingData>(&staticPressure_, p);
//}

void CStrokeDialog::initializeList()
{
	listStrokes_.InsertColumn(0, TEXT("序号"), 0, 50);
	listStrokes_.InsertColumn(1, TEXT("X"), 0, 80);
	listStrokes_.InsertColumn(2, TEXT("Y"), 0, 80);
	listStrokes_.InsertColumn(3, TEXT("Pressure"), 0, 80);
}

void CStrokeDialog::doFillListData()
{
	auto p = listData_.pop();
	insertData(listStrokes_, p);
}


BOOL CStrokeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	initialize();
	GlobalVariable::instance().setMessageWindow(this);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//void startSocket(CStrokeDialog* dialog)
//{
//	dialog->doStartSocket();
//}

//void CStrokeDialog::startServer()
//{
//}
//
//void CStrokeDialog::doStartSocket()
//{
//	//boost::asio::io_service service;
//	//tcp::endpoint endpoint(tcp::v4(), 9988);
//	//server_ = make_shared<server>(service, endpoint);
//	//server_->run();
//}

void notice(CStrokeDialog* dialog)
{
	MessageBox(dialog->GetSafeHwnd(), TEXT("请点击平板电脑按钮开始"), TEXT("消息"), MB_OK);
}

void CStrokeDialog::draw(Stroke* stroke)
{
	listData_.push(stroke);
	strokes_->draw(stroke);
	strokesX_->draw(stroke);
	//strokesY_->push(p);
	//strokesPressure_->push(p);
	savingStrokes_.push(stroke);
	changeButtonStates();
}

void CStrokeDialog::changeButtonStates()
{
	buttonSave_.EnableWindow(!savingStrokes_.empty());
}

//void CStrokeDialog::fillStroke(Stroke* p)
//{
//	listData_.push(p);
//}


//void CStrokeDialog::doFillStroke()
//{
//	while(true)
//	{
//		Stroke* p = listData_.pop();
//		Performence sec(TEXT("second doFillStroke"));
//		insertData(&listStrokes_, p);
//	}
//}

template<typename T>
void clearQueue(std::queue<T>& q)
{
	while (!q.empty())
		q.pop();
}

void CStrokeDialog::clearData()
{
	listStrokes_.DeleteAllItems();
	strokes_->clear();
	strokesX_->clear();
	//initializeDrawingData();
	//savingStrokes_.clear();
	clearQueue(savingStrokes_);
	changeButtonStates();
}

void CStrokeDialog::stopDrawing()
{

}

UINT AFX_CDECL acceptStroke(void* p)
{
	auto window = static_cast<CStrokeDialog*>(p);
	window->doAcceptStroke();
	return 0;
}

void CStrokeDialog::onCommandStart()
{
	::SendMessage(this->GetParent()->m_hWnd, WM_SHOW_STROKE_WINDOW, 0, 0);
	if (!drawingThread_)
	{
		drawingThread_ = AfxBeginThread(acceptStroke, this);
		drawingThread_->SetThreadPriority(THREAD_PRIORITY_TIME_CRITICAL);
	}
}

void CStrokeDialog::doAcceptStroke()
{
	//while (!stop_)
	while(true)
	{
		auto stroke = listData_.pop();
		insertData(listStrokes_, stroke);
	}
	//stop_;
}

void CStrokeDialog::onCommandDrawing(Stroke* stroke)
{
	//Performence p(TEXT("onCommandDrawing"));
	draw(stroke);
}

LRESULT CStrokeDialog::onSocketMessages(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case COMMAND_DRAWING:
		onCommandDrawing(reinterpret_cast<Stroke*>(lParam));
		break;
	case COMMAND_START:
		onCommandStart();
		break;
	case COMMAND_CLEAR:
		clearData();
		break;
	case COMMAND_STOP:
		stopDrawing();
		break;
	}
	return 0;
}

static std::shared_ptr<Gdiplus::Bitmap> createBitmap(CWnd& window)
{
	CRect rect;
	window.GetClientRect(&rect);
	return make_shared<Gdiplus::Bitmap>(rect.Width(), rect.Height());
}


static void saveFile(const wstring& fileName, std::queue<Stroke*> strokes)
{
	wofstream file(fileName);
	if (file.bad())
		return;
	while (!strokes.empty())
	{
		auto p = strokes.front();
		strokes.pop();
		file << p->id << ","
			<< p->x << ","
			<< p->y << ","
			<< p->pressure << ","
			<< p->status << ","
			<< p->timestamp << ","
			<< p->timestamp1 << endl;
	}
}

void CStrokeDialog::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dialog(FALSE, TEXT("保存笔迹"));
	auto ret = dialog.DoModal();
	if (ret == IDCANCEL)
		return;
	auto fileName = dialog.GetPathName();
	saveFile(fileName.GetBuffer(), savingStrokes_);
	changeButtonStates();
}


void CStrokeDialog::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	clearData();
	CDialogEx::OnClose();
}


void CStrokeDialog::OnIdcancel()
{
	// TODO: 在此添加命令处理程序代码
	//stop_ = true;
	if (!drawingThread_)
	{
		EndDialog(0);
		return ;
	}
	auto ret = TerminateThread(drawingThread_->m_hThread, 0);
	if (!ret)
	{
		auto code = GetLastError();
		Debugger::write("code", code);
	}

	EndDialog(0);
}
