// CreatePlayer.cpp : implementation file
//

#include "stdafx.h"
#include "DnD.h"
#include "CreatePlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreatePlayer dialog


CCreatePlayer::CCreatePlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CCreatePlayer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreatePlayer)
	CharacterName = _T("");
	m_charisma = 0;
	m_wisdom = 0;
	m_strength = 0;
	m_intelligence = 0;
	m_dexterity = 0;
	m_constitution = 0;
	m_hitpoints = 0;
	m_ac = 0;
	m_will = 0;
	m_reflex = 0;
	m_fortitude = 0;
	m_initiative = 0;
	m_ranged = 0;
	m_melee = 0;
	m_age = 0;
	m_description = _T("");
	//}}AFX_DATA_INIT
}


void CCreatePlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreatePlayer)
	DDX_Control(pDX, IDC_DEITY, m_deity);
	DDX_Control(pDX, IDC_ALIGNMENT, m_alignment);
	DDX_Control(pDX, IDC_FAMILIAR, m_familiar);
	DDX_Control(pDX, IDC_RACE, m_race);
	DDX_Control(pDX, IDC_CLASS, m_class);
	DDX_Control(pDX, IDC_GENDER, m_gender);
	DDX_Text(pDX, IDC_CHARNAME, CharacterName);
	DDX_Text(pDX, IDC_CHA, m_charisma);
	DDX_Text(pDX, IDC_WIS, m_wisdom);
	DDX_Text(pDX, IDC_STR, m_strength);
	DDX_Text(pDX, IDC_INT, m_intelligence);
	DDX_Text(pDX, IDC_DEX, m_dexterity);
	DDX_Text(pDX, IDC_CON, m_constitution);
	DDX_Text(pDX, IDC_HITPOINTS, m_hitpoints);
	DDX_Text(pDX, IDC_AC, m_ac);
	DDX_Text(pDX, IDC_WILL, m_will);
	DDX_Text(pDX, IDC_REFLEX, m_reflex);
	DDX_Text(pDX, IDC_FORT, m_fortitude);
	DDX_Text(pDX, IDC_INITIATIVE, m_initiative);
	DDX_Text(pDX, IDC_RANGED, m_ranged);
	DDX_Text(pDX, IDC_MELEE, m_melee);
	DDX_Text(pDX, IDC_AGE, m_age);
	DDV_MinMaxInt(pDX, m_age, 0, 100000);
	DDX_Text(pDX, IDC_DESC, m_description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreatePlayer, CDialog)
	//{{AFX_MSG_MAP(CCreatePlayer)
	ON_BN_CLICKED(IDC_BTNPORTRAIT, OnBtnportrait)
	ON_BN_CLICKED(IDC_GENSTATS, OnGenstats)
	ON_CBN_CLOSEUP(IDC_CLASS, OnCloseupClass)
	ON_CBN_CLOSEUP(IDC_RACE, OnCloseupRace)
	ON_CBN_SELCHANGE(IDC_CLASS, OnSelchangeClass)
	ON_CBN_SELCHANGE(IDC_RACE, OnSelchangeRace)
	ON_EN_CHANGE(IDC_CHARNAME, OnChangeCharname)
	ON_BN_CLICKED(IDC_GENRAND, OnGenrand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreatePlayer message handlers

void CCreatePlayer::OnBtnportrait() 
{
	// TODO: Add your control notification handler code here
	CDndHeadMenu dlg;
	CString file;
	HBITMAP bmp;
	dlg.MaxHeadBitmaps=MaxHeadBitmaps;
	dlg.PortraitsPath=PortraitsPath;
	if(dlg.DoModal()==IDOK)
	{	
		CStatic* pHead= (CStatic*)GetDlgItem(IDC_HEAD);
		file.Format("Heads\\head%i.bmp",dlg.chosenhead);
		bmp=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,
							LR_DEFAULTSIZE|LR_LOADFROMFILE);
		pHead->SetBitmap(bmp);
		head=dlg.chosenhead;
	}
	else
	AfxMessageBox("No head  chosen!");
}

