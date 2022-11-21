#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>
#include<iomanip>
#include <time.h>
#include <conio.h>

using namespace std;
string passwordInput(unsigned maxLength);
string password(unsigned maxLength);
void setCoLor(int backgound_color, int text_color);
void dinhDang();
class TheTu
{
    protected:	
	string id;
	string pin;
	bool status;

public:
	string getID() { return id; }
	bool getStatus() { return status; }
	void setPin (string s) { pin = s; }
	void setStatus (bool n) { status = n; }
	TheTu(string _id = "", string _pin = "")
	{
		id = _id;
		pin = _pin;
		status = 1;
	}

	TheTu (const TheTu &p)
	{
		id = p.id;
		pin = p.pin;
		status = p.status;
	}
	
	void set(string _id, string _pin)
	{
		id = _id;
		pin = _pin;
		status = 1;
	}

	~TheTu(){};

	friend istream& operator >> (istream& is, TheTu &p)
	{
		is >> p.id;
		is >> p.pin;
		is >> p.status;
		return is;
	} 
	
	friend void loadDSTheTu(TheTu a[], int &n)
	{
		ifstream in;
		in.open("TheTu.txt");
		if(in.is_open())
		{
			n = 0;
			while(in >> a[n]) { n++; }
			in.close();
		}
		else
		{
			cout << setw (70) << right << "He thong dang bao tri moi ban quay lai sau !!!" << endl;
			exit(0);
		}	
	}

	void updateDSTheTu(TheTu a[], int n)
	{
		ofstream o;
		o.open("TheTu.txt");
		for (int i = 0; i < n; ++i)
		{
			o << a[i].id << endl;
			o << a[i].pin << endl;
			o << a[i].status << endl;
		}
		o.close();
	}

	void ghiNoiDungGiaoDich(string _loaigiaodich, long _sotien)
	{
		time_t now;
		time(&now);
		string s;
		s = ctime(&now);
		ofstream o;
		o.open("LichSuID.txt", ios:: app);
		o << id << endl;
		o << _loaigiaodich << endl;
		o << _sotien << endl;
		o << s; 
		o.close();
	}

	int SearchID(TheTu a[], int n, string _id)
	{
		int index = -1;
		for (int i = 0; i < n; ++i)
		{
			if(a[i].id == _id){
				index = i;
				break;
			}
		}
		return index;
	}
	void dangNhapUser(TheTu a[], int n, int &index)
	{
		string _id, _pin;
		int dem = 0;
		while(true)
		{
			system("cls");
			cout << setw (70) << right << "*************************************" << endl;
			cout << setw(70) << right << "            DANG NHAP USER            "<<endl;
			cout << setw (70) << right << "*************************************" << endl;
			cout << setw(44) << right << "ID: ";
			cin >> _id;
			index = SearchID(a, n, _id);
			if (index == -1)
			{
				system("cls");
				cout << "\n\n\n";
				cout << setw(55) << right << "ID khong ton tai !!!" << endl;
				cout << "\n\n\n";
				cout << setw(55) << right << system("pause");
			}
			else
			{
				if(a[index].status == 0)
				{
					cout << setw(67) << right << "TAI KHOAN CUA BAN DA BI KHOA !!!" << endl;
					cout << setw(66) << right << "LIEN HE NGAN HANG DE GIAI QUYET" << endl;
					system("pause");
					exit(0);
				}	
				while(dem < 3)
				{	
					cout << setw(44) << right << "PIN: ";
					_pin = passwordInput(6);
					if (a[index].pin == _pin)
					{
						system("cls");
						cout << "\n\n\n";
						cout << setw(75) << right << "------------DANG NHAP THANH CONG-----------" << endl;
						cout << "\n\n\n";
						system("pause");
						system("cls");
						return;
					}
					else
					{
						dem++;
						system("cls");
						cout << "\n\n\n";
						cout << setw(55) << right  << "Sai ma PIN !!!" << endl;
						cout << "\n\n\n";
						system("pause");
						system("cls");
						cout << setw (70) << right << "*************************************" << endl;
						cout << setw(70) << right << "            DANG NHAP USER            "<<endl;
						cout << setw (70) << right << "*************************************" << endl;
						cout << setw(44) << right << "ID: " << _id << endl;
					}	
				}
				a[index].status = 0;
				updateDSTheTu(a, n);
				cout << setw(67) << right << "TAI KHOAN CUA BAN DA BI KHOA !!!" << endl;
				cout << setw(66) << right << "LIEN HE NGAN HANG DE GIAI QUYET" << endl;
				system("pause");
				exit(0);
				return;	
			}	
		}		
	}

