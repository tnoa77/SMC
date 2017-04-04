
// SMCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMC.h"
#include "SMCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMCDlg 对话框



CSMCDlg::CSMCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSMCDlg::IDD, pParent)
	, m_motorDirection(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MOTOR_UP, m_motorDirection);
	DDX_Control(pDX, IDC_PROMA_LIST, m_listBox);
	DDX_Control(pDX, IDC_TMP, m_tmp);
	DDX_Control(pDX, IDC_RATE, m_rate);
	DDX_Control(pDX, IDC_DELAY, m_delay);
}

BEGIN_MESSAGE_MAP(CSMCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_MOTOR, &CSMCDlg::OnBnClickedAddMotor)
	ON_BN_CLICKED(IDC_ADD_THERM, &CSMCDlg::OnBnClickedAddTherm)
	ON_BN_CLICKED(IDC_ADD_DELAY, &CSMCDlg::OnBnClickedAddDelay)
	ON_BN_CLICKED(IDC_MOTOR_UP, &CSMCDlg::OnBnClickedMotorUp)
	ON_BN_CLICKED(IDC_MOTOR_DOWN, &CSMCDlg::OnBnClickedMotorUp)
	ON_BN_CLICKED(IDC_RUN, &CSMCDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_STOP, &CSMCDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_OPEN, &CSMCDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CSMCDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_DELETE, &CSMCDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_CLEAR, &CSMCDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_EDIT_MOTOR, &CSMCDlg::OnBnClickedEditMotor)
	ON_BN_CLICKED(IDC_EDIT_THERM, &CSMCDlg::OnBnClickedEditTherm)
	ON_BN_CLICKED(IDC_EDIT_DELAY, &CSMCDlg::OnBnClickedEditDelay)
END_MESSAGE_MAP()


// CSMCDlg 消息处理程序

BOOL CSMCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSMCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSMCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSMCDlg::OnBnClickedAddMotor()
{
	PromaItem item;
	item.promaType = PT_MOTOR;
	if (m_motorDirection == PT_MOTOR_UP)
		item.wParam = PT_MOTOR_UP;
	else
		item.wParam = PT_MOTOR_DOWN;
	insertPromaItem(item);
}


void CSMCDlg::OnBnClickedAddTherm()
{
	CString tmp, rate;
	m_tmp.GetWindowText(tmp);
	m_rate.GetWindowText(rate);
	if (tmp == "") {
		AfxMessageBox(_T("温度错误！"));
		return;
	}
	if (rate == "") {
		AfxMessageBox(_T("速率错误！"));
		return;
	}
	PromaItem item;
	item.promaType = PT_THERM;
	item.wParam = _ttoi(tmp);
	item.lParam = _ttoi(rate);
	insertPromaItem(item);
}


void CSMCDlg::OnBnClickedAddDelay()
{
	CString delay;
	m_delay.GetWindowText(delay);
	if (delay == "") {
		AfxMessageBox(_T("保持时间错误！"));
		return;
	}
	PromaItem item;
	item.promaType = PT_DELAY;
	item.wParam = _ttoi(delay);
	insertPromaItem(item);
}


void CSMCDlg::OnBnClickedEditMotor()
{
	PromaItem item;
	item.promaType = PT_MOTOR;
	if (m_motorDirection == PT_MOTOR_UP)
		item.wParam = PT_MOTOR_UP;
	else
		item.wParam = PT_MOTOR_DOWN;
	replacePromaItem(item);
}


void CSMCDlg::OnBnClickedEditTherm()
{
	CString tmp, rate;
	m_tmp.GetWindowText(tmp);
	m_rate.GetWindowText(rate);
	if (tmp == "") {
		AfxMessageBox(_T("温度错误！"));
		return;
	}
	if (rate == "") {
		AfxMessageBox(_T("速率错误！"));
		return;
	}
	PromaItem item;
	item.promaType = PT_THERM;
	item.wParam = _ttoi(tmp);
	item.lParam = _ttoi(rate);
	replacePromaItem(item);
}


void CSMCDlg::OnBnClickedEditDelay()
{
	CString delay;
	m_delay.GetWindowText(delay);
	if (delay == "") {
		AfxMessageBox(_T("保持时间错误！"));
		return;
	}
	PromaItem item;
	item.promaType = PT_DELAY;
	item.wParam = _ttoi(delay);
	replacePromaItem(item);
}


void CSMCDlg::OnBnClickedMotorUp()
{
	UpdateData(TRUE);
}