void CCreatePlayer::OnGenstats() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	Generated= TRUE;
	CStatic* strmod=(CStatic*)GetDlgItem(IDC_STRMOD);
	CStatic* conmod=(CStatic*)GetDlgItem(IDC_CONMOD);
	CStatic* chamod=(CStatic*)GetDlgItem(IDC_CHAMOD);
	CStatic* wismod=(CStatic*)GetDlgItem(IDC_WISMOD);
	CStatic* dexmod=(CStatic*)GetDlgItem(IDC_DEXMOD);
	CStatic* intmod=(CStatic*)GetDlgItem(IDC_INTMOD);

	CString test;
	int thestats[6];
	int temp;

	int astat[4];
	for(int j=0;j<6;j++)
	{
		for(int i=0;i<4;i++)
			astat[i]=DieRoll(6);
		 //enkel hoogste 3 worpen tellen mee ->Sorteren
		for(int k=0;k<4;k++)
		{
			if(astat[k+1]>astat[k])
			{	
				temp=astat[k];
				astat[k]=astat[k+1];
				astat[k+1]=temp;
			}
		}
		thestats[j]=astat[0]+astat[1]+astat[2];
	}	
	//voorlopig puur willekeurig toekennen
	AssignAbilities(thestats);
	// Vervolgens Racial modifiers
	AssignRacialAbilities(thestats);

	//Nu de ability modifiers
	int tempmod;
	CString stringmod;
	//strength
	tempmod=GetAbilityModifier(m_strength);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	strmod->SetWindowText(stringmod);

	//dex
	tempmod=GetAbilityModifier(m_dexterity);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	dexmod->SetWindowText(stringmod);

	//int
	tempmod=GetAbilityModifier(m_intelligence);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	intmod->SetWindowText(stringmod);
	//char
	tempmod=GetAbilityModifier(m_charisma);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	chamod->SetWindowText(stringmod);

	//wisdom
	tempmod=GetAbilityModifier(m_wisdom);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	wismod->SetWindowText(stringmod);
	//constitution
	tempmod=GetAbilityModifier(m_constitution);
		if(tempmod>-1)
			stringmod.Format("+%i",tempmod);
		else
			stringmod.Format("%i",tempmod);
	conmod->SetWindowText(stringmod);
	UpdateData(FALSE);

	//Hitpoints berekenen
	AssignHitPoints(m_constitution);
	//Saves berekenen
	AssignSaves();
	//Combat bonusses
	AssignCombatBonusses();
	//als total mods minder dan 0 is herrollen
	if(0>GetAbilityModifier(m_strength)+GetAbilityModifier(m_charisma)+
		GetAbilityModifier(m_dexterity)+GetAbilityModifier(m_constitution)+
		GetAbilityModifier(m_intelligence)+GetAbilityModifier(m_wisdom))
	
	{
		OnGenstats();
	}
	//als hoogste stat maar 13 is herrollen
	int totab=0;
	bool reroll=TRUE;
	for(int l=0;l<6;l++)
	{
		if(thestats[l]>13)
			reroll=FALSE;
	}
	if(reroll)
	{
		OnGenstats();
	}

	UpdateData(FALSE);

}

int CCreatePlayer::DieRoll(int sides)
{
	int value=0;
	while(value==0)
		value=rand()%sides+1;
	return value;
}

void CCreatePlayer::OnCloseupClass() 
{

}

void CCreatePlayer::OnCloseupRace() 
{
}

BOOL CCreatePlayer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	
	UCanGenerate=0;
	head=0;
	Generated=FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CCreatePlayer::GetAbilityModifier(int ability)
{
	int mod;
	if(ability%2!=0)
		ability--;

	mod=(ability-10)/2;


	return mod;
}

void CCreatePlayer::OnSelchangeClass() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	CString temp;
	CStatic* btn=(CStatic*)GetDlgItem(IDC_GENSTATS);
	CStatic* combofamiliar=(CStatic*)GetDlgItem(IDC_FAMILIAR);
	if(m_class.GetCurSel()!=CB_ERR)
	{
		m_class.GetLBText(m_class.GetCurSel(),temp);
		if(temp=="Wizard" || temp=="Sorcerer")
			//Enable familiar
		{
			combofamiliar->EnableWindow(TRUE);
		}
		else //disable familiar
		{
			combofamiliar->EnableWindow(FALSE);
		}
		switch(UCanGenerate)
		{
		case 0:
			UCanGenerate=3;
			break;
		case 2:
			UCanGenerate=5;
			btn->EnableWindow(TRUE);
			break;

		}
	}
}