	void doiMaPin()
	{
		string _pin1,_pin2;
		tryagain:
		cout << setw (70) << right << "             Doi Ma Pin             " << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw (34) << "" << "Nhap ma PIN moi: ";
		_pin1 = passwordInput(6);
		cout << setw (34) << "" << "Nhap lai ma PIN: ";
		_pin2 = passwordInput(6);
		if (_pin1 == _pin2)
		{
			pin = _pin1;
			cout << setw (34) << "" << "Ban da doi ma PIN thanh cong !!!" << endl;
		}
		else
		{
			cout << setw (34) << "" << "Ma PIN khong khop !!!" << endl;
			system("pause");
			system("cls");
			cout << "\n\n";
			cout << setw (70) << right << "****************Menu*****************" << endl;
			cout << setw (70) << right << "     1. Xem thong tin tai khoan      " << endl;
			cout << setw (70) << right << "     2. Rut tien                     " << endl;
			cout << setw (70) << right << "     3. Chuyen tien                  " << endl;
			cout << setw (70) << right << "     4. Xem noi dung giao dich       " << endl;
			cout << setw (70) << right << "     5. Doi ma PIN                   " << endl;
			cout << setw (70) << right << "     6. Thoat                        " << endl;
			cout << setw (70) << right << "*************************************" << endl;
			goto tryagain;
		}	
	}

};

class User : public TheTu 
{
protected:	
	string name;
	long sodu;
	string dv;

public:
	string getName() { return name; }
	long getSodu() { return sodu; }
	string getDv() { return dv; }
	User(string _name = "", long _sodu = 0, string _dv = "", string _id = "")
	{
		id = _id;
		name = _name;
		sodu = _sodu;
		dv = _dv;
	}

	User(const User &p)
	{
		id = p.id;
		name = p.name;
		sodu = p.sodu;
		dv = p.dv;
	}

	void set (string _id, string _name, long _sodu, string _dv)
	{
		id = _id;
		name = _name;
		sodu = _sodu;
		dv = _dv;
	}

	~User(){};

	friend istream& operator >> (istream& is, User &p)
	{
		is >> p.id;
		is.ignore();
		getline(is,p.name);
		is >> p.sodu;
		is.ignore();
		is >> p.dv;
		return is;
	}

	friend void LoadDSuser(User a[], int &n)
	{
		ifstream in;
		in.open("ID.txt");
		if(in.is_open())
		{
			n = 0;
			while(in >> a[n]) { n++; }
			in.close();
		}
		else
		{
			cout << setw (70) << right << "He thong dang bao tri moi ban quay lai sau !!!" << endl;
			exit(0);
		}	
	}

	void updateDSUser(User a[], int n)
	{
		ofstream o;
		o.open("ID.txt");
		for (int i = 0; i < n; ++i)
		{
			o << a[i].id << endl;
			o << a[i].name << endl;
			o << a[i].sodu << endl;
			o << a[i].dv << endl;
		}
	}

	void MenuUser()
	{
		cout << "\n\n";
		cout << setw (70) << right << "****************Menu*****************" << endl;
		cout << setw (70) << right << "     1. Xem thong tin tai khoan      " << endl;
		cout << setw (70) << right << "     2. Rut tien                     " << endl;
		cout << setw (70) << right << "     3. Chuyen tien                  " << endl;
		cout << setw (70) << right << "     4. Xem noi dung giao dich       " << endl;
		cout << setw (70) << right << "     5. Doi ma PIN                   " << endl;
		cout << setw (70) << right << "     6. Thoat                        " << endl;
		cout << setw (70) << right << "*************************************" << endl;
	}

	void XemThongTinTaiKhoan()
	{
		cout << setw (70) << right << "            Tai Khoan               " << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw (34) << "" << "ID: " << id << endl;
		cout << setw (34) << "" << "Ho va ten: " << name << endl;
		cout << setw (34) << "" << "So du: " << sodu << " " << dv << endl;
	}

