#ifndef ACCES_H
#define ACCES_H


#include "stdafx.h"
#include "afxdao.h"


class ACCESS 
{

public:

	ACCESS();											// default constructor
	~ACCESS();											// destructor 
	ACCESS(CString dbname);								// constructor + open
	bool Open(CString dbname);
	void CreateTable(CString tablename);
	void CreateUserTable();
	void CreateTDevice2(CString tablename);
	void CreateBan();
	void CreateOverView();
	void CreateCharacterTable();
	void AddBan(const CString& IP,const CString &USERNAME);
	void UnBan(const CString &IP);
	void AddUser(const CString UserName,const CString PassWord);
	void DeleteUser(const CString UserName);
	bool ExistTable(CString tablename);
	bool ExistUser(CString Username);
	void GetArray(CString tablename,CString column,CStringArray &List);
	void GetCharArray(CString UserName,CStringArray &List);
	void SetStat(CString Charname,CString StatName,CString StatValue);
	void FillOverView(CString NAME,CString DESCRIPTION,int TYPE,CString IP, CString SCANNED, CString UP);
	void FillCharTable(const CString &CHARACTER,const CString &RACE,\
		const CString &CLASS,const CString &DEITY,const CString &ALIGNMENT,\
		const CString &FAMILIAR,const CString &LANGUAGES,const CString &GENDER,\
		const CString &PICTURE,const CString &DESCRIPTION,const CString &AGE,\
		const CString &STRENGTH,const CString &DEXTERITY,const CString &CONSTITUTION,\
		const CString &INTELLIGENCE,const CString &WISDOM,const CString &CHARISMA);
	void FillAbility(CString tablename,const CString &Charisma,const CString &Constitution,const CString &Dexterity,const CString &Intelligence,const CString &Strength,const CString &Wisdom);
	void FillTDevice2(CString tablename,const CStringArray &IP);
	void FillTFakeMac(CString IP,const CStringArray& MAC);
	void SetDbName(CString Setm_DbName);
	void SetTableName(CString Setm_TableName);
	void GetValue(CString tablename,CString columnname,CStringArray &PrintArray);
	CString GetValue(CString tablename,CString columnname,CString seekvalue);
	CString GetValue(CString tablename,CString columnname,CString targetcolumn,CString seekvalue);
	void GetValues(CString tablename,CString columnname,CString targetcolumn,CString seekvalue,CStringArray &values);
	CString GetDbName() { return m_DbName; }
	void GetBan_List(CStringArray &List);
	void GetUsers_List(CStringArray &List);
	void GetOverview(int type,CStringArray &NameArray, CStringArray &IPArray);
	void CleanTable(CString tablename);
	void CompleteTable(CString tablename);
	void CompleteDevice(CString tablename);
	void FinishTable(CString tablename);
	void UseSameChar(CString UserName,CString CharacterName);
	void MakeNewChar(CString UserName,CString CharacterName);
	void MakeNewChar2(CString UserName,CString CharacterName);
	CString ConvertIP(CString IP);
	void Close();
	//CString m_GetValue;

protected:

	void CreateDb();									// wordt enkel aangeroepen via Open
	void CreateTFakeMAC();
	CString FormatOleVariant(COleVariant var);
	void CleanTableBlock(CString tablename);
	void DeleteFakeMac(CString tablename);
	void RemoveDoubles(CString tablename);
	void SmartComplete(CString tablename);


private:

	CDaoDatabase DaoDb;
	CString m_DbName;
	CString m_TableName;
	//CString str;
	bool m_TExists;
	int teller;

};



ACCESS::ACCESS()			// default constructor
{
	teller=1;
}

ACCESS::~ACCESS()
{
}

ACCESS::ACCESS(CString dbname)
{
	teller=1;
	Open(dbname);

}

bool ACCESS::Open(CString dbname)	// modifier voor balance
{
	m_DbName=dbname;
	try
	{
		DaoDb.Open(m_DbName);
	}
	catch(CException* e)
	{
		e->Delete();
		AfxMessageBox("No DnD Database was found! Make sure the database is in place.");
		CreateDb();
		return false;
	}
	return true;
}

void ACCESS::CreateDb()
{
	try
	{
		DaoDb.Create(m_DbName,dbLangGeneral); //by default it will take the latest ver3.0
		CreateBan();
		CreateUserTable();
		CreateCharacterTable();
		CreateOverView();
		CreateCharacterTable();
	}
	catch ( CException* e)
	{
	//	e->ReportError();
		e->Delete();
	}
}

void ACCESS::CreateBan()
{
	if(!ExistTable("Ban_List"))
	{
		CDaoTableDef TableDef(&DaoDb) ; // Define Table object
		TableDef.Create("Ban_List") ;
		TableDef.CreateField("IP",dbText,50,dbUpdatableField|dbVariableField) ;
		TableDef.CreateField("USERNAME",dbText,50,dbUpdatableField|dbVariableField) ;
		TableDef.Append() ;
		TableDef.Close() ;
		DaoDb.Execute("ALTER TABLE ARP ADD PRIMARY KEY (IP)") ; //Add primary key
	}
}

void ACCESS::CreateOverView()
{
	if(!ExistTable("OVERVIEW"))
	{
		CDaoTableDef TableDef(&DaoDb) ; // Define Table object
		TableDef.Create("OVERVIEW") ;
		TableDef.CreateField("USERNAME",dbText,150,dbUpdatableField|dbVariableField) ;
		TableDef.CreateField("PASSWORD",dbText,50,dbUpdatableField|dbVariableField) ;
		TableDef.Append() ;
		TableDef.Close() ;
		DaoDb.Execute("ALTER TABLE OVERVIEW ADD PRIMARY KEY (USERNAME)") ; //Add primary key
	}
}

