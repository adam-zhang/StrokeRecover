
// RestoreDemoDlg.h: 头文件
//

#include <memory>

#pragma once

class CStrokeDialog;

// CRestoreDemoDlg 对话框
class CRestoreDemoDlg : public CDialogEx
{
// 构造
public:
	CRestoreDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESTOREDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT onShowStrokeWindow(WPARAM, LPARAM);
private:
	std::shared_ptr<CStrokeDialog> dialog_;
	HANDLE threadSocket_;
private:
	void initializeSocketServer();
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
