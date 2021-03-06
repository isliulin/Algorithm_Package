// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CPAGES_3DCB51D600B9_INCLUDED
#define _INC_CPAGES_3DCB51D600B9_INCLUDED

//temp #include <afxcoll.h>
#include "cpage.h"

class CFakeRecNos;
class CFieldList;

typedef byte  CSortType;
#define stDescent       0x01//降序
#define stAscend        0x02//升序



//该链表的个数不大，如20个，每个叶面一般拥有一百条记录。
//##ModelId=3DCB51D600B9
//#include  "Depot.h"
//### 2002-11-7 Eric------>
#include "PageArraySort.h"

//### 2002-11-7 Eric<------------
class CDriverBase;
//class CRURecordMod;
class CPages 
{//m_PageArraySort  temp
	BYTE m_cDateConvertType;//日期转换类型
	bool m_bIsBof;//###_Mod 2002-10-14 zlq 注意不能为同一个值表示
	bool m_bIsEof;
	int m_nSaveVersion;
protected:
	int m_nLogicCount;
public:
	int m_nCurRecNo;//===tempG
	int GetLogicCount(){	return m_nLogicCount;	};
	CFields* m_pFields;

public:

	bool Bof();
	bool Eof();
	//CDepot m_Depot;
	int m_ntemp; //===temp

public:
	CFakeRecNos* m_pFakeRecNos;
private:
	bool RenameFile(CTString strTempFileName, CTString strTargetFileName,CTString &strOutFileName);
	int m_nMaxCountPerPage;    //每个页的最大记录条数.
	int m_nNormalCountPerPage; //正常时每页的记录条数.
	//绝对的最大页面个数
	int m_nMaxPageCount;

	//正常工作时页面个数
	int m_nWorkPageCount;

	//设置的页面中断的预报警，页面进行预装入，避免访问数据时等
	//待。暂定为100（到时候测定）
	int m_nAlertRange;

	//上一次访问的数据逻辑纪录号，用于页面预测
	int m_lngLastRecNo; 	  

	int  m_nOldCurRecNo;	 //insert,append时,保存纪录号,用于cancel时恢复.

	int m_nCriticalRecCount; //在页面中移动时,此页面还有几条纪录时,要预装.
	void AdjustLogicRecNo(int logicRecNo,int nOffset);
	void AdjustFakeRecNo(int logicRecNo,int fakeRecNo,  int nFakeOffset);
protected:

	 
public:
	void PrintPages();
	bool _Edit();
	bool _Append();
	bool _Insert();
	bool AdjustPageCount(bool bAtOnce = false);
	void SetSaveFileVersion(int nVersion);
	int GetSaveFileVersion();
	int GetFileVersion();

	//### 2002-11-7 Eric----------------------->
	CPageArraySort m_PageArraySort;
	//### 2002-11-7 Eric<-----------------------
	//得到页设置属性 包括 最大的页个数 每个页的正常时的大小 已经使用的页
	void GetPageSet(int &nMaxPageCount,int &nPageNormalSize,int &nUsePage);

	bool AdjustOriginCount(int nOffset);
	int GetNormalCountPerPage();
	bool SetNormalCountPerPage(int nCount);
	int GetMaxCountPerPage();

	CTString m_sFileName;
	
	int GetPageCount();

	CPages();

	~CPages();

	void BindFieldList(CFieldList * pFieldList);
	
	int GetInsertPos(int nColIndex,double bValue,CSortType nType,int nNullCount);

	int SearchPos(int nRecSmall,int nRecLarge,double fValue,int nColIndex,CSortType nType);

	bool Clear();

	bool LoadFile(LPCTSTR lpszFileName);


	bool NewFile();

	//pstrOutFile 返回false 时且保存为天律文件时有效, 为保存时出错时的另存为的文件名字,由内部生成
	bool SaveFile(LPCTSTR lpszFileName,CTString *pstrOutFile);

	//##ModelId=3DCB52A4006F
	bool SetMaxPageCount(int count);


	CPage* GetCurPage();

	//设置当前的记录号（得到指定记录号的数据）
	//如果不在内存页中，则调用GetNormalPage()得到一个可用的页�

	//并检查是否需要卸载。然后发出页请求，并等待返回（因为是多
	//线程，所以必须用到WaitForSingleObject API函数）
	//
	//注意：如果需要的数据在已经申请的队列中，且是读的，则必须
	//修改该队列对应的项，要求返回WaitForSingleObject。
	//##ModelId=3DCB59260273
	bool SetCurRecNo(int RecNo);