void ACCESS::CreateTable(CString tablename)
{
	m_TExists=false;
	CDaoTableDef TableDef(&DaoDb) ; // Define Table object
	CString c_temp="ALTER TABLE ";
	c_temp+=tablename;
	c_temp+=" ADD PRIMARY KEY (ID)";
	TableDef.Create(tablename);
	TableDef.CreateField("ID",dbLong, 4, dbAutoIncrField ) ;
	TableDef.CreateField("CHARACTER",dbText,50,dbUpdatableField|dbVariableField) ;
	TableDef.CreateField("RACE",dbText, 30, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("CLASS",dbText, 30, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("DEITY",dbText, 100, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("ALIGNMENT",dbText, 30, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("FAMILIAR",dbText, 50, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("LANGUAGES",dbText, 150, dbUpdatableField|dbVariableField ) ;
	TableDef.CreateField("GENDER",dbText,10,dbUpdatableField|dbVariableField) ;
	TableDef.CreateField("PICTURE",dbText,4,dbUpdatableField|dbVariableField);
	TableDef.CreateField("DESCRIPTION",dbText,250,dbUpdatableField|dbVariableField) ;
	TableDef.CreateField("AGE",dbText, 50, dbUpdatableField|dbVariableField ) ;
	try
	{
		TableDef.Append() ;
	}
	catch(CException* e)
	{
		e->Delete();
		m_TExists=true;
	}
	TableDef.Close() ;
	if(!m_TExists)
		DaoDb.Execute(c_temp);
}

void ACCESS::CreateCharacterTable()
{
	if(!ExistTable("CHARACTERTABLE"))
	{
		m_TExists=false;
		CDaoTableDef TableDef(&DaoDb) ; // Define Table object
		TableDef.Create("CHARACTERTABLE");
		TableDef.CreateField("CHARACTER_ID",dbText, 10, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("NAME",dbText,50,dbUpdatableField|dbVariableField) ;
		TableDef.CreateField("RACE",dbText, 30, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("CLASS",dbText, 30, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("DEITY",dbText, 100, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("ALIGNMENT",dbText, 30, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("FAMILIAR",dbText, 50, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("LANGUAGES",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("GENDER",dbText,20,dbUpdatableField|dbVariableField) ;
		TableDef.CreateField("PICTURE",dbText,20,dbUpdatableField|dbVariableField);
		TableDef.CreateField("DESCRIPTION",dbText,250,dbUpdatableField|dbVariableField) ;
		TableDef.CreateField("AGE",dbText, 50, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("ARMORCLASS",dbText, 50, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("ITEMLIST_ID",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("STRENGTH",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("DEXTERITY",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("CONSTITUTION",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("INTELLIGENCE",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("WISDOM",dbText, 150, dbUpdatableField|dbVariableField ) ;
		TableDef.CreateField("CHARISMA",dbText, 150, dbUpdatableField|dbVariableField ) ;
		try
		{
			TableDef.Append() ;
		}
		catch(CException* e)
		{
			e->Delete();
			m_TExists=true;
		}
		TableDef.Close() ;
		if(!m_TExists)
			DaoDb.Execute("ALTER TABLE CHARACTERTABLE ADD PRIMARY KEY (CHARACTER_ID)");
	}
}

void ACCESS::CreateUserTable()
{
	if(!ExistTable("UserTable"))
	{
		CDaoTableDef TableDef(&DaoDb) ; // Define Table object
		TableDef.Create("USERTABLE");
		TableDef.CreateField("ID",dbLong, 4, dbAutoIncrField );
		TableDef.CreateField("USERNAME",dbText,50,dbUpdatableField|dbVariableField);
		TableDef.CreateField("CHARACTER_ID",dbText,4,dbUpdatableField|dbVariableField);
		try
		{
			TableDef.Append() ;
		}
		catch(CException* e)
		{
			e->Delete();
			m_TExists=true;
		}
		TableDef.Close() ;
		if(!m_TExists)
			DaoDb.Execute("ALTER TABLE USERTABLE ADD PRIMARY KEY (ID)");
	}
}

void ACCESS::CreateTDevice2(CString tablename)
{
	m_TExists=false;
	CDaoTableDef TableDef(&DaoDb) ; // Define Table object
	CString c_temp="ALTER TABLE ";
	c_temp+=tablename;
	c_temp+=" ADD PRIMARY KEY (KEYVALUE)";
	TableDef.Create(tablename);
	TableDef.CreateField("KEYVALUE",dbLong, 4, dbAutoIncrField ) ;
	TableDef.CreateField("CONNECTED DEVICE",dbText,50,dbUpdatableField|dbVariableField);
	TableDef.CreateField("IP",dbText,50,dbUpdatableField|dbVariableField) ;
	TableDef.CreateField("LIFE",dbInteger,dbUpdatableField|dbVariableField) ;
	try
	{
		TableDef.Append() ;
	}
	catch(CException* e)
	{
		e->Delete();
		m_TExists=true;
	}
	TableDef.Close() ;
	if(!m_TExists)
		DaoDb.Execute(c_temp);
}

void ACCESS::CreateTFakeMAC()
{
	CDaoTableDef TableDef(&DaoDb) ; // Define Table object
	TableDef.Create("FAKEMACTABLE") ;
	TableDef.CreateField("IP",dbText,50,dbUpdatableField|dbVariableField) ;
	TableDef.CreateField("MAC",dbText,50,dbUpdatableField|dbVariableField) ;
	TableDef.Append() ;
	TableDef.Close() ;
}

void ACCESS::AddBan(const CString &IP,const CString &USERNAME)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM Ban_List",0);

	COleVariant tempvar (_T(IP),VT_BSTRT);
	COleVariant tempvar2 (_T(USERNAME),VT_BSTRT);
	CString c_tmpIP="IP= '";
	c_tmpIP+=IP;
	c_tmpIP+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_tmpIP))
	{
		COleVariant var= RecSet->GetFieldValue("USERNAME");
		if(FormatOleVariant(var)!=USERNAME) //indien vorige ip een ander username had -> vorige waarde deleten
		{				// str verkregen uit FormatOleVariant()
			RecSet->Delete();
			RecSet->AddNew();
			RecSet->SetFieldValue("IP",tempvar);
			RecSet->SetFieldValue("USERNAME",tempvar2);
			RecSet->Update();
		}
	}
	else
	{
		RecSet->AddNew();
		RecSet->SetFieldValue("IP",tempvar);
		RecSet->SetFieldValue("USERNAME",tempvar2);
		RecSet->Update();
	}
	
	RecSet->Close();
}

void ACCESS::DeleteUser(const CString UserName)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM OVERVIEW",0);
	RecSet->MoveFirst();
	CString c_tmpUserName="USERNAME= '";
	c_tmpUserName+=UserName;
	c_tmpUserName+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_tmpUserName))
	{
			RecSet->Delete();
	}
	RecSet->Close();
}

void ACCESS::AddUser(const CString UserName,const CString PassWord)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM OVERVIEW",0);

	COleVariant tempvar (_T(UserName),VT_BSTRT);
	COleVariant tempvar2 (_T(PassWord),VT_BSTRT);

	RecSet->AddNew();
	RecSet->SetFieldValue("USERNAME",tempvar);
	RecSet->SetFieldValue("PASSWORD",tempvar2);
	RecSet->Update();
	
	RecSet->Close();
}

void ACCESS::UnBan(const CString &IP)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM Ban_List",0);
	COleVariant tempvar (_T(IP),VT_BSTRT);
	CString c_tmpIP="IP= '";
	c_tmpIP+=IP;
	c_tmpIP+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_tmpIP))
	{
			RecSet->Delete();
		//	RecSet->Update();
	}
/*	else
	{
		RecSet->AddNew();
		RecSet->SetFieldValue("IP",tempvar);
		RecSet->SetFieldValue("USERNAME",tempvar2);
		RecSet->Update();
	}*/
	
	RecSet->Close();
}

void ACCESS::FillOverView(CString NAME,CString DESCRIPTION,int TYPE,CString IP, CString SCANNED, CString UP)
{
	char s_Type[20];
	itoa(TYPE,s_Type,10);
	COleVariant tempName (_T(NAME),VT_BSTRT);
	COleVariant tempDescr (_T(DESCRIPTION),VT_BSTRT);
	COleVariant tempType (_T(s_Type),VT_BSTRT);
	COleVariant tempIP (_T(IP),VT_BSTRT);
	COleVariant tempSCANNED (_T(SCANNED),VT_BSTRT);
	COleVariant tempUP (_T(UP),VT_BSTRT);
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM OVERVIEW",0);
	RecSet->AddNew();
	RecSet->SetFieldValue("NAME",tempName);
	RecSet->SetFieldValue("DESCRIPTION",tempDescr);
	RecSet->SetFieldValue("TYPE",tempType);
	RecSet->SetFieldValue("IP",tempIP);
	RecSet->SetFieldValue("SCANNED",tempSCANNED);
	RecSet->SetFieldValue("UPTIME",tempUP);
	try
	{
		RecSet->Update();
	}
	catch(CDaoException* e)
	{
		//e->ReportError();		// The changes you requested 
		e->Delete();
	}
	RecSet->Close();
}

void ACCESS::FillCharTable(const CString &CHARACTER,const CString &RACE,\
		const CString &CLASS,const CString &DEITY,const CString &ALIGNMENT,\
		const CString &FAMILIAR,const CString &LANGUAGES,const CString &GENDER,\
		const CString &PICTURE,const CString &DESCRIPTION,const CString &AGE,\
		const CString &STRENGTH,const CString &DEXTERITY,const CString &CONSTITUTION,\
		const CString &INTELLIGENCE,const CString &WISDOM,const CString &CHARISMA)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM CHARACTERTABLE",0);

	//COleVariant tempvar (_T(CHARACTER),VT_BSTRT);
	COleVariant tempvar (_T(RACE),VT_BSTRT);
	COleVariant tempvar2 (_T(CLASS),VT_BSTRT);
	COleVariant tempvar3 (_T(DEITY),VT_BSTRT);
	COleVariant tempvar4 (_T(ALIGNMENT),VT_BSTRT);
	COleVariant tempvar5 (_T(FAMILIAR),VT_BSTRT);
	COleVariant tempvar6 (_T(LANGUAGES),VT_BSTRT);
	COleVariant tempvar7 (_T(GENDER),VT_BSTRT);
	COleVariant tempvar8 (_T(PICTURE),VT_BSTRT);
	COleVariant tempvar9 (_T(DESCRIPTION),VT_BSTRT);
	COleVariant tempvar10 (_T(AGE),VT_BSTRT);
	COleVariant tempvar11 (_T(STRENGTH),VT_BSTRT);
	COleVariant tempvar12 (_T(DEXTERITY),VT_BSTRT);
	COleVariant tempvar13 (_T(CONSTITUTION),VT_BSTRT);
	COleVariant tempvar14 (_T(INTELLIGENCE),VT_BSTRT);
	COleVariant tempvar15 (_T(WISDOM),VT_BSTRT);
	COleVariant tempvar16 (_T(CHARISMA),VT_BSTRT);
	CString c_seekstring="NAME= '";
	c_seekstring+=CHARACTER;
	c_seekstring+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("RACE",tempvar);
		RecSet->SetFieldValue("CLASS",tempvar2);
		RecSet->SetFieldValue("DEITY",tempvar3);
		RecSet->SetFieldValue("ALIGNMENT",tempvar4);
		RecSet->SetFieldValue("FAMILIAR",tempvar5);
		RecSet->SetFieldValue("LANGUAGES",tempvar6);
		RecSet->SetFieldValue("GENDER",tempvar7);
		RecSet->SetFieldValue("PICTURE",tempvar8);
		RecSet->SetFieldValue("DESCRIPTION",tempvar9);
		RecSet->SetFieldValue("AGE",tempvar10);
		RecSet->SetFieldValue("STRENGTH",tempvar11);
		RecSet->SetFieldValue("DEXTERITY",tempvar12);
		RecSet->SetFieldValue("CONSTITUTION",tempvar13);
		RecSet->SetFieldValue("INTELLIGENCE",tempvar14);
		RecSet->SetFieldValue("WISDOM",tempvar15);
		RecSet->SetFieldValue("CHARISMA",tempvar16);
		RecSet->Update();
	}

	RecSet->Close();
}

void ACCESS::SetStat(CString Charname,CString StatName,CString StatValue)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);

	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM CHARACTERTABLE",0);
	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		RecSet->Close();
		return ;
	}
	CString c_seekstring="NAME= '";
	c_seekstring+=Charname;
	c_seekstring+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		COleVariant varValue(_T(StatValue),VT_BSTRT);
		RecSet->Edit();
		RecSet->SetFieldValue(StatName,varValue);
		try
		{
			RecSet->Update();
		}
		catch(CDaoException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}
	//† NOT YET TESTED †//
}

void ACCESS::FillAbility(CString tablename,const CString &Charisma,const CString &Constitution,const CString &Dexterity,const CString &Intelligence,const CString &Strength,const CString &Wisdom)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_temp="SELECT * FROM ";
	c_temp+=tablename;
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,c_temp,0);

	COleVariant tempvar (_T(Charisma),VT_BSTRT);
	COleVariant tempvar2 (_T(Constitution),VT_BSTRT);
	COleVariant tempvar3 (_T(Dexterity),VT_BSTRT);
	COleVariant tempvar4 (_T(Intelligence),VT_BSTRT);
	COleVariant tempvar5 (_T(Strength),VT_BSTRT);
	COleVariant tempvar6 (_T(Wisdom),VT_BSTRT);

	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Charisma'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar);
		RecSet->Update();
	}
	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Constitution'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar2);
		RecSet->Update();
	}
	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Dexterity'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar3);
		RecSet->Update();
	}
	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Intelligence'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar4);
		RecSet->Update();
	}
	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Strength'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar5);
		RecSet->Update();
	}
	if(RecSet->Find(AFX_DAO_FIRST,"NAME= 'Wisdom'"))
	{
		RecSet->Edit();
		RecSet->SetFieldValue("VALUE",tempvar6);
		RecSet->Update();
	}
	RecSet->Close();
}