	void RutTien()
	{
		string choose;
		int money; 
		tryagain:
		cout << setw (70) << right << "               Rut Tien              " << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw (34) << "" << "1. 1.000.000 VND" << endl;
		cout << setw (34) << "" << "2. 2.000.000 VND" << endl;
		cout << setw (34) << "" << "3. 3.000.000 VND" << endl;
		cout << setw (34) << "" << "4. So khac" << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw (34) << "" << "Nhap lua chon cua ban: ";
		cin >> choose;
		if (choose == "1")
		{
			money = 1000000;
		}
		else if (choose == "2")
		{
			money = 2000000;
		}
		else if (choose == "3")
		{
			money = 3000000;
		}
		else if (choose == "4")
		{
			cout << setw (34) << "" << "Nhap so tien muon rut: ";
			cin >> money;
		}
		
		if( (money % 50000 == 0) && (money >= 50000) && (sodu - money >= 50000))
		{
			sodu -= money;
			ghiNoiDungGiaoDich("Rut Tien", money*-1);
			cout << setw (34) << "" << "Giao dich thanh cong!!!" << endl;
			cout << setw (34) << "" << "So du tai khoan: " << sodu << " " << dv << endl;
			cout << setw (34) << "" << "Nhan the truoc khi nhan tien !!!" << endl;
		}
		else
		{
			cout << setw (34) << "" << "Giao dich khong thanh cong !!!" << endl;
			cout << setw (34) << "" << "So tien rut phai >= 50.000 VND" << endl;
			cout << setw (34) << "" << "Tai khoan phai con lai it nhat 50.000 VND" << endl;
			system("pause");
			system("cls");
			MenuUser();
			goto tryagain;
		}
	}

	void ChuyenTien(User a[], TheTu b[], int n, int index)
	{
		string _id;
		cout << setw (70) << right << "            Chuyen Khoan             " << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw (34) << "" << "Nhap so tai khoan can chuyen: ";
		cin >> _id;
		int account = SearchID(b, n, _id);
		if (account != -1)
		{
			int money;
			tryagain:
			cout << setw (34) << "" << "Nhap so tien can chuyen: ";
			cin >> money;
			if((money >= 50000) && (sodu - money >= 50000))
			{
				sodu -= money;
				a[account].sodu += money;
				updateDSUser(a, n);
				cout << setw (34) << "" << "Giao dich thanh cong !!!" << endl;
				cout << setw (34) << "" << "So du tai khoan: " << sodu << " " << dv << endl;
				ghiNoiDungGiaoDich("Chuyen Tien", money*-1);
				a[account].ghiNoiDungGiaoDich("Nhan Tien", money); 
			}
			else
			{
				cout << setw (34) << "" << "Giao dich khong thanh cong !!!" << endl;
				cout << setw (34) << "" << "So tien giao dich phai >= 50.000 VND" << endl;
				cout << setw (34) << "" << "Tai khoan phai con lai it nhat 50.000 VND" << endl;
				system("pause");
				system("cls");
				MenuUser();
				cout << setw (70) << right << "            Chuyen Khoan             " << endl;
				cout << setw (70) << right << "-------------------------------------" << endl;
				cout << setw (34) << "" << "Nhap so tai khoan can chuyen: " << _id << endl;
				goto tryagain; 
			}	
		}
		else
		{
			cout << setw (34) << "" << "ID khong ton tai !!!" << endl; 
		}	
	}

};

class LichSu : public User
{
	string loai;
	long sotien;
	string thoigian;
public:
	LichSu(string _id = "", string _loai = "", long _sotien = 0, string _thoigian = "")
	{
		id = _id;
		loai = _loai;
		sotien = _sotien;
		thoigian = _thoigian;
	}
	~LichSu(){};
	
	friend istream& operator >> (istream& is, LichSu &p)
	{
		is >> p.id;
		is.ignore();
		getline(is, p.loai);
		is >> p.sotien;
		is.ignore();
		getline(is, p.thoigian);
		return is;
	}	
	friend void loadDSLichSu(LichSu a[], int &n, string _id)
	{
		ifstream in;
		in.open("LichSuID.txt");
		if (in.is_open())
		{
			LichSu tmp;
			n = 0;
			while(in >> tmp)
			{
				if (tmp.id == _id)
				 {
				 	a[n] = tmp;
				 	n++;
				 } 
			}
			in.close();
		}
		else
		{
			cout << "He thong dang bao tri moi ban quay lai sau !!!" << endl;
			exit(0);
		}	
	}