void CCreatePlayer::OnSelchangeRace() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	CStatic* btn=(CStatic*)GetDlgItem(IDC_GENSTATS);
	CStatic* langs=(CStatic*)GetDlgItem(IDC_LANG);
	CString temp;
	if(m_race.GetCurSel()!=CB_ERR)
	{
	
		m_race.GetLBText(m_race.GetCurSel(),temp);
		if(temp=="Dwarf")
			langs->SetWindowText("Common and Dwarven");
		else if(temp=="Elf")
			langs->SetWindowText("Common and Elven");
		else if(temp=="Gnome")
			langs->SetWindowText("Common and Gnome");
		else if(temp=="Half-Elf")
			langs->SetWindowText("Common and Elven");
		else if(temp=="Half-Orc")
			langs->SetWindowText("Common and Orc");
		else if(temp=="Halfling")
			langs->SetWindowText("Common and Halfling");
		else if(temp=="Human")
			langs->SetWindowText("Common");



		
		switch(UCanGenerate)
		{
		case 0:
			UCanGenerate=2;
			break;
		case 3:
			UCanGenerate=5;
			btn->EnableWindow(TRUE);
			break;
		}
	}
	
	UpdateData(FALSE);

}

bool CCreatePlayer::AssignAbilities(int array[])
{
	CString temp;
	//BubbleSort(array,6);
	//
	m_strength=array[0];
	m_dexterity=array[1];
	m_intelligence=array[2];
	m_charisma=array[3];
	m_wisdom=array[4];
	m_constitution=array[5];
	return TRUE;
}

void CCreatePlayer::BubbleSort(int array[], int size)
{
  if (size > 1)
  {
    int finished = 0;
    int number = (size-1);
    while ((number > 0) && (!finished))
    {
      finished = 1;
      for (int i = 0; i < number; i++)
      {
        if (array[i] > array[i+1])
        {
          int j = array[i+1];
          array[i+1] = array[i];
          array[i] = j;
          finished = 0;
        }
      }
      number--;
    }
  }
}


void CCreatePlayer::OnChangeCharname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

bool CCreatePlayer::AssignRacialAbilities(int array[])
{
	CString temp;

	m_race.GetLBText(m_race.GetCurSel(),temp);
	CString dbg, dbg2;
	dbg.Format("Before:%i,%i,%i,%i,%i,%i", array[0],array[1],array[2],array[3],array[4],array[5]);
	if(temp=="Dwarf") 
	{
		array[5]=array[5]+2; //constitution +2
		if(array[5]<3)
			array[5]=3;
		array[3]=array[3]-2; //charisma -2
		if(array[3]<3)
			array[3]=3;
	}
	else if(temp=="Elf")
	{
		array[1]=array[1]+2; //dex +2
		if(array[1]<3)
			array[1]=3;
		array[5]=array[5]-2; //con -2
		if(array[5]<3)
			array[5]=3;
	}		
	else if(temp=="Gnome")
	{
		array[5]=array[5]+2; //constitution +2
		if(array[5]<3)
			array[5]=3;
		array[0]=array[0]-2; //strength -2
		if(array[0]<3)
			array[0]=3;
	}		
	else if(temp=="Half-Elf")
	{
		//no racial changes
	}		
	else if(temp=="Half-Orc")
	{
		array[0]=array[0]+2; //str +2
		if(array[0]<3)
			array[0]=3;
		array[3]=array[3]-2; //charisma -2
		if(array[3]<3)
			array[3]=3;
		array[2]=array[2]-2; //intelligence -2
		if(array[2]<3)
			array[2]=3;
	}		
	else if(temp=="Halfling")
	{
		array[1]=array[1]+2; //dext +2
		if(array[1]<3)
			array[1]=3;
		array[0]=array[0]-2; //strength -2
		if(array[0]<3)
			array[0]=3;
	}		
	else if(temp=="Human")
	{
		//no racial changes
	}
	dbg2.Format("\nAfter:%i,%i,%i,%i,%i,%i", array[0],array[1],array[2],array[3],array[4],array[5]);

//	AfxMessageBox(dbg+dbg2 );
	return true;
}