void ACCESS::FillTDevice2(CString tablename,const CStringArray &IP)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_temp="SELECT * FROM ";
	c_temp+=tablename;
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,c_temp,0);
	for (int i=0;i<IP.GetSize();i++)
	{
		COleVariant tempvar2 (ConvertIP(_T(IP[i])),VT_BSTRT);
		COleVariant life (_T("30"),VT_BSTRT);
		RecSet->AddNew();
		RecSet->SetFieldValue("IP",tempvar2);
		RecSet->SetFieldValue("LIFE",life);
		RecSet->Update();
	}
	RecSet->Close();
}

void ACCESS::FillTFakeMac(CString IP, const CStringArray& MAC)
{
	
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM FAKEMACTABLE",0);
	for (int i=0;i<MAC.GetSize();i++)
	{
		COleVariant tempvar (_T(IP),VT_BSTRT);
		COleVariant tempvar2 (_T(MAC[i]),VT_BSTRT);
		CString c_tmpIP="MAC= '";
		c_tmpIP+=MAC[i];
		c_tmpIP+="'";
		if(RecSet->Find(AFX_DAO_FIRST,c_tmpIP))
		{
			COleVariant var= RecSet->GetFieldValue("IP");
			if(FormatOleVariant(var)!=IP) //indien vorige ip een ander mac had -> vorige waarde deleten
			{				// str verkregen uit FormatOleVariant()
				RecSet->Delete();
				RecSet->AddNew();
				RecSet->SetFieldValue("IP",tempvar);
				RecSet->SetFieldValue("MAC",tempvar2);
				RecSet->Update();
			}
		}
		else
		{
			RecSet->AddNew();
			RecSet->SetFieldValue("IP",tempvar);
			RecSet->SetFieldValue("MAC",tempvar2);
			RecSet->Update();
		}
	}
	RecSet->Close();
}


CString ACCESS::FormatOleVariant(COleVariant var)
{  // Functie dat zorgt voor omzetting COleVariant -> CString
	CString str;
	switch (var.vt) 
	{
		case VT_BSTR:
		str = (LPCSTR) var.bstrVal; // narrow characters in DAO
		break;
		case VT_I2:
		str.Format("%d", (int) var.iVal);
		break;
		case VT_I4:
		str.Format("%d", var.lVal);
		break;
		case VT_R4:
		str.Format("%10.2f", (double) var.fltVal);
		break;
		case VT_R8:
		str.Format("%10.2f", var.dblVal);
		break;
		case VT_CY:
		str = COleCurrency(var).Format();
		break;
		case VT_DATE:
		str = COleDateTime(var).Format();
		break;
		case VT_BOOL:
		str = (var.boolVal == 0) ? "FALSE" : "TRUE";
		break;
		case VT_NULL:
		str = "----";
		break;
		default:
		str.Format("Unk type %d\n", var.vt);
		TRACE("Unknown type %d\n", var.vt);
	}
	return str;
}

void ACCESS::SetDbName(CString Setm_DbName)
{
	m_DbName=Setm_DbName;
}

void ACCESS::SetTableName(CString Setm_TableName)
{
	m_TableName=Setm_TableName;
}

void ACCESS::GetValue(CString tablename,CString columnname,CStringArray &PrintArray)
{
	/* Deze functie haalt de alle waarde op uit een door de gebruiker gedefineerde kolom */

	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		CString c_empty="Table is Empty!";
		AfxDaoTerm( ); // NIET VERGETEN !!!
		PrintArray.Add("EMPTY");
		RecSet->Close();
		return ;
	}

	RecSet->MoveFirst();
	COleVariant var;

	while(!RecSet->IsEOF())
	{
		var = RecSet->GetFieldValue(columnname);
		PrintArray.Add(FormatOleVariant(var));
		RecSet->MoveNext();
	}
	RecSet->Close();

}


void ACCESS::GetArray(CString tablename,CString column,CStringArray &List)
{
	CString c_value,c_tmp,Result;
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		List.Add("The list is empty");
		RecSet->Close();
	}

	else
	{
		RecSet->MoveFirst();
		COleVariant varvalue;
		while(!RecSet->IsEOF())
		{
			varvalue=RecSet->GetFieldValue(column);
			c_value=FormatOleVariant(varvalue);

			Result=c_value;
			List.Add(Result);
			
			RecSet->MoveNext();
		}
		RecSet->Close();
	}
}

void ACCESS::GetCharArray(CString UserName,CStringArray &List)
{
	CString c_value,Result,c_tempvalue;
	bool empty=true;
	CStringArray TempList;
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM USERTABLE", 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
	//	TempList.Add("The list is empty");
		RecSet->Close();
	}

	else
	{
		RecSet->MoveFirst();
		COleVariant varvalue;
		COleVariant varUserName;
		while(!RecSet->IsEOF())
		{
			varvalue=RecSet->GetFieldValue("USERNAME");
			c_value=FormatOleVariant(varvalue);
			if(c_value==UserName)
			{
				empty=false;
				varUserName=RecSet->GetFieldValue("CHARACTER_ID");
				c_tempvalue=FormatOleVariant(varUserName);
				Result=c_tempvalue;
				TempList.Add(Result);
			}
			
			RecSet->MoveNext();
		}
		RecSet->Close();
	}
	//if(TempList[0]!="The list is empty")
	if(!empty)
	{
		CString FinalResult;
		try
		{
			for(int i=0;i<TempList.GetSize();i++)
			{
				FinalResult=GetValue("CHARACTERTABLE","CHARACTER_ID","NAME",TempList[i]);
				if(FinalResult!="Not Found")
					List.Add(FinalResult);
			}
		}
		catch(CDaoException *e)
		{
			e->ReportError();
			e->Delete();
		}
	}
	else
		List.Add("The list is empty");

	/*for(int j=0;j<List.GetSize();j++)
		AfxMessageBox(List[j]);*/
}