void CSMCDlg::syncPromaList(int iCurSel)
{
	m_listBox.ResetContent();
	POSITION pos = m_promaList.GetHeadPosition();
	while (pos != NULL) {
		PromaItem item = m_promaList.GetNext(pos);
		m_listBox.AddString(formatPromaItem(item));
	}
	m_listBox.SetCurSel(iCurSel);
}

void CSMCDlg::insertPromaItem(PromaItem item)
{
	int iCurSel = m_listBox.GetCurSel();
	POSITION pos = m_promaList.GetHeadPosition();
	for (int i = 0; i < iCurSel; ++i) {
		m_promaList.GetNext(pos);
	}
	m_promaList.InsertAfter(pos, item);
	syncPromaList(iCurSel + 1);
}

void CSMCDlg::replacePromaItem(PromaItem item)
{
	int iCurSel = m_listBox.GetCurSel();
	if (iCurSel < 0)
		return;
	POSITION pos = m_promaList.GetHeadPosition();
	for (int i = 0; i < iCurSel; ++i) {
		m_promaList.GetNext(pos);
	}
	m_promaList.InsertAfter(pos, item);
	m_promaList.RemoveAt(pos);
	syncPromaList(iCurSel);
}

CString CSMCDlg::formatPromaItem(PromaItem item)
{
	CString rel;
	switch (item.promaType)
	{
	case PT_MOTOR:
		rel.Format(_T("制冷片：%s"), (item.wParam == PT_MOTOR_UP) ? _T("上升") : _T("下降"));
		break;
	case PT_THERM:
		rel.Format(_T("温度：%d°C, 速率：%d°C/min"), item.wParam, item.lParam);
		break;
	case PT_DELAY:
		rel.Format(_T("保持：%d秒"), item.wParam);
		break;
	default:
		rel = "未知命令";
		break;
	}
	return rel;
}


void CSMCDlg::OnBnClickedOpen()
{
	BOOL isOpen = TRUE;
	CString path, fileName;
	CString filter = _T("SMC文件 (*.smc;)|*.smc;||");
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = path + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		CFile file;
		file.Open(filePath, CFile::modeRead);
		PromaItem item;
		while (file.Read(&item, sizeof(PromaItem)) > 0) {
			m_promaList.AddTail(item);
		}
		file.Close();
		syncPromaList(-1);
	}
}


void CSMCDlg::OnBnClickedSave()
{
	BOOL isOpen = FALSE;
	CString path, fileName;
	CString filter = _T("SMC文件 (*.smc;)|*.smc;||");
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = path + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();
		if (filePath.Right(4) != _T(".smc")) {
			filePath = filePath + _T(".smc");
		}
		CFile file;
		file.Open(filePath, CFile::modeReadWrite);
		POSITION pos = m_promaList.GetHeadPosition();
		while (pos != NULL) {
			PromaItem item = m_promaList.GetNext(pos);
			file.Write(&item, sizeof(PromaItem));
		}
		file.Close();
	}
}


void CSMCDlg::OnBnClickedDelete()
{
	int iCurSel = m_listBox.GetCurSel();
	if (iCurSel < 0)
		return;
	POSITION pos = m_promaList.GetHeadPosition();
	for (int i = 0; i < iCurSel; ++i) {
		m_promaList.GetNext(pos);
	}
	m_promaList.RemoveAt(pos);
	syncPromaList(iCurSel - 1);
}


void CSMCDlg::OnBnClickedClear()
{
	m_promaList.RemoveAll();
	syncPromaList(-1);
}


void CSMCDlg::setEditEnable(BOOL enable)
{
	GetDlgItem(IDC_OPEN)->EnableWindow(enable);
	GetDlgItem(IDC_SAVE)->EnableWindow(enable);
	GetDlgItem(IDC_DELETE)->EnableWindow(enable);
	GetDlgItem(IDC_CLEAR)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_MOTOR)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_MOTOR)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_THERM)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_THERM)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(enable);
	GetDlgItem(IDC_ADD_DELAY)->EnableWindow(enable);
	GetDlgItem(IDC_RUN)->EnableWindow(enable);
	GetDlgItem(IDC_MOTOR_UP)->EnableWindow(enable);
	GetDlgItem(IDC_MOTOR_DOWN)->EnableWindow(enable);
	GetDlgItem(IDC_TMP)->EnableWindow(enable);
	GetDlgItem(IDC_RATE)->EnableWindow(enable);
	GetDlgItem(IDC_DELAY)->EnableWindow(enable);
	GetDlgItem(IDC_STOP)->EnableWindow(~enable);
}


void CSMCDlg::OnBnClickedRun()
{
	setEditEnable(FALSE);
}


void CSMCDlg::OnBnClickedStop()
{
	setEditEnable(TRUE);
}