bool CCreatePlayer::AssignHitPoints(int con)
{
	CString temp;
	m_class.GetLBText(m_class.GetCurSel(),temp);
	int	conmod=GetAbilityModifier(con);
	m_hitpoints=0;
	if(temp=="Barbarian")
		m_hitpoints=12 +conmod;	
	else if(temp=="Bard")
		m_hitpoints=6 +conmod;
	else if(temp=="Cleric")
		m_hitpoints=8 +conmod;
	else if(temp=="Druid")
		m_hitpoints=8 +conmod;
	else if(temp=="Fighter")
		m_hitpoints=10 +conmod;
	else if(temp=="Monk")
		m_hitpoints=8 +conmod;
	else if(temp=="Paladin")
		m_hitpoints=10 +conmod;
	else if(temp=="Ranger")
		m_hitpoints=10 +conmod;
	else if(temp=="Rogue")
		m_hitpoints=6 +conmod;
	else if(temp=="Sorcerer")
		m_hitpoints=4 +conmod;
	else if(temp=="Wizard")
		m_hitpoints=4 +conmod;
	

	if(m_hitpoints==0)
		AfxMessageBox("Error in AssignHitPoints(), please check spelling of classes");
	UpdateData(FALSE);
	return true;
}

bool CCreatePlayer::AssignSaves()
{
	CString temp,tempfam;
	m_class.GetLBText(m_class.GetCurSel(),temp);
	//ability mods
	int	conmod=GetAbilityModifier(m_constitution);
	int dexmod=GetAbilityModifier(m_dexterity);
	int wismod=GetAbilityModifier(m_wisdom);
	int chamod=GetAbilityModifier(m_charisma);
	//base saves
	int refmod=0;
	int wilmod=0;
	int fortmod=0;
	//misc saves
	int refmisc=0;
	int wilmisc=0;
	int fortmisc=0;


	UpdateData(TRUE);

	if(temp=="Barbarian")
	{
		fortmod=2;
		refmod=0;
		wilmod=0;
	}
	else if(temp=="Bard")
	{
		fortmod=0;
		refmod=2;
		wilmod=2;
	}		
	else if(temp=="Cleric")
	{
		fortmod=2;
		refmod=0;
		wilmod=2;
	}
	else if(temp=="Druid")
	{
		fortmod=2;
		refmod=0;
		wilmod=2;
	}
	else if(temp=="Fighter")
	{
		fortmod=2;
		refmod=0;
		wilmod=0;
	}
	else if(temp=="Monk")
	{
		fortmod=2;
		refmod=2;
		wilmod=2;
		if(wismod>0)
		{
		fortmisc=wismod;
		refmisc=wismod;
		wilmisc=wismod;
		}
	}
	else if(temp=="Paladin")
	{
		fortmod=2;
		refmod=0;
		wilmod=0;
		//pala krijgt ook nog charisma als misc;
		fortmisc=chamod;
		refmisc=chamod;
		wilmisc=chamod;
	}
	else if(temp=="Ranger")
	{
		fortmod=2;
		refmod=0;
		wilmod=0;
	}
	else if(temp=="Rogue")
	{
		fortmod=0;
		refmod=2;
		wilmod=0;
	}
	else if(temp=="Sorcerer" || temp=="Wizard")
	{
		fortmod=0;
		refmod=0;
		wilmod=2;
		//familiar mods 
			m_familiar.GetLBText(m_familiar.GetCurSel(),tempfam);
			if(tempfam=="Rat")
				fortmisc=2;
			else if(tempfam=="Weasel")
				refmisc=2;

	}

	m_reflex=refmod+dexmod+refmisc;
	m_will=wilmod+wismod+wilmisc;
	m_fortitude=fortmod+conmod+fortmisc;

	return true;
}