	friend void xemNoiDungGiaoDich(LichSu a[], int n)
	{
		cout << setw (70) << right << "         Lich Su Giao Dich           " << endl;
		cout << setw (70) << right << "-------------------------------------" << endl;
		cout << setw(4) << ""  << setw(20) << left << "Loai giao dich";
		cout << setw(4) << ""  << setw(20) << left << "So tien";
		cout << setw(4) << ""  << setw(50) << left << "Thoi gian";
		cout << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << setw(4) << ""  << setw(20) << left << a[i].loai;
			cout << setw(4) << ""  << setw(20) << left << a[i].sotien;
			cout << setw(4) << ""  << setw(50) << left << a[i].thoigian;
			cout << setw(4) << ""  << endl;
		}
	}
};	

class Admin : public User
{
public:
	Admin(string _id = "", string _pin = "")
	{
		id = _id;
		pin = _pin;
	}

	Admin(const Admin &p)
	{
		id = p.id;
		pin = p.pin;
	}

	~Admin(){};
	
	friend istream& operator >> (istream& is, Admin &p)
	{
		is >> p.id;
		is >> p.pin;
		return is;
	} 
	void menuAdmin()
	{
		cout << "\n\n";
		cout << setw (70) << right << "****************Menu*****************" << endl;
		cout << setw (70) << right << "     1. Xem danh sach tai khoan      " << endl;
		cout << setw (70) << right << "     2. Them tai khoan               " << endl;
		cout << setw (70) << right << "     3. Xoa tai khoan                " << endl;
		cout << setw (70) << right << "     4. Mo khoa tai khoan            " << endl;
		cout << setw (70) << right << "     5. Thoat                        " << endl;
		cout << setw (70) << right << "*************************************" << endl;
	}

	friend void loadDSAdmin(Admin a[], int &n)
	{
		ifstream in;
		in.open("Admin.txt");
		if(in.is_open())
		{
			n = 0;
			while(in >> a[n]) { n++; }
			in.close();
		}
		else
		{
			cout << setw (70) << right << "He thong dang bao tri moi ban quay lai sau !!!" << endl;
			exit(0);
		}	
	}
	void dangNhapAdmin(Admin a[], int n)
	{
		string _id, _pass;
		int dem = 0;
		while(dem < 3)
		{
			system("cls");
			cout << setw (70) << right << "*************************************" << endl;
			cout << setw(70) << right << "            DANG NHAP Admin           " <<endl;
			cout << setw (70) << right << "*************************************" << endl;
			cout << setw(44) << right << "Admin: ";
			cin >> _id;
			cout << setw(43) << right << "PASS: ";
			_pass = passwordInput(6);
			for (int i = 0; i < n; ++i)
			{
				if(a[i].id == _id && a[i].pin == _pass)
				{
					system("cls");
					cout << "\n\n\n";
					cout << setw(75) << right << "------------DANG NHAP THANH CONG-----------" << endl;
					cout << "\n\n\n";
					system("pause");
					system("cls");
					return;
				}
			}
			cout << setw(71) << right << "Tai khoan hoac mat khau khong dung !!!" << endl;
			dem++;
			system("pause");
		}
		cout << setw(63) << right << "BAN DA NHAP SAI QUA NHIEU LAN !!!" << endl;
		system("pause");
		exit(0);
	}

	void xemDStaikhoan(User a[], TheTu b[], int n)
	{
		
		cout << setw(65) << right << "DANH SACH TAI KHOAN NGAN HANG" << endl;
		cout << endl;
		cout << setw(4) << "" << setw(20) << left << "ID";
		cout << setw(4) << "" << setw(34) << left << "Name";
		cout << setw(4) << "" << setw(6) << left << "So du";
		cout << setw(4) << "" << setw(10) << left << "Loai";
		cout << setw(6) << left << "Trang Thai";
		cout << endl;
		
		for (int i = 0; i < n; ++i)
		{
			cout << setw(4) << "" << setw(20) << left << a[i].getID();
			cout << setw(4) << "" << setw(30) << left << a[i].getName();
			cout << setw(4) << "" << setw(10) << right << a[i].getSodu();
			cout << setw(4) << "" << setw(10) << left << a[i].getDv();
			cout << setw(6) << left << (b[i].getStatus() == 0 ? "bi khoa" : "binh thuong");
			cout << endl;
		}
		cout << endl;
	}