void ACCESS::UseSameChar(CString UserName,CString CharacterName)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM USERTABLE", 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
	//	TempList.Add("The list is empty");
		RecSet->Close();
	}

	else
	{
		CDaoRecordset* RecSet2; 
		RecSet2 = new CDaoRecordset(&DaoDb);
		if ( !RecSet2->IsOpen() )
			RecSet2->Open( dbOpenDynaset ,"SELECT * FROM CHARACTERTABLE", 0 );	
		if( RecSet2->IsBOF() )
		{
			AfxDaoTerm( ); // NIET VERGETEN !!!
		//	TempList.Add("The list is empty");
			RecSet2->Close();
		}
		else
		{
			COleVariant tempID,tempUserName(_T(UserName),VT_BSTRT);
			CString ID,c_seekstring="NAME= '";
			c_seekstring+=CharacterName;
			c_seekstring+="'";
			if(RecSet2->Find(AFX_DAO_FIRST,c_seekstring))
			{
				tempID=RecSet2->GetFieldValue("CHARACTER_ID");
			//	ID=FormatOleVariant(tempID);
			}
			else
				return;
			RecSet2->Close();

			RecSet->AddNew();
			RecSet->SetFieldValue("USERNAME",tempUserName);
			RecSet->SetFieldValue("CHARACTER_ID",tempID);
			RecSet->Update();
			RecSet->Close();
		}
	}
}

void ACCESS::MakeNewChar(CString UserName,CString CharacterName)
{
// FASE 1: FIND THE RIGHT CHARACTER_ID (auto-incr)
	COleVariant tempID;
	CString ID;
	int n_ID;
	int old_ID=0;
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM CHARACTERTABLE", 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
	//	TempList.Add("The list is empty");
		RecSet->Close();
	}

	else
	{
		RecSet->MoveFirst();
		while(!RecSet->IsEOF())
		{
			tempID=RecSet->GetFieldValue("CHARACTER_ID");

			ID=FormatOleVariant(tempID);
			n_ID=atoi(ID);
			if(n_ID>old_ID)
				old_ID=n_ID;
			RecSet->MoveNext();
		}
		old_ID++;
		ID.Format("%d",old_ID);
		RecSet->Close();
	}

	// FASE 2: ADD THE NEW CHARACTER_ID TO THE USERTABLE
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM USERTABLE", 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
	//	TempList.Add("The list is empty");
		RecSet->Close();
	}
	else
	{
		COleVariant newID(_T(ID),VT_BSTRT);
		COleVariant tempUserName(_T(UserName),VT_BSTRT);
		RecSet->AddNew();
		RecSet->SetFieldValue("USERNAME",tempUserName);
		RecSet->SetFieldValue("CHARACTER_ID",newID);
		RecSet->Update();
		RecSet->Close();
	}

	// FASE 3: ADD THE NEW CHARACTER_ID AND CHARACTERNAME TO THE USERTABLE
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM CHARACTERTABLE", 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
	//	TempList.Add("The list is empty");
		RecSet->Close();
	}

	else
	{
		try
		{
			COleVariant newID(_T(ID),VT_BSTRT);
			COleVariant tempCharacterName(_T(CharacterName),VT_BSTRT);
			COleVariant empty(_T("not defined"),VT_BSTRT);
			RecSet->AddNew();
			RecSet->SetFieldValue("CHARACTER_ID",newID);
			RecSet->SetFieldValue("NAME",tempCharacterName);
			RecSet->SetFieldValue("RACE",empty);
			RecSet->SetFieldValue("CLASS",empty);
			RecSet->SetFieldValue("DEITY",empty);
			RecSet->SetFieldValue("ALIGNMENT",empty);
			RecSet->SetFieldValue("FAMILIAR",empty);
			RecSet->SetFieldValue("LANGUAGES",empty);
			RecSet->SetFieldValue("GENDER",empty);
			RecSet->SetFieldValue("PICTURE",empty);
			RecSet->SetFieldValue("DESCRIPTION",empty);
			RecSet->SetFieldValue("AGE",empty);
			RecSet->SetFieldValue("ARMORCLASS",empty);
			RecSet->SetFieldValue("ITEMLIST_ID",empty);
			RecSet->SetFieldValue("STRENGTH",empty);
			RecSet->SetFieldValue("DEXTERITY",empty);
			RecSet->SetFieldValue("CONSTITUTION",empty);
			RecSet->SetFieldValue("INTELLIGENCE",empty);
			RecSet->SetFieldValue("WISDOM",empty);
			RecSet->SetFieldValue("CHARISMA",empty);
			RecSet->Update();
			RecSet->Close();
		}
		catch(CDaoException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}
}

void ACCESS::MakeNewChar2(CString UserName,CString CharacterName)
{
	// Deze functie wordt aangeroepen indien we vertrokken zijn van een nieuwe database
	// ---> dus geen zorgen maken over Char ID
	CString ID="1";
	CDaoRecordset* RecSet; // Define Recordset object

	// FASE 2: ADD THE NEW CHARACTER_ID TO THE USERTABLE
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM USERTABLE", 0 );

	COleVariant newID(_T(ID),VT_BSTRT);
	COleVariant tempUserName(_T(UserName),VT_BSTRT);
	RecSet->AddNew();
	RecSet->SetFieldValue("USERNAME",tempUserName);
	RecSet->SetFieldValue("CHARACTER_ID",newID);
	RecSet->Update();
	RecSet->Close();


	// FASE 3: ADD THE NEW CHARACTER_ID AND CHARACTERNAME TO THE USERTABLE
	RecSet = new CDaoRecordset(&DaoDb);
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,"SELECT * FROM CHARACTERTABLE", 0 );


	try
	{
		COleVariant newID(_T(ID),VT_BSTRT);
		COleVariant tempCharacterName(_T(CharacterName),VT_BSTRT);
		COleVariant empty(_T("not defined"),VT_BSTRT);
		RecSet->AddNew();
		RecSet->SetFieldValue("CHARACTER_ID",newID);
		RecSet->SetFieldValue("NAME",tempCharacterName);
		RecSet->SetFieldValue("RACE",empty);
		RecSet->SetFieldValue("CLASS",empty);
		RecSet->SetFieldValue("DEITY",empty);
		RecSet->SetFieldValue("ALIGNMENT",empty);
		RecSet->SetFieldValue("FAMILIAR",empty);
		RecSet->SetFieldValue("LANGUAGES",empty);
		RecSet->SetFieldValue("GENDER",empty);
		RecSet->SetFieldValue("PICTURE",empty);
		RecSet->SetFieldValue("DESCRIPTION",empty);
		RecSet->SetFieldValue("AGE",empty);
		RecSet->SetFieldValue("ARMORCLASS",empty);
		RecSet->SetFieldValue("ITEMLIST_ID",empty);
		RecSet->SetFieldValue("STRENGTH",empty);
		RecSet->SetFieldValue("DEXTERITY",empty);
		RecSet->SetFieldValue("CONSTITUTION",empty);
		RecSet->SetFieldValue("INTELLIGENCE",empty);
		RecSet->SetFieldValue("WISDOM",empty);
		RecSet->SetFieldValue("CHARISMA",empty);
		RecSet->Update();
		RecSet->Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}

void ACCESS::GetBan_List(CStringArray &List)
{
	/* Deze functie haalt alle waarden uit kolom IP en USERNAME uit Ban_List*/
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp="SELECT * FROM Ban_List";
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		List.Add("The ban list is empty");
		RecSet->Close();
		return ;
	}

	RecSet->MoveFirst();
	COleVariant varUSERNAME;
	COleVariant varIP;
	CString IPke,Nameke,Result;

	while(!RecSet->IsEOF())
	{
		varIP=RecSet->GetFieldValue("IP");
		IPke=FormatOleVariant(varIP);
		varUSERNAME=RecSet->GetFieldValue("USERNAME");
		Nameke=FormatOleVariant(varUSERNAME);

		Result="IP: ";
		Result+=IPke;
		Result+="   UserName: ";
		Result+=Nameke;
		List.Add(Result);
		
		RecSet->MoveNext();
	}
	RecSet->Close();
}

void ACCESS::GetUsers_List(CStringArray &List)
{
	/* Deze functie haalt alle waarden uit kolom USERNAME  uit OVERVIEW*/
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp="SELECT * FROM OVERVIEW";
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		List.Add("The ban list is empty");
		RecSet->Close();
		return ;
	}

	RecSet->MoveFirst();
	COleVariant varUSERNAME;
	CString Result;

	while(!RecSet->IsEOF())
	{
		varUSERNAME=RecSet->GetFieldValue("USERNAME");
		Result=FormatOleVariant(varUSERNAME);
		List.Add(Result);
		
		RecSet->MoveNext();
	}
	RecSet->Close();
}