bool CCreatePlayer::AssignCombatBonusses()
{
	CString temp;
	int base=0;
	m_class.GetLBText(m_class.GetCurSel(),temp);
	int dexmod=GetAbilityModifier(m_dexterity);
	int strmod=GetAbilityModifier(m_strength);
	//initiative
	int tempinit=0;
	//if(improved_init_feat)
	//	tempinit=4;
	m_initiative=dexmod+tempinit;

	//melee and ranged
	if(temp=="Barbarian")
		base=1;
	else if(temp=="Bard")
		base=0;
	else if(temp=="Cleric")
		base=0;
	else if(temp=="Druid")
		base=0;
	else if(temp=="Fighter")
		base=1;
	else if(temp=="Monk")
		base=0;
	else if(temp=="Paladin")
		base=1;
	else if(temp=="Ranger")
		base=1;
	else if(temp=="Rogue")
		base=0;
	else if(temp=="Sorcerer")
		base=0;
	else if(temp=="Wizard")
		base=0;
	
	m_melee=strmod+base;
	m_ranged=dexmod+base;
	
	return true;
}

void CCreatePlayer::OnOK() 
{
	// TODO: Add extra validation here
		CString temp;
		int fault=0;
		
		if(CharacterName.Find(" ")!=-1)
		{
			if(IDNO==AfxMessageBox("No spaces allowed in name. Do you want them replaced by underscores? Click no to choose a new character name",MB_YESNO|MB_ICONQUESTION   ,0))
				fault=1;
			else
			{
				CharacterName.Replace(" ","_");
				AfxMessageBox("Changed");
			}
		}
		
		UpdateData(FALSE);
		if(!CharacterName.IsEmpty())
		{
		ThePlayer.CharacterName=CharacterName;
		}
		else fault=1;

		if(m_gender.GetCurSel()!=CB_ERR)
			m_gender.GetLBText(m_gender.GetCurSel(),ThePlayer.Gender);
		else fault=1;
		
		if(head!=0)
			ThePlayer.head=head;
		else fault=1;
		
		if(m_alignment.GetCurSel()!=CB_ERR)
			m_alignment.GetLBText(m_alignment.GetCurSel(),ThePlayer.Alignment);
		else fault=1;


		if(m_class.GetCurSel()!=CB_ERR)
		{
			m_class.GetLBText(m_class.GetCurSel(),ThePlayer.Class);
			m_class.GetLBText(m_class.GetCurSel(),temp);
		}
		else fault=1;

		if(m_description.IsEmpty())
			m_description.Format("A standard character (No description given)");
		ThePlayer.Description=m_description;

		if(Generated)
		{
			ThePlayer.Constitution=m_constitution;
			ThePlayer.Strength=m_strength;
			ThePlayer.Wisdom=m_wisdom;
			ThePlayer.Intelligence=m_intelligence;
			ThePlayer.Dexterity=m_dexterity;
			ThePlayer.Charisma=m_charisma;
		}
		else fault=1;

		if(m_deity.GetCurSel()!=CB_ERR)
			m_deity.GetLBText(m_deity.GetCurSel(),ThePlayer.Deity);
		else fault=1;
			
		
	
		if(temp=="Wizard"|| temp=="Sorcerer")
			m_familiar.GetLBText(m_familiar.GetCurSel(),ThePlayer.Familiar);
		else
			ThePlayer.Familiar="None";

		
		if(m_race.GetCurSel()!=CB_ERR)
			m_race.GetLBText(m_race.GetCurSel(),ThePlayer.Race);
		else fault=1;

	


		if(m_age!=0)
			ThePlayer.Age=m_age;
		else fault=1;

		//controleren op dubbele naam
		for(int i=0;i<ForbiddenNames.GetSize();i++)
		{
			if(CharacterName.Compare(ForbiddenNames.GetAt(i))==0)
				fault=3;
			else fault = 0;

		}
		
		if(fault==1)
		{
			AfxMessageBox("Not all fields are filled in properly. Please make sure they are before continuing");
			fault=0;
		}
		else if(fault==3)
		{
			AfxMessageBox("Charactername already exists, please choose new one",MB_ICONINFORMATION   ,0);
		}

		if(fault!=1 && fault!=3)
			CDialog::OnOK();
}