	void danhSachTaiKhoanBiKhoa(User a[], TheTu b[], int n)
	{
		cout << setw(65) << right << "DANH SACH TAI KHOAN BI KHOA" << endl;
		cout << endl;
		cout << setw(4) << "" << setw(20) << left << "ID";
		cout << setw(4) << "" << setw(34) << left << "Name";
		cout << setw(4) << "" << setw(6) << left << "So du";
		cout << setw(4) << "" << setw(10) << left << "Loai";
		cout << setw(6) << left << "Trang Thai";
		cout << endl;
		
		for (int i = 0; i < n; ++i)
		{
			if(!b[i].getStatus())
			{
				cout << setw(4) << "" << setw(20) << left << a[i].getID();
				cout << setw(4) << "" << setw(30) << left << a[i].getName();
				cout << setw(4) << "" << setw(10) << right << a[i].getSodu();
				cout << setw(4) << "" << setw(10) << left << a[i].getDv();
				cout << setw(6) << left << (b[i].getStatus() == 0 ? "bi khoa" : "binh thuong");
				cout << endl;
			}
		}
		cout << endl;
	}

	void moKhoaTaiKhoan(TheTu b[], int n)
	{
		string _id;
		cout << setw (34) << "" << "Nhap ID cua tai khoan can mo khoa: ";
		cin >> _id;
		int index = SearchID(b, n, _id);
		if (index == -1)
		{
			cout << setw (34) << ""  << "Khong tim thay ID !!!" << endl;
		}
		else
		{
			b[index].setStatus(1);
			updateDSTheTu(b, n);
			cout << setw (34) << ""  << "Da mo khoa tai khoan co ID: " << _id << endl;
		}	
	}

	void xoaTaiKhoan(User a[], TheTu b[], int &n)
	{
		string _id;
		cout << setw (34) << "" << "Nhap ID tai khoan muon xoa: ";
		cin >> _id;
		int index = SearchID(b, n, _id);
		if(index == -1)
		{
			cout << setw (34) << "" << "ID khong ton tai !!!" << endl;
			return;
		}	
		for (int i = index; i < n-1; ++i)
		{
			a[i] = a[i+1];
			b[i] = b[i+1];
		}
		n--;
		updateDSUser(a, n);
		updateDSTheTu(b, n);
		cout << setw (34) << "" << "Da xoa tai khoan co ID: " << _id << endl;
	}

	void themTaiKhoan(User a[], TheTu b[], int &n)
	{
		string _id, _name, _dv, _pin;
		long _sodu;
		while(true)
		{	system("cls");
			menuAdmin();
			cout << setw (70) << right << "             TAO TAI KHOAN           " << endl;
			cout << setw (44) << right << "ID: " ;
			cin >> _id;
			if (SearchID(b, n, _id) != -1)
			{
				system("cls");
				cout << setw (65) << right << "ID da ton tai !!!" << endl;
				system("pause");
				continue;
			}
			else
			{
				cin.ignore();
				cout << setw (51) << right << "Ho va ten: ";
				getline(cin, _name);
				cout << setw (47) << right << "So du: ";
				cin >> _sodu;
				cout << setw (56) << right << "Don vi tien te: "; 
				cin >> _dv;
				cout << setw (53) << right << "Nhap ma Pin: ";
				_pin = password(6);
				a[n].set(_id, _name, _sodu, _dv);
				b[n].set(_id, _pin);
				n++;
				updateDSUser(a, n);
				updateDSTheTu(b, n);
				cout << setw (68) << right << "Tao tai khoan thanh cong !!!" << endl;
				return;
			}	
		}	
	}
};