CString ACCESS::GetValue(CString tablename,CString columnname,CString targetcolumn, CString seekvalue)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		CString c_empty="Table is Empty!";
	//	AfxMessageBox(c_empty);
		AfxDaoTerm( ); // NIET VERGETEN !!!
		RecSet->Close();
		return c_empty;
	}

	RecSet->MoveFirst();
	CString c_seekstring=columnname;
	c_seekstring+="= '";
	c_seekstring+=seekvalue;
	c_seekstring+="'";
	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		CString str;
		COleVariant var= RecSet->GetFieldValue(targetcolumn);
		str=FormatOleVariant(var);
		RecSet->Close();
		return str;
	}
	else
	{
		CString m_GetValue;
		RecSet->Close();
		return m_GetValue="Not Found";
	}

}

void ACCESS::GetValues(CString tablename,CString columnname,CString targetcolumn, CString seekvalue,CStringArray &values)
{
	// Haalt alle waarden uit een bepaalde kolom waar in de targetkolom de value=seekvalue

	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		values.Add("Table is Empty!");
	//	AfxMessageBox(c_empty);
		AfxDaoTerm( ); // NIET VERGETEN !!!
		RecSet->Close();
		return ;
	}

	RecSet->MoveFirst();
	CString c_seekstring=columnname;
	c_seekstring+="= '";
	c_seekstring+=seekvalue;
	c_seekstring+="'";

	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		CString str;
		COleVariant var= RecSet->GetFieldValue(targetcolumn);
		str=FormatOleVariant(var);
		values.Add(str);
		str.Empty();
		while(!RecSet->IsEOF())
		{
			if(RecSet->Find(AFX_DAO_NEXT,c_seekstring))
			{
				COleVariant var= RecSet->GetFieldValue(targetcolumn);
				str=FormatOleVariant(var);
				values.Add(str);
				str.Empty();
			}
		}

		RecSet->Close();
	}
	else
	{
		RecSet->Close();
		values.Add("Not Found");
	}

}

CString ACCESS::GetValue(CString tablename,CString columnname, CString seekvalue)
{
	/*
		Deze functie zoekt achter een bepaalde waarde, waarvoor de gebruiker moet definieren in welke
		kolom gezocht moet worden. De functie haalt dan automatisch de bijhorende waarde op 
		(zoek in IP kolom -> resultaat uit UserName kolom en vica versa) en returned deze
	*/

	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	if( RecSet->IsBOF() )
	{
		CString c_empty="Not found";
//		AfxMessageBox(c_empty);
		AfxDaoTerm( ); // NIET VERGETEN !!!
		RecSet->Close();
		return c_empty;
	}
	

	RecSet->MoveFirst();

	CString c_seekstring=columnname;
	c_seekstring+="= '";
	c_seekstring+=seekvalue;
	c_seekstring+="'";

	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		CString str;
		if(columnname=="IP")
		{
			COleVariant var= RecSet->GetFieldValue("USERNAME");
			str=FormatOleVariant(var);
		}
		else if(columnname=="USERNAME")
		{
			COleVariant var= RecSet->GetFieldValue("IP");
			str=FormatOleVariant(var);
		}
	
		RecSet->Close();
		return str;
	}
	else
	{
		CString m_GetValue="Not found";
		RecSet->Close();
		return m_GetValue;
	}
}


void ACCESS::CleanTable(CString tablename)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		return;
	}

	RecSet->MoveFirst();
	while(!RecSet->IsEOF())
	{
		RecSet->Delete();
		RecSet->MoveNext();
	}
	
}

void ACCESS::CleanTableBlock(CString tablename)
{
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
//		AfxMessageBox( "Table is Empty!");
		AfxDaoTerm( ); // NIET VERGETEN !!!
		return;
	}

	RecSet->MoveFirst();
	COleVariant varIP;
	COleVariant varMAC;
	COleVariant varLIFE;
	COleVariant varInterface;

	while(!RecSet->IsEOF())
	{
		bool einde=false;

		varInterface=RecSet->GetFieldValue("INTERFACE");
		CString firstInterface=FormatOleVariant(varInterface);

		varIP = RecSet->GetFieldValue("IP");
		CString seekvalue=FormatOleVariant(varIP);

		varMAC = RecSet->GetFieldValue("MAC");
		CString firstMAC=FormatOleVariant(varMAC);

		varLIFE = RecSet->GetFieldValue("LIFE");
		int n_life=atoi(FormatOleVariant(varLIFE));
		n_life--;
		CString c_life;
		c_life.Format("%d",n_life);
		COleVariant newlife (c_life,VT_BSTRT);
		
		if(n_life==0)
			RecSet->Delete();
		else
		{
			if(seekvalue=="?")  
			{//***********************************************
				CString c_seekstring="INTERFACE= '";
				c_seekstring+=firstInterface;
				c_seekstring+="'";
				if(RecSet->Find(AFX_DAO_NEXT,c_seekstring))// zoek volgende waarde waar interface zelfde is
				{
					RecSet->Find(AFX_DAO_FIRST,c_seekstring);
					COleVariant tempIP;
					RecSet->GetFieldValue("IP",tempIP);
					CString c_tempIP=FormatOleVariant(tempIP);
					if(c_tempIP=="?")
					{
						RecSet->Delete();
					}
					else
					{
						RecSet->Find(AFX_DAO_PREV,c_seekstring);
						RecSet->Edit();
						RecSet->SetFieldValue("LIFE",newlife);
						RecSet->Update();
						RecSet->Find(AFX_DAO_NEXT,c_seekstring);
						RecSet->Delete();
					}
				}//*********************************************
				else
				{
					if(RecSet->Find(AFX_DAO_PREV,c_seekstring))
					{
						RecSet->Edit();
						RecSet->SetFieldValue("LIFE",newlife);
						RecSet->Update();
						RecSet->Find(AFX_DAO_NEXT,c_seekstring);
						RecSet->Delete();
					}
				}
			}

			else
			{
				CString c_seekstring="IP= '";
				c_seekstring+=seekvalue;
				c_seekstring+="'";

				if(RecSet->Find(AFX_DAO_NEXT,c_seekstring))
				{	
					varInterface = RecSet->GetFieldValue("INTERFACE");
					CString lastInterface=FormatOleVariant(varInterface);
					if(lastInterface==firstInterface)
					{
						RecSet->Find(AFX_DAO_FIRST,c_seekstring);
						RecSet->Delete();
					}
					else
					{
						RecSet->Find(AFX_DAO_FIRST,c_seekstring);
						RecSet->Edit();
						RecSet->SetFieldValue("IP","?");
						RecSet->SetFieldValue("MAC","?");
						RecSet->Update();
					}
				}
				else
					RecSet->Find(AFX_DAO_FIRST,c_seekstring);
			}
		}

		RecSet->MoveNext();
	}

	/*	
		Beginnen bij RecSet->MoveFirst(), en LIFE van deze record -1 doen
			Controleer of LIFE hierna !=0, indien
				Ja: delete deze record
				Nee: Via Find AFX_DAO_NEXT controleren of het ip al voorkomt in de tabel
						Indien zo: is Mac anders? 
							Ja: delete de eerste record -> hoe?
								Terug een Find AFX_DAO_FIRST en deze record deleten
							Nee: verwijder record
				ga terug naar 'zoekrecord' (in het geval van 'ja' zitten we daar al)
			doe een MoveNext()
			van deze volgende record (LIFE -1) en bijkomstige controle
			herhaal de Find AFX_DAO_NEXT totdat we RecSet->IsBOF()

		[ADD]	Bij IP=? moet hij controleren ofdat de interfacename al voorkomt in de tabel 
				Dit gebeurt via de AFX_DAO_PREV. Indien deze interfacename reeds eerder in de tabel
				stond -> life-- bij de oude interfacename
	*/

	RecSet->Close();
	
}