	//得到最近没有使用的数据集
	//##ModelId=3D056C3603E6
	//CPage* GetRecentNoUse();//#_修改 2002-11-12 $ 16:56:44 zlq

	
	//CPage* GetRecentNoUseNoModify(); //#_修改 2002-11-12 $ 16:56:46 zlq
	//##ModelId=3D056C8F01B3
	int GetUsePageCount();

	//得到记录号对应的数据所处于的状态。
	//有以下几种状态：
	//正常工作状态，等待数据装入，数据调入，等待数据写回，数据
	//写回状态，没有装入（不包括等待数据装入，数据调入，等待数
	//据写回，数据写回状态）
	//(参考页面状态）
	//typedef byte  CPageState
	//
	//#define pgNormal       0x01
	//#define pgWaitLoad     0x02
	//#define pgLoading      0x03
	//#define pgWaitUnLoad   0x04
	//#define pgUnLoading    0x05
	//#define pgInDisk       0x06
	//##ModelId=3D0869600206
	bool QueryRecNoState(int RecNo, CPage*& InPage,int& StartRecNo,int& Count);


	//面的AdjustFakeRecNo函数）
	//注意：所有页面，不管处于什么状态
	void UnLoad(CPage* pPage,bool IsNeedFeedback=false);

	//得到逻辑记录号与伪记录号的偏移
	int GetLogicToFake(int LogicRecNo);
    CPage* GetPhysicalEmptyPage();


	int Next();
	int Prior();

	int MoveBy(int iSkipLen ,CFromPos MoveFlags);

	int First();
	int Last();
	//返回当前记录号
	 int GetRecNo();
	 bool Delete();
	 bool Cancel();


	//返回记录集的个数，包括没有装入内存的记录
	 int GetRecordCount();


	//设置当前条记录的所有的字段的数据信息到一个指定的缓冲区里
	//
	//数据组织按指示信息部分（所有字段，每个字段一字节）+数据�

	//分（所有字段，可能某些字段也没有数据，前面能够表达时）
	//
	//返回数据长度
	//##ModelId=3D054ECF01DA
	 int SetRecord(LPBYTE lpData);

	//对当前的记录数据赋值操作（数据集在此之前应该通过处于编辑
	//或添加状态，调用append,edit等方法），
	//调用字段链表各字段的LoadDataFromBuffer
	//
	//返回是否装载成功，及有效缓冲区数据大小
	//##ModelId=3D0020C401A9
	 bool GetRecord(LPBYTE lpData, int& count);

	//对当前的记录数据赋值操作（数据集在此之前应该通过处于编辑
	//或添加状态，调用append,edit等方法），并且修改指针
	//调用字段链表各字段的LoadDataFromBuffer
	//##ModelId=3D0553C00247
	 bool GetRecord(LPBYTE& lpData);

	 //bool SetPagePosition(CPage* pPage ,int nPos);

	/*
	返回时该页已经有效（即已经卸载过）
	1。1调用本页面集的UnLoad函数（该函数内部还要调整其它页面的伪记录起址）
	1。2本线程进入等待状态
	*/
	 void WaitForUnLoad(CPage* pPage);

	/*返回时该页已经有效
	1。1调用该页的load函数
	1。2本线程进入等待状态
	*/
	 void WaitForLoad(CPage* pPage,int logicRecNo, int count );

	/*
	根据传入的记录号，得到所在的页（不在内存则内部装入并返回该页）
	注意：该函数不进行页面顺序的调整
	返回：记录所在的页

	1.先查询该记录号状态QueryRecNoState
	1。1 正常在内存中，则返回该页
	1。2 在队列中，调用WaitForInQueue(pPage : CPage*)返回该页
	1。3 如果不在内存页中，则调用GetPhysicalEmptyPage得到一个可用的空页,WaitForLoad得到该页
	*/

	CPage* GetRecNoPageInNormal(int RecNo);




	void InsertField(int nIndex,CField* pNewField);
	void DeleteField(int nIndex); 
	void ModifyField(int nIndex,CField* pNewField);
	void AddField(CField* pNewField);
	bool MoveRecord(int nSourceRec,int nDestinationRec); 
	void MoveField(int nFrom, int nTo);
};


#endif /* _INC_CPAGES_3DCB51D600B9_INCLUDED */