int main()
{
	Admin arr_Admin[100];
	User arr_User[100];
	TheTu arr_Thetu[100];
	int n_User;
	int n_Admin;
	loadDSAdmin(arr_Admin, n_Admin);
	LoadDSuser(arr_User, n_User);
	loadDSTheTu(arr_Thetu, n_User);
	string choose;
	int index;
	dinhDang();
	while (true)
	{	
		cout << "\n\n";
		cout << setw (70) << right << "****************MENU*****************" << endl;
		cout << setw (70) << right << "         1.Dang nhap User            " << endl;
		cout << setw (70) << right << "         2.Dang nhap Admin           " << endl;
		cout << setw (70) << right << "*************************************" << endl;
		cout << setw (60) << right <<"Nhap lua chon cua ban: ";
		cin >> choose;
		if (choose == "1")
		{
			arr_Thetu[n_User].dangNhapUser(arr_Thetu, n_User, index);
			while (true)
			{
				arr_User[index].MenuUser();
				cout << setw (60) << right <<"Nhap lua chon cua ban: ";
				cin >> choose;
				cout << setw (70) << right <<"-------------------------------------" << endl;
				cout << endl;
				if (choose == "1")
				{
					arr_User[index].XemThongTinTaiKhoan();
				}
				else if (choose == "2")
				{
					arr_User[index].RutTien();
					arr_User[index].updateDSUser(arr_User, n_User);
				}
				else if (choose == "3")
				{
					arr_User[index].ChuyenTien(arr_User, arr_Thetu, n_User, index);
					arr_User[index].updateDSUser(arr_User, n_User);
				}
				else if (choose == "4")
				{
					int n_Lichsu;
					LichSu arr_Lichsu[1000];
					loadDSLichSu(arr_Lichsu, n_Lichsu, arr_User[index].getID());
					xemNoiDungGiaoDich(arr_Lichsu, n_Lichsu);
				}	
				else if (choose == "5")
				{
					arr_Thetu[index].doiMaPin();
					arr_Thetu[index].updateDSTheTu(arr_Thetu, n_User);
				}
				else if (choose == "6")
				{
					system("cls");
					break;
				}
				system("pause");
				system("cls");
			}	
		}
		else if (choose == "2")
		{
			arr_Admin[n_Admin].dangNhapAdmin(arr_Admin, n_Admin);
			while (true)
			{
				arr_Admin[n_Admin].menuAdmin();
				cout << setw (60) << right <<"Nhap lua chon cua ban: ";
				cin >> choose;
				cout << setw (70) << right <<"-------------------------------------" << endl;
				cout << endl;
				if (choose == "1")
				{
					arr_Admin[n_Admin].xemDStaikhoan(arr_User, arr_Thetu, n_User);
				}
				else if (choose == "2")
				{
					arr_Admin[n_Admin].themTaiKhoan(arr_User, arr_Thetu, n_User);
				}
				else if (choose == "3")
				{
					arr_Admin[n_Admin].xemDStaikhoan(arr_User, arr_Thetu, n_User);
					arr_Admin[n_Admin].xoaTaiKhoan(arr_User, arr_Thetu, n_User);
				}	
				else if (choose == "4")
				{
					arr_Admin[n_Admin].danhSachTaiKhoanBiKhoa(arr_User, arr_Thetu, n_User);
					arr_Admin[n_Admin].moKhoaTaiKhoan(arr_Thetu, n_User);
				}
				else if (choose == "5")
				{
					system("cls");
					break;
				}
				system("pause");
				system("cls");
			}
		}	
		// Con day la xu ly loi nhap sai	
		else
		{
			system("cls");
			cout << "\n\n\n";
			cout << setw (34) << "" << "Nhap Sai !!!" << endl;
			cout << "\n\n\n";
			system("pause");
			system("cls");
		}
	}
	
	return 0;
}

string passwordInput(unsigned maxLength)
{
    string pw;
    for (char c; (c = getch()); )
    {
        if (c == '\n' || c == '\r') { //phím enter
            cout << "\n";
            break;
        } 
		else if (c == '\b') { //phím backspace
            cout << "\b \b";
            if (!pw.empty()) pw.erase(pw.size()-1);
        } 
		else if (c == -32) { //phím mũi tên
            _getch(); //bỏ qua kí tự tiếp theo (hướng mũi tên)
        } 
		else if (isprint(c) && pw.size() < maxLength) { //isprint tức là chỉ nhận những ký tự in ra được (có tính khoảng trắng)
            cout << '*';
            pw += c;
        }
    }
    return pw;
}

string password(unsigned maxLength)
{
    string pw;
    for (char c; (c = getch()); )
    {
        if (c == '\n' || c == '\r') { //phím enter
            cout << "\n";
            break;
        } 
		else if (c == '\b') { //phím backspace
            cout << "\b \b";
            if (!pw.empty()) pw.erase(pw.size()-1);
        } 
		else if (c == -32 || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == ' ') { //phím mũi tên
            _getch(); //bỏ qua kí tự tiếp theo (hướng mũi tên)
        } 
		else if (isprint(c) && pw.size() < maxLength) { //isprint tức là chỉ nhận những ký tự in ra được (có tính khoảng trắng)
            cout << c;
            pw += c;
        }
    }
    return pw;
}

// ham dinh dang man hinh console
void setCoLor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void dinhDang()
{
	SetConsoleTitle("ATM");
	setCoLor(0, 2);
}