void ACCESS::DeleteFakeMac(CString tablename)
{ /*
  doorloopt tabel van device
  als IP = ------
	MAC opzoeken in FAKEMACTABEL
		als bijbehorend IP (in FAKEMACTABEL) == IP van het device zelf
			IP en MAC -> ?  -> FAKE MAC!
		anders als bijbehorend IP = ander IP
			IP invullen
	*/
	
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
//		AfxMessageBox( "Table is Empty!");
		AfxDaoTerm( ); // NIET VERGETEN !!!
		return;
	}

	RecSet->MoveFirst();
	COleVariant varIP;
	COleVariant varMAC;
	
	while(!RecSet->IsEOF())
	{
		varIP = RecSet->GetFieldValue("IP");
		CString seekvalue=FormatOleVariant(varIP);
		varMAC = RecSet->GetFieldValue("MAC");
		CString seekvalue2="MAC = '";
		seekvalue2+=FormatOleVariant(varMAC);
		seekvalue2+="'";
		if(seekvalue=="-----------")
		{
			CDaoRecordset* RecSet2;
			RecSet2= new CDaoRecordset(&DaoDb);
			if( !RecSet2->IsOpen())
				RecSet2->Open(dbOpenDynaset, "SELECT * FROM FAKEMACTABLE",0);
			if(RecSet2->Find(AFX_DAO_FIRST, seekvalue2))
			{
				varIP = RecSet2->GetFieldValue("IP");
				CString CheckIP=FormatOleVariant(varIP);
				RecSet->Edit();
				if(CheckIP== tablename )
				{
					RecSet->SetFieldValue("IP","?");
					RecSet->SetFieldValue("MAC","?");
				}
				else
				{
					RecSet->SetFieldValue("IP", varIP);
					RecSet->SetFieldValue("MAC", varMAC);
				}
				RecSet->Update();
			}
			else
			{
				RecSet->Edit();
				RecSet->SetFieldValue("IP","?");
				RecSet->SetFieldValue("MAC","?");
				RecSet->Update();
			}
			RecSet2->Close();
		}
		RecSet->MoveNext();
	}	
	RecSet->Close();
}


void ACCESS::RemoveDoubles(CString tablename)
{// Controleer of er dubbele poorten in de table staan -> zoek op welk van de IP's een switch is,en
/*	CDaoRecordset* RecSet; //  vervang door dat 1ne device
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	CStringArray IPArray;
	CStringArray MACArray;
	CStringArray VLANArray;
	bool equal=false;
	bool firstfind=false;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	COleVariant tempInterface;
	COleVariant tempInterface2;
	COleVariant tempIP;
	COleVariant tempMAC;
	CString c_IP;
	CString c_MAC;
	CString ReplaceIP;
	CString TypeDevice;
	RecSet->MoveFirst();
	tempInterface=RecSet->GetFieldValue("INTERFACE");
	tempIP=RecSet->GetFieldValue("IP");
	c_IP=FormatOleVariant(tempIP);
	IPArray.Add(c_IP);
	tempMAC=RecSet->GetFieldValue("MAC");
	c_MAC=FormatOleVariant(tempMAC);
	MACArray.Add(c_MAC);
	RecSet->MoveNext();
	while(!RecSet->IsEOF())
	{
		tempInterface2=RecSet->GetFieldValue("INTERFACE");
		tempIP=RecSet->GetFieldValue("IP");
		c_IP=FormatOleVariant(tempIP);
		IPArray.Add(c_IP);
		tempMAC=RecSet->GetFieldValue("MAC");
		c_MAC=FormatOleVariant(tempMAC);
		MACArray.Add(c_MAC);
		CString IF1=FormatOleVariant(tempInterface);
		CString IF2=FormatOleVariant(tempInterface2);
		if(IF1==IF2)
		{
			equal=true;
			if(firstfind)
			{
				IPArray.RemoveAll();
				IPArray.Add(c_IP);
				MACArray.RemoveAll();
				MACArray.Add(c_MAC);
				firstfind=false;
			}
		}
		else
		{
			
			if(equal)
			{
				IPArray.RemoveAt(IPArray.GetSize()-1,1);
				MACArray.RemoveAt(MACArray.GetSize()-1,1);
			//	for(int k=0;k<IPArray.GetSize();k++)
			//		AfxMessageBox(IPArray[k]);
				equal=false;
				CDaoRecordset* RecSet2;
				RecSet2 = new CDaoRecordset(&DaoDb);
				if ( !RecSet2->IsOpen() )
					RecSet2->Open( dbOpenDynaset ,"SELECT * FROM OVERVIEW", 0 );
				RecSet2->MoveFirst();
				bool found=false;
				for(int i=0;i<IPArray.GetSize();i++)
				{
					CString c_seekstring="IP= '";
					c_seekstring+=IPArray[i];
				//	ReplaceIP=IPArray[i];
					//AfxMessageBox(ReplaceIP);
					c_seekstring+="'";

					if(RecSet2->Find(AFX_DAO_FIRST,c_seekstring))
					{
						COleVariant tempType=RecSet2->GetFieldValue("TYPE");
						CString c_Type=FormatOleVariant(tempType);
						if(c_Type=="23")
						{
							ReplaceIP=IPArray[i];
							COleVariant tempName=RecSet2->GetFieldValue("NAME");
							TypeDevice="->";
							TypeDevice+=FormatOleVariant(tempName);
							found=true;
						}
						else if(c_Type=="15")
						{
							ReplaceIP=IPArray[i];
							COleVariant tempName=RecSet2->GetFieldValue("NAME");
							CString c_tempName=FormatOleVariant(tempName);
							TypeDevice="->";
							TypeDevice+=FormatOleVariant(tempName);
							found=true;
							CreateTDevice(c_tempName);
							CStringArray temparray;
							IPArray.RemoveAt(i,1);
							MACArray.RemoveAt(i,1);
							for(int k=0;k<IPArray.GetSize();k++)
							{
								temparray.Add("Unknown");
								VLANArray.Add("?");			//TIJDELIJK
							}
							FillTDevice(c_tempName,temparray,VLANArray,IPArray,MACArray,MACArray,MACArray);
							temparray.RemoveAll();
							CleanTable(c_tempName);
						}
						else if(!found)
							ReplaceIP=IPArray[i];
					}
				}
				if(!found)
				{					
					CString Unknown="UnknownDevice";
					CString temp;
					temp.Format("%d",teller);
					teller++;
					Unknown+=temp;
					CreateTDevice(Unknown);
					TypeDevice="->";
					TypeDevice+=Unknown;
					CStringArray temparray;
					for(int k=0;k<IPArray.GetSize();k++)
					{
						temparray.Add("Unknown");
						VLANArray.Add("?");
					}
					FillTDevice(Unknown,temparray,VLANArray,IPArray,MACArray,MACArray,MACArray);
					temparray.RemoveAll();
					CleanTable(Unknown);
				}

				RecSet2->Close();

				CString c_seekstring="IP= '";
				c_seekstring+=ReplaceIP;
				c_seekstring+="'";
				
				RecSet->Find(AFX_DAO_FIRST,c_seekstring);
				RecSet->Edit();
				COleVariant Device (TypeDevice,VT_BSTRT);
				RecSet->SetFieldValue("CONNECTED DEVICE",Device);
				RecSet->Update();

				c_seekstring="INTERFACE= '";
				c_seekstring+=IF1;
				c_seekstring+="'";
				IF2=IF1;
				RecSet->Find(AFX_DAO_FIRST,c_seekstring);
				while(IF2==IF1)
				{
					COleVariant tempDevice=RecSet->GetFieldValue("CONNECTED DEVICE");
					CString c_Device=FormatOleVariant(tempDevice);
					if(c_Device=="----") // de lege waarde in ACCESS=----
						RecSet->Delete();
					RecSet->MoveNext();
					RecSet->GetFieldValue("INTERFACE",tempInterface2);
					IF2=FormatOleVariant(tempInterface2);
				}

				// pols via IPArray OVERVIEW af op zoek naar switch/hub
				// Doe dan een Find First IP van switch/hub en edit()
				// Doe dan een Find First IF1 en delete indien IP!=name switch/hub
				// Doe dan een Find Next + idem zolang Find Next een waarde vind
				// Doe dan een Find First IF2
			
				firstfind=true;
			}
			else
			{
				IPArray.RemoveAt(IPArray.GetSize()-2,1);//Verwijder steeds de voorlaatste waarde
				MACArray.RemoveAt(MACArray.GetSize()-2,1);//Verwijder steeds de voorlaatste waarde
			}

			tempInterface=tempInterface2;
		}
		RecSet->MoveNext();
	}

	RecSet->Close();*/
}

void ACCESS::CompleteDevice(CString tablename)
{
	/* Deze functie zal alle mogelijke lege waardes proberen te vullen */

	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	RecSet->MoveFirst();

	while(!RecSet->IsEOF())
	{
		COleVariant tempIP=RecSet->GetFieldValue("IP");
		CString c_IP=FormatOleVariant(tempIP);
		if(c_IP=="-----------")
		{
			COleVariant searchMAC=RecSet->GetFieldValue("MAC");
			CString c_searchMAC=FormatOleVariant(searchMAC);
			CDaoRecordset* RecSetFakeMac;
			RecSetFakeMac = new CDaoRecordset(&DaoDb);
			if ( !RecSetFakeMac->IsOpen() )
				RecSetFakeMac->Open( dbOpenDynaset ,"SELECT * FROM FAKEMACTABLE", 0 );
			RecSetFakeMac->MoveFirst();
			while(!RecSetFakeMac->IsEOF())
			{
				COleVariant newMAC=RecSetFakeMac->GetFieldValue("MAC");
				CString c_newMAC=FormatOleVariant(newMAC);
				COleVariant changeIP=RecSetFakeMac->GetFieldValue("IP");
				if(c_newMAC==c_searchMAC)
				{
					RecSet->Edit();
					RecSet->SetFieldValue("IP",changeIP);
					RecSet->Update();
				}
				RecSetFakeMac->MoveNext();
			}
			RecSetFakeMac->Close();
		}
		RecSet->MoveNext();
	}
	RecSet->Close();
}


