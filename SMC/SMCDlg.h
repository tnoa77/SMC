
// SMCDlg.h : 头文件
//

#pragma once
#include "afxtempl.h"
#include "afxwin.h"


// CSMCDlg 对话框
class CSMCDlg : public CDialogEx
{
// 构造
public:
	CSMCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SMC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CList<PromaItem, PromaItem&> m_promaList;
	afx_msg void OnBnClickedAddMotor();
	afx_msg void OnBnClickedAddTherm();
	afx_msg void OnBnClickedAddDelay();
	int m_motorDirection;
	afx_msg void OnBnClickedMotorUp();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedStop();
	CListBox m_listBox;
	void syncPromaList(int iCurSel);
	CString formatPromaItem(PromaItem item);
	void insertPromaItem(PromaItem item);
	void replacePromaItem(PromaItem item);
	CEdit m_tmp;
	CEdit m_rate;
	CEdit m_delay;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedEditMotor();
	afx_msg void OnBnClickedEditTherm();
	afx_msg void OnBnClickedEditDelay();
	void setEditEnable(BOOL enable);
};