void CCreatePlayer::OnGenrand() 
{
	// TODO: Add your control notification handler code here

	CStatic* combofamiliar=(CStatic*)GetDlgItem(IDC_FAMILIAR);	
	CString file;
	HBITMAP bmp;
	

	CString temp;
	
	m_gender.SetCurSel(rand()%2);
	CharacterName.Format("%s",NameGenerator(m_gender.GetCurSel()));
	
	OnBtnportrait();
	while(head==0)
		head=rand()%15;
	m_alignment.SetCurSel(rand()%m_alignment.GetCount());
	m_class.SetCurSel(rand()%m_class.GetCount());
	m_class.GetLBText(m_class.GetCurSel(),temp);


	m_deity.SetCurSel(rand()%m_deity.GetCount());

	if(temp=="Wizard"|| temp=="Sorcerer")
	{
		combofamiliar->EnableWindow(TRUE);
		m_familiar.SetCurSel(rand()%m_familiar.GetCount());
	}
	else
		combofamiliar->EnableWindow(FALSE);
	m_race.SetCurSel(rand()%m_race.GetCount());
	m_age=rand()%200;
	OnGenstats();
	m_description=DescGenerator();
	CStatic* pHead= (CStatic*)GetDlgItem(IDC_HEAD);
	file.Format("Heads\\head%i.bmp",head);
	bmp=(HBITMAP)LoadImage(NULL,file,IMAGE_BITMAP,0,0,
						LR_DEFAULTSIZE|LR_LOADFROMFILE);
	pHead->SetBitmap(bmp);
	

	UpdateData(FALSE);
}

CString CCreatePlayer::NameGenerator(int randgetal)
{



	//poging tot random generator.Feel free to laugh:p
	//here goes
	CString Name,str;
	CString klinker="aieou";
	CString medeklinker="bcdfghjklmnprstvwz";
	bool IsKlinker=FALSE;;
	char ch;
	int namesize=5+rand()%6, j;
	for(int i=0;i<namesize;i++)
	{

		switch(i)
		{
		case 0:
			//hoofdletter
			ch=65+rand()%26;
			break;
		default:
			//kijken of vorige klinker is
			for(j=0;j<5;j++)
			{
				if(klinker[j]==Name[i-1])
					IsKlinker=TRUE;
			}
			if(IsKlinker)
				ch=medeklinker[rand()%medeklinker.GetLength()];
			else
				ch=klinker[rand()%klinker.GetLength()];
			break;
		}
		Name.Format("%s%c",str,ch);
		str=Name;
		IsKlinker=FALSE;		
	}

	for(j=0;j<5;j++)
	{
		if(klinker[j]==Name[i-1])
			IsKlinker=TRUE;
	}
	if(randgetal==1&&!IsKlinker)
	{//tis een vrouw
		ch=klinker[rand()%3];
		Name.Format("%s%c",str,ch);
	}
/*
	if(randgetal==0)
		return SillyNamesMale.GetAt(rand()%SillyNamesMale.GetSize());
	else
		return SillyNamesFeMale.GetAt(rand()%SillyNamesFeMale.GetSize());*/

	return Name;

}

CString CCreatePlayer::DescGenerator()
{
	CString Desc,str,gender,classs,align,race,deit;
	m_gender.GetLBText(m_gender.GetCurSel(),gender);
	m_class.GetLBText(m_class.GetCurSel(),classs);
	m_alignment.GetLBText(m_alignment.GetCurSel(),align);
	m_race.GetLBText(m_race.GetCurSel(),race);
	m_deity.GetLBText(m_deity.GetCurSel(),deit);
	gender.MakeLower();
	classs.MakeLower();
	race.MakeLower();
	align.MakeLower();
	deit.MakeLower();
	Desc.Format("%s the %s %s.A %s %s who worships %s.",CharacterName,gender,classs,align,race,deit);
 
	return Desc;
}