void ACCESS::GetOverview(int type,CStringArray &NameArray, CStringArray &IPArray)
{
	/* Deze functie haalt alle waarden uit kolom NAME en IPwaarvoor TYPE=type */
	// vervang ineens _ door . in IPs
	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp="SELECT * FROM OVERVIEW";
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );

	if( RecSet->IsBOF() )
	{
		CString c_empty="Table is Empty!";
		AfxDaoTerm( ); // NIET VERGETEN !!!
		NameArray.Add("EMPTY");
		RecSet->Close();
		return ;
	}

	RecSet->MoveFirst();
	COleVariant var,var2;
	COleVariant vartype;
	CString newtype;
	CString oldtype;
	oldtype.Format("%d",type);

	while(!RecSet->IsEOF())
	{
		vartype=RecSet->GetFieldValue("TYPE");
		newtype=FormatOleVariant(vartype);
		if(oldtype==newtype)
		{
			var=RecSet->GetFieldValue("IP");
			IPArray.Add( FormatOleVariant(var));


			var2=RecSet->GetFieldValue("NAME");
			NameArray.Add(FormatOleVariant(var2));

		}
		RecSet->MoveNext();
	}
	RecSet->Close();

}


void ACCESS::CompleteTable(CString tablename)
{ //vult IP's in in de table, ahv van MAC uit ARP
	COleVariant vartmp;
	CStringArray ar_Interface;
	CStringArray ar_Mac;
	CStringArray ar_Ip;
	CString c_tmp;

	CDaoRecordset* RecSet; // Define Recordset object
	RecSet = new CDaoRecordset(&DaoDb);
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	RecSet->MoveFirst();
	while(!RecSet->IsEOF())
	{
		vartmp=RecSet->GetFieldValue("INTERFACE");
		ar_Interface.Add(FormatOleVariant(vartmp));

		vartmp=RecSet->GetFieldValue("MAC");   // stonden vroeger hieronder
		ar_Mac.Add(FormatOleVariant(vartmp));  //

		RecSet->MoveNext();
	}
/*	RecSet->MoveFirst();

	while(!RecSet->IsEOF())
	{
		vartmp=RecSet->GetFieldValue("MAC");
		ar_Mac.Add(FormatOleVariant(vartmp));
		RecSet->MoveNext();
	}*/	

	for(int i=0;i<ar_Interface.GetSize();i++)
	{
		ar_Ip.Add(GetValue("ARP","MAC",ar_Mac[i]));
	}
	RecSet->Close();	
//	FillTDevice(tablename,ar_Interface,ar_Ip,ar_Mac);

}

void ACCESS::FinishTable(CString tablename)
{// Controleer of er dubbele poorten in de table staan -> zoek op welk van de IP's een switch is,en
	CDaoRecordset* RecSet; //  vervang door dat 1ne device
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp;
	CString c_tempIP;
	CStringArray IPArray;
	CStringArray tempArray;
	bool equal=false;
	bool firstfind=false;
	bool KeepIP=false;
	bool hub=false;
	int teller=0;
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	COleVariant tempInterface;
	COleVariant tempInterface2;
	COleVariant tempIP;
	COleVariant ReplaceIP;
	CString c_IP;
	CString TypeDevice;
	RecSet->MoveFirst();
	tempInterface=RecSet->GetFieldValue("INTERFACE");
	tempIP=RecSet->GetFieldValue("IP");
	c_IP=FormatOleVariant(tempIP);
	IPArray.Add(c_IP);
	COleVariant varMEUH=RecSet->GetFieldValue("CONNECTED DEVICE");
	RecSet->MoveNext();
	while(!RecSet->IsEOF())
	{
		tempInterface2=RecSet->GetFieldValue("INTERFACE");
		tempIP=RecSet->GetFieldValue("IP");
		c_IP=FormatOleVariant(tempIP);
		IPArray.Add(c_IP);
		CString IF1=FormatOleVariant(tempInterface);
		CString IF2=FormatOleVariant(tempInterface2);
		if(IF1==IF2)
		{
			equal=true;
		}
		else
		{
			
			if(equal)
			{
				IPArray.RemoveAt(IPArray.GetSize()-1,1);
				equal=false;
				CDaoRecordset* RecSet2;
				RecSet2 = new CDaoRecordset(&DaoDb);
				if ( !RecSet2->IsOpen() )
					RecSet2->Open( dbOpenDynaset ,"SELECT * FROM OVERVIEW", 0 );
				RecSet2->MoveFirst();
				bool found=false;
				bool found2=false;
				for(int i=0;i<IPArray.GetSize();i++)
				{
					CString c_seekstring="IP= '";
					c_seekstring+=ConvertIP(IPArray[i]);
					c_seekstring+="'";
				//	AfxMessageBox(ConvertIP(IPArray[i]));
					if(ConvertIP(IPArray[i]).Compare(tablename))
					{
						teller++;
					}

					if(RecSet2->Find(AFX_DAO_FIRST,c_seekstring))
					{
						COleVariant tempType=RecSet2->GetFieldValue("TYPE");
						CString c_Type=FormatOleVariant(tempType);
						if(c_Type=="23")
						{
							CString c_temp=ConvertIP(IPArray[i]);
			
					//		AfxMessageBox(tablename);
					//		AfxMessageBox("Array:");
					//		for(int j=0;j<IPArray.GetSize();j++)
					//		{
					//			AfxMessageBox(IPArray[j]);
					//		}
					//		AfxMessageBox("Einde Array");

//	De IP's in de array zijn met '_', behalve de IP's die =tablename, die zijn met '.'

//	Wanneer er 3 switches in cascade hangen: nu gaat het programma de laatst gevonden
//	switch in de array van IP's gebruiken. 
//	Stelling: hoogstgelegen switch heeft de meeste MAC adressen van SWITCHES.
//	Gevolg: maak een struct voor elke switch gevonden in de iparray van die ene poort
//			wat moet er in staan: 
							if(c_temp.Compare(tablename))
							{
								hub=false;
								COleVariant tempName=RecSet2->GetFieldValue("NAME");
								ReplaceIP=RecSet2->GetFieldValue("IP");
								TypeDevice="->";
								TypeDevice+=FormatOleVariant(tempName);
								found=true;
							//	AfxMessageBox(TypeDevice);
							}
						}
						else if((c_Type=="15")&&!found)
						{
							hub=true;
							COleVariant tempName=RecSet2->GetFieldValue("NAME");
							ReplaceIP=RecSet2->GetFieldValue("IP");
							c_tempIP=FormatOleVariant(ReplaceIP);
							CString c_tempName=FormatOleVariant(tempName);
							TypeDevice="->";
							TypeDevice+=FormatOleVariant(tempName);
							
							tempArray.Copy(IPArray);
							found=true;
					//		CreateTDevice(c_tempName);
					//		CStringArray temparray;
					//		IPArray.RemoveAt(i,1);
					//		MACArray.RemoveAt(i,1);
					//		for(int k=0;k<IPArray.GetSize();k++)
					//		{
					//			temparray.Add("Unknown");
					//		}
					//		FillTDevice(c_tempName,temparray,IPArray,MACArray);
					//		temparray.RemoveAll();
					//		CleanTable(c_tempName);
						}
						else if((c_Type=="39")&&(!found))
						{
							COleVariant tempName=RecSet2->GetFieldValue("NAME");
							ReplaceIP=RecSet2->GetFieldValue("IP");
							CString c_tempName=FormatOleVariant(tempName);
							TypeDevice="->";
							TypeDevice+=FormatOleVariant(tempName);
							found2=true;
						}
						else if((c_Type=="7")&&(!found)&&(!found2))
						{
							COleVariant tempName=RecSet2->GetFieldValue("NAME");
							ReplaceIP=RecSet2->GetFieldValue("IP");
							CString c_tempName=FormatOleVariant(tempName);
							TypeDevice=FormatOleVariant(tempName);
							found2=true;
						}

					}
				}
				CString temp;
				temp.Format("%d",teller);
//				AfxMessageBox(temp);
				if((!found&&!found2)||(!found&&teller>1))
				{	
					CString Unknown="UnknownDevice";
					KeepIP=true;
				//	CString temp;
				//	temp.Format("%d",teller);
				//	teller++;
				//	Unknown+=temp;
				//	CreateTDevice(Unknown);
					TypeDevice="->";
					TypeDevice+=Unknown;
				//	CStringArray temparray;
				//	for(int k=0;k<IPArray.GetSize();k++)
				//	{
				//		temparray.Add("Unknown");
				//	}
				//	FillTDevice(Unknown,temparray,IPArray,MACArray);
				//	temparray.RemoveAll();
				//	CleanTable(Unknown);
				}

				if(hub)
				{
					hub=false;
					CreateTDevice2(c_tempIP);
					FillTDevice2(c_tempIP,tempArray);
					tempArray.RemoveAll();
					CString c_select="SELECT * FROM ";
					c_select+=c_tempIP;
					CDaoRecordset* RecSet3;
					RecSet3=new CDaoRecordset(&DaoDb);
					if ( !RecSet3->IsOpen() )
						RecSet3->Open( dbOpenDynaset ,c_select, 0 );
					RecSet3->MoveFirst();
					ReplaceIP=RecSet3->GetFieldValue("IP");
					c_tempIP=ConvertIP(FormatOleVariant(ReplaceIP));
//					AfxMessageBox(c_tempIP);
//					AfxMessageBox(tablename);
					while(!RecSet3->IsEOF())
					{
						if(c_tempIP.Compare(tablename))
						{
							CString c_seekstring="IP= '";
							c_seekstring+=c_tempIP;
							c_seekstring+="'";
							RecSet2->MoveFirst();
							if(RecSet2->Find(AFX_DAO_FIRST,c_seekstring))
							{
								COleVariant tempname=RecSet2->GetFieldValue("NAME");
								RecSet3->Edit();
								RecSet3->SetFieldValue("CONNECTED DEVICE",tempname);
								RecSet3->Update();
							}
							else
							{
								RecSet3->Edit();
								RecSet3->SetFieldValue("CONNECTED DEVICE",varMEUH);
								RecSet3->Update();
							}
						}
						else
						{
							RecSet3->Delete();
							RecSet3->MoveNext();
						}
						RecSet3->MoveNext();
					}
					RecSet3->Close();
				}

				RecSet2->Close();

				RecSet->MovePrev();
				RecSet->Edit();
				COleVariant Device (TypeDevice,VT_BSTRT);
				RecSet->SetFieldValue("CONNECTED DEVICE",Device);//Device);
				if(!KeepIP)
					RecSet->SetFieldValue("IP",ReplaceIP);
				RecSet->SetFieldValue("MAC",varMEUH);	// varMEUH is een lege waarde. 
														// dit is zo gedaan omdat ik er niet in
														// slaagde om een lege waarde te 'maken'
				RecSet->Update();
				teller=0;
				RecSet->MoveNext();

				IPArray.RemoveAll();
				IPArray.Add(c_IP);
				KeepIP=false;
			}
			else
			{
				RecSet->MovePrev();
				COleVariant varcheck=RecSet->GetFieldValue("IP");
				CString c_check=ConvertIP(FormatOleVariant(varcheck));
				if(!c_check.Compare(tablename)) // Vreemde logica :p
				{
					RecSet->Edit();
					RecSet->SetFieldValue("IP",varMEUH);
					RecSet->SetFieldValue("MAC",varMEUH);
					RecSet->Update();
				}
				RecSet->MoveNext();


				IPArray.RemoveAt(IPArray.GetSize()-2,1);//Verwijder steeds de voorlaatste waarde
			}

			tempInterface=tempInterface2;
		}
		RecSet->MoveNext();
	}
	RecSet->MovePrev();  // Zorgt ervoor dat ook nog de laatste waarde gechecked wordt
	COleVariant varcheck=RecSet->GetFieldValue("IP");
	CString c_check=ConvertIP(FormatOleVariant(varcheck));
	if(!c_check.Compare(tablename)) // Vreemde logica :p
	{
		RecSet->Edit();
		RecSet->SetFieldValue("IP",varMEUH);
		RecSet->SetFieldValue("MAC",varMEUH);
		RecSet->Update();
	}

	RecSet->Close();
	SmartComplete(tablename);
}

void ACCESS::SmartComplete(CString tablename)
{
	COleVariant o_IP;
	COleVariant o_Device;
	COleVariant o_Interface;
	COleVariant o_Interface2;
	CString c_IP;
	CString c_Device;
	CString c_Interface;
	CString c_tmp;

	CDaoRecordset* RecSet;
	RecSet = new CDaoRecordset(&DaoDb);
	c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	if ( !RecSet->IsOpen() )
		RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	CDaoRecordset* RecSet2;
	RecSet2 = new CDaoRecordset(&DaoDb);
	if ( !RecSet2->IsOpen() )
		RecSet2->Open( dbOpenDynaset ,"SELECT * FROM OVERVIEW", 0 );
	RecSet->MoveFirst();
	o_Interface=RecSet->GetFieldValue("INTERFACE");
	o_IP=RecSet->GetFieldValue("IP");
	RecSet->MoveNext();
	while(!RecSet->IsEOF())
	{
		o_Interface2=RecSet->GetFieldValue("INTERFACE");
		if(o_Interface==o_Interface2)
		{
			RecSet->MovePrev();
			RecSet->Delete();
			RecSet->MoveNext();
		}
		else
		{
			RecSet->MovePrev();
			o_IP=RecSet->GetFieldValue("IP");
			c_IP=FormatOleVariant(o_IP);
			o_Interface=RecSet->GetFieldValue("CONNECTED DEVICE");
			c_Interface=FormatOleVariant(o_Interface);
			RecSet2->MoveFirst();
			while(!RecSet2->IsEOF())
			{
				COleVariant o_IP2=RecSet2->GetFieldValue("IP");
				CString c_IP2=FormatOleVariant(o_IP2);
				if((ConvertIP(c_IP)==c_IP2)&&(c_Interface=="----"))
				{
					o_Device=RecSet2->GetFieldValue("Name");
					RecSet->Edit();
					RecSet->SetFieldValue("CONNECTED DEVICE",o_Device);
					RecSet->Update();
				}
				RecSet2->MoveNext();
			}
			RecSet->MoveNext();


		}
		RecSet->MoveNext();
		o_Interface=o_Interface2;
	}
	RecSet->Close();
	RecSet2->Close();

	// Wat moet gebeuren: dubbele poorten eruit halen, enkele laatste poort van de 
	// reeks laten staan (waar device is ingevuld).
	// Verder moet er ook steeds opgezocht worden of het IP voorkomt in Overview.
	// Indien dit het geval is, vul dan de bijhorende naam in in Connected Device kolom
	// Dit is nodig indien we geen FakeMacs hebben. Deze functie is dus nog niet getoetst aan
	// de praktijk, doch schrijvende veronderstelt dat ze wel zal werken. Merk op dat er 
	// geen '->' voor het device staat, omdat dit device toch geen andere IPs aan zich heeft 
	// hangen, en het dus zinloos is om hier een aparte tabel van te maken.

}

CString ACCESS::ConvertIP(CString IP)
{
	IP.Replace(".","_");
	return IP;

}

bool ACCESS::ExistTable(CString tablename)
{
	CDaoRecordset* RecSet;
	RecSet = new CDaoRecordset(&DaoDb);
	CString c_tmp="SELECT * FROM ";
	c_tmp+=tablename;
	TRY
	{
		if ( !RecSet->IsOpen() )
			RecSet->Open( dbOpenDynaset ,c_tmp, 0 );
	}
	CATCH(CDaoException,e)
	{
		e->Delete();
		return false;
	}
	AND_CATCH(CMemoryException,e)
	{
		e->Delete();
		e->ReportError();
		return false;
	}
	END_CATCH;

	RecSet->Close();
	return true;

}

bool ACCESS::ExistUser(CString Username)
{
	CDaoRecordset* RecSet;
	RecSet = new CDaoRecordset(&DaoDb);

	if (!RecSet->IsOpen())
		RecSet->Open(dbOpenDynaset,"SELECT * FROM OVERVIEW",0);
	if( RecSet->IsBOF() )
	{
		AfxDaoTerm( ); // NIET VERGETEN !!!
		RecSet->Close();
		return false;
	}
	CString c_seekstring="USERNAME= '";
	c_seekstring+=Username;
	c_seekstring+="'";
	RecSet->MoveFirst();
	if(RecSet->Find(AFX_DAO_FIRST,c_seekstring))
	{
		RecSet->Close();
		return true;
	}
	else
	{
		RecSet->Close();
		return false;
	}
}


void ACCESS::Close()
{
	DaoDb.Close();
	AfxDaoTerm( );
}



#endif